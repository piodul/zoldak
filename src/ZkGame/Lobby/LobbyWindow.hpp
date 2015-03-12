#pragma once

#include <QtWidgets>

#include "../Config/Config.hpp"

namespace Zk {
namespace Game {

class LobbyWindow : public QMainWindow
{
	Q_OBJECT;

public:
	LobbyWindow(Config & config, QWidget * parent = nullptr);
	virtual ~LobbyWindow() = default;

	virtual void closeEvent(QCloseEvent * event) override;

private:
	Config & config;
};

}}
