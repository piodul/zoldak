#pragma once

#include <QtWidgets>

namespace Zk {
namespace Game {

class GraphicsTab : public QWidget
{
	Q_OBJECT;
	
public:
	GraphicsTab(QWidget * parent = nullptr);
	virtual ~GraphicsTab();
	
private:
	QComboBox * resolutionsBox;
	QCheckBox * fullscreenBox;
	
	void populateResolutionsBox();
};

}}
