#include "MainWindow.hpp"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	return app.exec();
}
