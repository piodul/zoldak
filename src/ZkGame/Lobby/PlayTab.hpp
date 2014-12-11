#pragma once

#include <QtWidgets>

#include "../Config/Config.hpp"

namespace Zk {
namespace Game {

class PlayTab : public QWidget
{
	Q_OBJECT;

public:
	PlayTab(Config & config, QWidget * parent = nullptr);
	virtual ~PlayTab();

private slots:
	void startGame();
	void selectLevel();

private:
	void populateLevelList();

	QListWidget * levelList;
	QPushButton * startGameButton;

	QString levelName;
	Config & config;
};

}}
