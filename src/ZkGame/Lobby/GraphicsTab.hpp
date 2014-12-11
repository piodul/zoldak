#pragma once

#include <QtWidgets>

#include "../Config/Config.hpp"

namespace Zk {
namespace Game {

class GraphicsTab : public QWidget
{
	Q_OBJECT;

public:
	GraphicsTab(Config & config, QWidget * parent = nullptr);
	virtual ~GraphicsTab();

private slots:
	void changeResolution(int index);
	void changeFullscreenOption(bool full);

private:
	void populateResolutionsBox();

	QComboBox * resolutionsBox;
	QCheckBox * fullscreenBox;

	Config & config;

};

}}
