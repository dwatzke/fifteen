#include "Board.h"
#include "MainWindow.h"
#include <QtGlobal>
#include <QDebug>
#include <QGridLayout>
#include <QObject>
#include <QPoint>
#include <QPushButton>
#include <QString>
#include <QTime>

#include <cstdlib> // for rand()

Board::Board(int cb, QWidget* parent) : QWidget(parent), cube(cb)
{
	grid = new QGridLayout;
	grid->setHorizontalSpacing(1);
	grid->setVerticalSpacing(1);
	grid->setContentsMargins(2, 2, 2, 2);

	QTime midnight(0, 0, 0);
	srand(midnight.secsTo(QTime::currentTime()));

	int n;

	for(int i = 0; i < size(); i++)
	{ // random numbers from
		do n = rand() % size() + 1; // add 1, mod returns in range (0, size()-1)
		while(numbers.contains(n));
		numbers << n;
	}

	n = 0;

	// check for which path-row is this random placement solvable
	for(int i = 2; i <= size(); i++)
	for(int j = 0; j < numbers.indexOf(i); j++)
		if(numbers[j] < i) ++n;

	// generate a random even or odd row position of the initial path, depending on "n"
	do path.setY(rand() % cube);
	while(n%2 != path.y()%2);

	path.setX(rand() % cube);

	n = 0;

	for(int y = 0; y < cube; ++y) // row
	for(int x = 0; x < cube; ++x) // column
	{
		if(path.x() == x && path.y() == y)
			continue;

		createButton(NULL, numbers[n++], x, y);
	}

	setLayout(grid);
}

Board::~Board()
{
	QLayoutItem* child;
	while((child = grid->takeAt(0)) != 0)
		delete child;
	delete grid;
}

void Board::moveClicked()
{
	int x, y, rs, cs;
	QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
	grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

	if((path.x() == x && (path.y() == y+1 || path.y() == y-1))
	|| (path.y() == y && (path.x() == x+1 || path.x() == x-1))) // valid button, move it
	{
		// remove the widget from the actual position
		grid->removeWidget(clickedBtn);
		// and re-add it to where the path has been
		createButton(clickedBtn, 0, path.x(), path.y());
		// and update the path coordinates
		path = QPoint(x, y);
		// also update the move count
		static_cast<MainWindow*>(parentWidget())->updateMoves();
		checkGameOver();
	}
}

void Board::checkGameOver()
{
	Q_ASSERT(grid->count() == numbers.size());

	int i=1, n=0;

	// check whether the buttons are placed upwardly from 1 to n
	for(int y = 0; y < grid->rowCount(); ++y) // row
	for(int x = 0; x < grid->columnCount(); ++x) // column
	{
		if(grid->itemAtPosition(y, x) == 0)
			continue;
		n = numbers.indexOf(i++);
		if(buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
			return;
	}

	// check whether the path is the last item in the grid
	if(path.y() == grid->rowCount()-1 && path.x() == grid->columnCount()-1)
	{ // game over:
		// disable all the buttons
		for(QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
			(*it)->setDisabled(true);
		// stop the timer
		static_cast<MainWindow*>(parentWidget())->stopTimer();
	}
}

void Board::createButton(QPushButton* b, int no, int x, int y)
{
	QPushButton* btn = b;
	if(!btn)
	{
		btn = new QPushButton(QString("%1").arg(no), this);
		buttons << btn;
		connect(btn, SIGNAL(clicked()), this, SLOT(moveClicked()));
		btn->setFixedSize(50, 50);
	}
	grid->addWidget(btn, y, x);
}

int Board::size() const
{
	return cube*cube-1;
}
