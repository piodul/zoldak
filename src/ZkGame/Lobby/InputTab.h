#pragma once

#include <QtWidgets>

#include <map>

#include "../Config/PlayerAction.h"
#include "../Config/InputAction.h"

namespace Zk {
namespace Game {

class InputTab : public QWidget
{
	Q_OBJECT;
	
public:
	InputTab(QWidget * parent = nullptr);
	virtual ~InputTab();
	
private slots:
	void changeInputBind(QTableWidgetItem * twi);
	
private:
	QTableWidget * keyBindsWidget;
	std::map<PlayerAction, InputAction> keyBinds;
};

}}
