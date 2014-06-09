#include <QtCore>
#include <QtGui>

#include "../Config/Config.h"
#include "../GameSystem.h"

#include "PlayTab.h"

using namespace Zk::Game;

PlayTab::PlayTab(Config & config, QWidget * parent)
	: QWidget(parent), config(config)
{
	//Lewa strona:
	//Lista poziomów + labelka
	QLabel * levelListLabel = new QLabel("Choose a level:");
	
	levelListModel = new QStringListModel();
	levelListView = new QListView();
	levelListView->setModel(levelListModel);
	levelListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	QVBoxLayout * leftLayout = new QVBoxLayout();
	leftLayout->addWidget(levelListLabel);
	leftLayout->addWidget(levelListView);
	
	//Prawa strona:
	//Opcje + przycisk rozpoczęcia gry
	startGameButton = new QPushButton("Play!");
	connect(startGameButton, SIGNAL(clicked()),
			this, SLOT(startGame()));
	
	QHBoxLayout * mainLayout = new QHBoxLayout();
	mainLayout->addLayout(leftLayout);
	mainLayout->addWidget(startGameButton);
	
	this->setLayout(mainLayout);
	
	QStringList sl;
	sl << "One" << "Two" << "Three";
	levelListModel->setStringList(sl);
}

PlayTab::~PlayTab()
{
	
}

void PlayTab::startGame()
{
	GameSystem::getInstance()->changeState(GameSystem::State::Game);
}
