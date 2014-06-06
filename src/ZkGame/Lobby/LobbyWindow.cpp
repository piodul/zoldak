#include <QtCore>
#include <QtGui>

#include "LobbyWindow.h"
#include "PlayTab.h"
#include "GraphicsTab.h"

using namespace Zk::Game;

LobbyWindow::LobbyWindow(QWidget * parent)
	: QMainWindow(parent)
{
	QTabWidget * tabWidget = new QTabWidget();
	tabWidget->addTab(new PlayTab(), "Game");
	tabWidget->addTab(new GraphicsTab(), "Graphics");
	
	setCentralWidget(tabWidget);
}

LobbyWindow::~LobbyWindow()
{
	
}
