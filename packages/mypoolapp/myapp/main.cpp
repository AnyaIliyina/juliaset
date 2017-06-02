#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
	
	setlocale(LC_ALL, "Russian");
	QApplication app(argc, argv);
	MainWindow *w = new MainWindow();
	w->show();
	return app.exec();
}
