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
			layout->addWidget(cb, x, y);
			boxes[QPair<int, int>(x, y)] = cb;
		}
	}
	
	setLayout(layout);
}

ColorPaletteWidget::~ColorPaletteWidget()
{
	
}
