#include "mainwindow.h"
#include "connection.h"
#include "riotgames.h"

#include <QApplication>
#include <QFontDatabase>

MainWindow* gMainWindow;
Connection* gConnection;

int main(int argc, char *argv[]){
	riotgames::init();
	QApplication a(argc, argv);
	int id = QFontDatabase::addApplicationFont("assets/fonts/frizquadratatt.ttf");

	gConnection = new Connection();
	gMainWindow = new MainWindow();
	gMainWindow->show();

	return a.exec();
}
