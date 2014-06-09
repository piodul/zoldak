#pragma once

#include <QtWidgets>

#include "../Config/Config.h"

namespace Zk {
namespace Game {

class GraphicsTab : public QWidget
{
	Q_OBJECT;
	
public:
	GraphicsTab(Config & config, QWidget * parent = nullptr);
	virtual ~GraphicsTab();
	
private:
	void populateResolutionsBox();
	
	QComboBox * resolutionsBox;
	QCheckBox * fullscreenBox;
	
	Config & config;
	
};

}}
