#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class ColorBox;

class ColorPaletteWidget : public QWidget
{
	Q_OBJECT;
	
public:
	ColorPaletteWidget(int columns, int rows, QWidget * parent = nullptr);
	virtual ~ColorPaletteWidget();
	
	QColor getSelectedColor() const;
	
private slots:
	void setColor(QColor color);

signals:
	void colorChanged(QColor color);
	
private:
	QHash<QPair<int, int>, ColorBox*> boxes;
	QColor color;
	
};

}}
