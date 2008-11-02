#include "MainWindow.h"
#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QObject>
#include <QPushButton>
#include <QSizePolicy>
#include <QString>
#include <QSpinBox>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget*) : board(NULL)
{
	cubesize = new QSpinBox;
	cubesize->setRange(3, 20);
	cubesize->setValue(4);

	QLabel* secsLabel = new QLabel(tr("Secs:"));
	QLabel* movesLabel = new QLabel(tr("Moves:"));

	lcdSecs = new QLCDNumber(4);
	lcdMoves = new QLCDNumber(4);
	QPushButton* newgame = new QPushButton(tr("New game"));
	connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));

	lcdLayout = new QHBoxLayout;
	lcdLayout->addWidget(secsLabel);
	lcdLayout->addWidget(lcdSecs, 1);
	lcdLayout->addWidget(movesLabel);
	lcdLayout->addWidget(lcdMoves, 1);

	settingsLayout = new QHBoxLayout;
	settingsLayout->addWidget(newgame, 1);
	//settingsLayout->addWidget(cubesize);

	layout = new QVBoxLayout;
	layout->setContentsMargins(2, 2, 2, 2);
	layout->addLayout(settingsLayout);
	layout->addLayout(lcdLayout);
	newGame();

	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));
	timer->setInterval(1000);

	setLayout(layout);
}

MainWindow::~MainWindow()
{
	QLayoutItem *child;
	while((child = lcdLayout->takeAt(0)) != 0)
		delete child;
	while((child = settingsLayout->takeAt(0)) != 0)
		delete child;
	while((child = layout->takeAt(0)) != 0)
		delete child;
	delete layout;
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
	/* FIXME: this is apparently needed for resize() to set the proper size :-/ */
	board->hide();
	board->show();

	seconds = -1;
	moves = -1;
	updateClock();
	updateMoves();

	layout->addWidget(board);

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
		timer->start();
	lcdMoves->display(++moves);
}
