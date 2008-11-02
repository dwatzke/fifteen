#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QWidget>
class QGridLayout;
class QPoint;
class QPushButton;

class Board : public QWidget
{
	Q_OBJECT
private:
	QList<QPushButton*> buttons;
	QList<int> numbers;
	QGridLayout* grid;
	QPoint path;
	int cube;
	unsigned int clicks;

	void checkGameOver();
	int size() const;

public slots:
	void moveClicked();

public:
	Board(int cb = 4, QWidget* parent = 0);
	//~Board();
	void createButton(QPushButton*, int, int, int);
};

#endif
