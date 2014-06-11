#include <QtCore>
#include <QtGui>

#include "../Config/Config.h"
#include "../GameSystem.h"

#include "LobbyWindow.h"
#include "PlayTab.h"
#include "GraphicsTab.h"
#include "InputTab.h"

using namespace Zk::Game;

LobbyWindow::LobbyWindow(Config & config, QWidget * parent)
	: QMainWindow(parent), config(config)
{
	QTabWidget * tabWidget = new QTabWidget();
	tabWidget->addTab(new PlayTab(config), "Game");
	tabWidget->addTab(new GraphicsTab(config), "Graphics");
	tabWidget->addTab(new InputTab(config), "Input");
	
	setCentralWidget(tabWidget);
}

LobbyWindow::~LobbyWindow()
{
	
}

void LobbyWindow::closeEvent(QCloseEvent * event)
{
	GameSystem::getInstance()->changeState(GameSystem::State::Quit);
	event->accept();
}
