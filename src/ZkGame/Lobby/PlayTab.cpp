#include <QtCore>
#include <QtGui>

#include <QDebug>

#include "../Config/Config.hpp"
#include "../GameSystem.hpp"

#include "PlayTab.hpp"

using namespace Zk::Game;

PlayTab::PlayTab(Config & config, QWidget * parent)
	: QWidget(parent), config(config)
{
	//Lewa strona:
	//Lista poziomów + labelka
	QLabel * levelListLabel = new QLabel("Choose a level:");

	levelList = new QListWidget();
	levelList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(levelList, SIGNAL(itemSelectionChanged()),
			this, SLOT(selectLevel()));

	QVBoxLayout * leftLayout = new QVBoxLayout();
	leftLayout->addWidget(levelListLabel);
	leftLayout->addWidget(levelList);

	//Prawa strona:
	//Opcje + przycisk rozpoczęcia gry
	startGameButton = new QPushButton("Play!");
	connect(startGameButton, SIGNAL(clicked()),
			this, SLOT(startGame()));
	startGameButton->setEnabled(false);

	QHBoxLayout * mainLayout = new QHBoxLayout();
	mainLayout->addLayout(leftLayout);
	mainLayout->addWidget(startGameButton);

	this->setLayout(mainLayout);

	populateLevelList();
}

PlayTab::~PlayTab()
{

}

void PlayTab::startGame()
{
	GameSystem::getInstance()->setLevelName(QString("levels/") + levelName);
	GameSystem::getInstance()->changeState(GameSystem::State::Game);
}

void PlayTab::selectLevel()
{
	QListWidgetItem * lwi = levelList->currentItem();
	startGameButton->setEnabled(true);
	levelName = lwi->text();
}

void PlayTab::populateLevelList()
{
	QDir levelsDir(GameSystem::resourcePath("levels/").c_str());
	QStringList filters;
	filters << "*.zvl";
	QStringList levels = levelsDir.entryList(
		filters, QDir::Files | QDir::Readable, QDir::Name
	);

	for (const QString & s : levels)
		levelList->addItem(s);
}
