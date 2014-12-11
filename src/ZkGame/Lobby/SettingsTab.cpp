#include <QtCore>

#include "../Config/Config.hpp"

#include "SettingsTab.hpp"

using namespace Zk::Game;

SettingsTab::SettingsTab(Config & config, QWidget * parent)
: QWidget(parent), config(config)
{
	initEdits();
	initLayout();
}

SettingsTab::~SettingsTab()
{

}

void SettingsTab::initEdits()
{
	respawnTimeEdit = new QDoubleSpinBox;
	maxGrenadesEdit = new QSpinBox;
	maxMedkitsEdit = new QSpinBox;

	respawnTimeEdit->setValue(config.settingsConfig.respawnTime());
	maxGrenadesEdit->setValue(config.settingsConfig.maxGrenadePacksOnMap());
	maxMedkitsEdit->setValue(config.settingsConfig.maxMedkitsOnMap());

	connect(respawnTimeEdit, SIGNAL(valueChanged(double)), &config.settingsConfig, SLOT(setRespawnTime(double)));
	connect(maxGrenadesEdit, SIGNAL(valueChanged(int)), &config.settingsConfig, SLOT(setMaxGrenadePacksOnMap(int)));
	connect(maxMedkitsEdit, SIGNAL(valueChanged(int)), &config.settingsConfig, SLOT(setMaxMedkitsOnMap(int)));
}

void SettingsTab::initLayout()
{
	QFormLayout *mainLayout = new QFormLayout;
	this->setLayout(mainLayout);

	mainLayout->addRow("Respawn time", respawnTimeEdit);
	mainLayout->addRow("Max granades pack on map", maxGrenadesEdit);
	mainLayout->addRow("Max medkits on map", maxMedkitsEdit);
}
