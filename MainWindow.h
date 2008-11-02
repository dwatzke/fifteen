#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
#include <QWidget>
class QHBoxLayout;
class QLabel;
class QLCDNumber;
class QSpinBox;
class QVBoxLayout;

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
	void updateMoves();
	void stopTimer();
public slots:
	void newGame();
	void updateClock();
private:
	Board* board;
	QHBoxLayout* lcdLayout;
	QHBoxLayout* settingsLayout;
	QVBoxLayout* layout;
	QLCDNumber* lcdSecs;
	QLCDNumber* lcdMoves;
	QSpinBox* cubesize;
	QTimer* timer;
	int seconds;
	int moves;
};

#endif
