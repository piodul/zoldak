#include <QtCore>
#include <QtGui>

#include "../Config/Config.hpp"
#include "../GameSystem.hpp"

#include "LobbyWindow.hpp"
#include "PlayTab.hpp"
#include "GraphicsTab.hpp"
#include "InputTab.hpp"

using namespace Zk::Game;

LobbyWindow::LobbyWindow(Config & config, QWidget * parent)
	: QMainWindow(parent), config(config)
{
	QTabWidget * tabWidget = new QTabWidget();
	tabWidget->addTab(new PlayTab(config), "Game");
	tabWidget->addTab(new GraphicsTab(config), "Graphics");
	tabWidget->addTab(new InputTab(config), "Input");
	
	setWindowIcon(
		QIcon(GameSystem::resourcePath("grenade-large.png").c_str())
	);

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
