#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class ColorBox;

class ColorPaletteWidget : public QWidget
{
	Q_OBJECT;

public:
	ColorPaletteWidget(int rows, QWidget * parent = nullptr);
	virtual ~ColorPaletteWidget();

	void fromColorList(const std::vector<QColor> & colors);
	void toColorList(std::vector<QColor> & colors) const;

	QColor getSelectedColor() const;

private slots:
	void setColor(QColor color);
	void addRow();
	void removeRow();

signals:
	void colorChanged(QColor color);

private:
	void clear();
	void setRowCount(int count);

	ColorBox * createColorBox();

	QList<ColorBox*> boxes;
	QPushButton * moreButton;
	QPushButton * lessButton;
	QColor color;

	int numRows;
};

}}
