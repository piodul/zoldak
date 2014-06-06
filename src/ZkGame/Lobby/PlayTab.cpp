#include <QtCore>
#include <QtGui>

#include "PlayTab.h"

using namespace Zk::Game;

PlayTab::PlayTab(QWidget * parent)
	: QWidget(parent)
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
