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
	
	void fromColorList(const std::vector<QColor> & colors);
	void toColorList(std::vector<QColor> & colors) const;
	
	QColor getSelectedColor() const;
	
private slots:
	void setColor(QColor color);

signals:
	void colorChanged(QColor color);
	
private:
	void clear();
	
	ColorBox * createColorBox();
	
	QList<ColorBox*> boxes;
	QColor color;
	
};

}}
