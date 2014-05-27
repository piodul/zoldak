#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class ColorBox;

class ColorPaletteWidget : public QWidget
{
public:
	ColorPaletteWidget(int columns, int rows, QWidget * parent = nullptr);
	virtual ~ColorPaletteWidget();
	
private:
	QHash<QPair<int, int>, ColorBox*> boxes;
	
};

}}
