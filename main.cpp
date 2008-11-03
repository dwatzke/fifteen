#include <QApplication>
#include "MainWindow.h"

/* TODO:
   button size (btn->fontMetrics())
   LCD number width...
*/

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	return app.exec();
}
