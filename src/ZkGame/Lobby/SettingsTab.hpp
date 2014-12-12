#pragma once

#include <QtWidgets>

#include <map>

#include "../Config/Config.hpp"

namespace Zk {
namespace Game {

class SettingsTab : public QWidget
{
	Q_OBJECT;

public:
	SettingsTab(Config & config, QWidget * parent = nullptr);
	virtual ~SettingsTab();

private slots:

private:
	void initEdits();
	void initLayout();

	Config & config;
	QDoubleSpinBox * respawnTimeEdit;
	QSpinBox * maxGrenadesEdit;
	QSpinBox * maxMedkitsEdit;
	QCheckBox * enabledFovBox;
};

}}
