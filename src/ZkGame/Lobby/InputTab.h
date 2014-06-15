#pragma once

#include <QtWidgets>

#include <map>

#include "../Config/Config.h"
#include "../Config/InputConfig.h"
#include "../Config/PlayerAction.h"
#include "../Config/InputAction.h"

namespace Zk {
namespace Game {

class InputTab : public QWidget
{
	Q_OBJECT;

public:
	InputTab(Config & config, QWidget * parent = nullptr);
	virtual ~InputTab();

private slots:
	void changeInputBind(QTableWidgetItem * twi);
	void changeMouseDevice();
	void resetInputSystem();
	void changePlayer();

private:
	void updateItems();

	QLabel * playerNumberLabel;
	QTableWidget * keyBindsWidget;
	int displayedPlayerID;
	Config & config;
};

}}
