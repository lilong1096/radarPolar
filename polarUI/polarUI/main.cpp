#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow mainWindow;
	mainWindow.resize( 800, 600 );
	mainWindow.show();
	return a.exec();
}
