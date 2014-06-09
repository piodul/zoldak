#pragma once

#include <QtWidgets>

#include "../Config/Config.h"

namespace Zk {
namespace Game {

class PlayTab : public QWidget
{
	Q_OBJECT;
	
public:
	PlayTab(Config & config, QWidget * parent = nullptr);
	virtual ~PlayTab();
	
private:
	QListView * levelListView;
	QStringListModel * levelListModel;
	
	QPushButton * startGameButton;
	
	Config & config;
};

}}
