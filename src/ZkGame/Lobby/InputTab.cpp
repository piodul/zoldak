#include <QtCore>

#include <SFML/Window.hpp>

#include <algorithm>
#include <map>

#include "../Config/Config.hpp"
#include "../Config/InputAction.hpp"
#include "../Config/PlayerAction.hpp"

#include "../InputSystem.hpp"
#include "../GameSystem.hpp"

#include "InputChoiceDialog.hpp"
#include "MouseChoiceDialog.hpp"
#include "InputTab.hpp"

using namespace Zk::Game;

InputTab::InputTab(Config & config, QWidget * parent)
	: QWidget(parent), config(config)
{
	playerNumberLabel = new QLabel();

	keyBindsWidget = new QTableWidget((int)PlayerAction::NUM_ACTIONS, 2);
	keyBindsWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	keyBindsWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(keyBindsWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
			this, SLOT(changeInputBind(QTableWidgetItem*)));

	QPushButton * changePlayerButton = new QPushButton("Change player");
	connect(changePlayerButton, SIGNAL(clicked()),
			this, SLOT(changePlayer()));

	QPushButton * changeMouseButton = new QPushButton("Change mouse");
	connect(changeMouseButton, SIGNAL(clicked()),
			this, SLOT(changeMouseDevice()));

	QPushButton * resetManyMouseButton = new QPushButton("Reset ManyMouse");
	connect(resetManyMouseButton, SIGNAL(clicked()),
			this, SLOT(resetInputSystem()));

	QHBoxLayout * bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(changePlayerButton);
	bottomLayout->addWidget(changeMouseButton);
	bottomLayout->addWidget(resetManyMouseButton);
	bottomLayout->addStretch();

	QVBoxLayout * mainLayout = new QVBoxLayout();
	mainLayout->addWidget(playerNumberLabel);
	mainLayout->addWidget(keyBindsWidget);
	mainLayout->addLayout(bottomLayout);
	this->setLayout(mainLayout);

	displayedPlayerID = 1;
	changePlayer();
}

InputTab::~InputTab()
{

}

void InputTab::changeInputBind(QTableWidgetItem * twi)
{
	InputAction & ia =
		config.playerInputConfig[displayedPlayerID].playerToInput[(PlayerAction)twi->row()];

	PlayerAction pa = (PlayerAction)twi->row();
	InputChoiceDialog::chooseInputAction(ia);
	keyBindsWidget->item((int)pa, 1)->setText(ia.getName());
}

void InputTab::changeMouseDevice()
{
	MouseChoiceDialog::chooseMouse(
		config.playerInputConfig[displayedPlayerID].mouseDevice
	);
}

void InputTab::resetInputSystem()
{
	GameSystem::getInstance()->getInputSystem().resetMice();
}

void InputTab::changePlayer()
{
	displayedPlayerID = 1 - displayedPlayerID;
	playerNumberLabel->setText(
		QString("<b>Player #%1:</b>").arg(displayedPlayerID + 1)
	);
	updateItems();
}

void InputTab::updateItems()
{
	for (int i = 0; i < (int)PlayerAction::NUM_ACTIONS; i++)
	{
		InputAction ia =
			config.playerInputConfig[displayedPlayerID].playerToInput[(PlayerAction)i];

		keyBindsWidget->setItem(
			i, 0,
			new QTableWidgetItem(playerActionToName((PlayerAction)i))
		);

		keyBindsWidget->setItem(
			i, 1,
			new QTableWidgetItem(ia.getName())
		);
	}
}
