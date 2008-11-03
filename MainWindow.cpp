#include "MainWindow.h"
//#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget*) : board(NULL)
{
	layout = new QVBoxLayout(this);
	lcdLayout = new QHBoxLayout;
	settingsLayout = new QHBoxLayout;

	QLabel* secsLabel = new QLabel(tr("Secs:"));
	QLabel* movesLabel = new QLabel(tr("Moves:"));
	lcdSecs = new QLCDNumber(4);
	lcdMoves = new QLCDNumber(4);
	//lcdSecs->setSegmentStyle(QLCDNumber::Filled);

	QPushButton* newgame = new QPushButton(tr("&New game"));
	cubesize = new QSpinBox;
	cubesize->setRange(3, 20);
	cubesize->setValue(4);
	connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));

	lcdLayout->addWidget(secsLabel);
	lcdLayout->addWidget(lcdSecs, 1);
	lcdLayout->addWidget(movesLabel);
	lcdLayout->addWidget(lcdMoves, 1);

	settingsLayout->addWidget(newgame, 1);
	settingsLayout->addWidget(cubesize);

	layout->setContentsMargins(2, 2, 2, 2);
	layout->addLayout(settingsLayout);
	layout->addLayout(lcdLayout);
	newGame();

	setLayout(layout);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
}

void MainWindow::newGame()
{
	if(board)
	{
		layout->removeWidget(board);
		delete board;
		stopTimer();
	}

	board = new Board(cubesize->value(), this);
	layout->addWidget(board);
	// without this old boards don't disappear
	layout->update();
	// FIXME: this is apparently needed for resize() to set the proper size
	board->hide();
	board->show();

	seconds = -1;
	moves = -1;
	updateClock();
	updateMoves();

	resize(sizeHint());
}

void MainWindow::stopTimer()
{
	timer->stop();
}

void MainWindow::updateClock()
{
	lcdSecs->display(++seconds);
}

void MainWindow::updateMoves()
{
	if(moves == 0)
		timer->start(1000);
	lcdMoves->display(++moves);
}
