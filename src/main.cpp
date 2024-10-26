#include "../services.hpp"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "../gui.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("Tutorial app");
	Services services;
	GUI gui = GUI(services);
	gui.show();
	return app.exec();
}