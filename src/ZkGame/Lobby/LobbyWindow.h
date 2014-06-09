#pragma once

#include <QtWidgets>

#include "../Config/Config.h"

namespace Zk {
namespace Game {

class LobbyWindow : public QMainWindow
{
	Q_OBJECT;
	
public:
	LobbyWindow(QWidget * parent = nullptr);
	virtual ~LobbyWindow();
	
private:
	Config config;
};

}}
