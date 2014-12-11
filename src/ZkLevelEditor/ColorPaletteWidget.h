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

	void fromColorList(const QVector<QColor> & colors);
	QVector<QColor> toColorList() const;

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
