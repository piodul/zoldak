#include "ColorPaletteWidget.h"
#include "ColorBox.h"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

ColorPaletteWidget::ColorPaletteWidget(int columns, int rows, QWidget * parent)
	: QWidget(parent)
{
	QGridLayout * layout = new QGridLayout();
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			ColorBox * cb = new ColorBox();
			
			connect(cb, SIGNAL(colorSelected(QColor)),
				this, SLOT(setColor(QColor)));
			
			connect(this, SIGNAL(choiceChanged()),
				cb, SLOT(deselect()),
				Qt::DirectConnection);
			
			layout->addWidget(cb, x, y);
			boxes[QPair<int, int>(x, y)] = cb;
		}
	}
	
	setLayout(layout);
	
	boxes[QPair<int, int>(0, 0)]->select();
}

ColorPaletteWidget::~ColorPaletteWidget()
{
	
}

QColor ColorPaletteWidget::getSelectedColor() const
{
	return color;
}

void ColorPaletteWidget::setColor(QColor color)
{
	this->color = color;
	emit choiceChanged();
}
