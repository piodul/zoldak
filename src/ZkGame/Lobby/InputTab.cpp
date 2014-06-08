#include <QtCore>

#include <SFML/Window.hpp>

#include <algorithm>
#include <map>

#include "../Config/InputAction.h"
#include "../Config/PlayerAction.h"

#include "InputChoiceDialog.h"
#include "InputTab.h"

using namespace Zk::Game;

InputTab::InputTab(QWidget * parent)
	: QWidget(parent)
{
	keyBindsWidget = new QTableWidget((int)PlayerAction::NUM_ACTIONS, 2);
	keyBindsWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	keyBindsWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	for (int i = 0; i < (int)PlayerAction::NUM_ACTIONS; i++)
	{
		keyBindsWidget->setItem(
			i, 0,
			new QTableWidgetItem(playerActionToName((PlayerAction)i))
		);
		
		keyBindsWidget->setItem(
			i, 1,
			new QTableWidgetItem(keyBinds[(PlayerAction)i].getName())
		);
	}
	
	connect(keyBindsWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
			this, SLOT(changeInputBind(QTableWidgetItem*)));
	
	QVBoxLayout * mainLayout = new QVBoxLayout();
	mainLayout->addWidget(keyBindsWidget);
	this->setLayout(mainLayout);
}

InputTab::~InputTab()
{
	
}

void InputTab::changeInputBind(QTableWidgetItem * twi)
{
	PlayerAction pa = (PlayerAction)twi->row();
	InputChoiceDialog::chooseInputAction(keyBinds[pa]);
	keyBindsWidget->item((int)pa, 1)->setText(keyBinds[pa].getName());
}
