#include <QtCore>
#include <QtGui>

#include "LobbyWindow.h"
#include "PlayTab.h"
#include "GraphicsTab.h"
#include "InputTab.h"

using namespace Zk::Game;

LobbyWindow::LobbyWindow(QWidget * parent)
	: QMainWindow(parent)
{
	QTabWidget * tabWidget = new QTabWidget();
	tabWidget->addTab(new PlayTab(), "Game");
	tabWidget->addTab(new GraphicsTab(), "Graphics");
	tabWidget->addTab(new InputTab(), "Input");
	
	setCentralWidget(tabWidget);
}

LobbyWindow::~LobbyWindow()
{
	
}
