#include "mainwindow.h"
#include "connection.h"
#include <QtGui/QApplication>

MainWindow* gMainWindow;
Connection* gConnection;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	gConnection = new Connection();
	gMainWindow = new MainWindow();
	gMainWindow->show();

	return a.exec();
}
