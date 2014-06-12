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
			ColorBox * cb = createColorBox();
			
			layout->addWidget(cb, y, x);
			boxes << cb;
		}
	}
	
	setLayout(layout);
	
	boxes[0]->select();
}

ColorPaletteWidget::~ColorPaletteWidget()
{
	
}

void ColorPaletteWidget::fromColorList(const std::vector<QColor> & colors)
{
	clear();
	
	QGridLayout * layout = new QGridLayout();
	
	for (int y = 0; y < (int)(colors.size() + 3) / 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int id = y * 4 + x;
			ColorBox * cb = createColorBox();
			
			if (id < (int)colors.size())
				cb->setColor(colors[id]);
			
			layout->addWidget(cb, y, x);
			boxes << cb;
		}
	}
	
	delete this->layout();
	setLayout(layout);
}

void ColorPaletteWidget::toColorList(std::vector<QColor> & colors) const
{
	colors.clear();
	
	for (const ColorBox * cb : boxes)
		colors.push_back(cb->getColor());
}

QColor ColorPaletteWidget::getSelectedColor() const
{
	return color;
}

void ColorPaletteWidget::setColor(QColor color)
{
	this->color = color;
	emit colorChanged(color);
}

void ColorPaletteWidget::clear()
{
	for (ColorBox * cb : boxes)
		delete cb;
	
	boxes.clear();
}

ColorBox * ColorPaletteWidget::createColorBox()
{
	ColorBox * cb = new ColorBox();
	
	connect(cb, SIGNAL(colorSelected(QColor)),
		this, SLOT(setColor(QColor)));
	
	connect(this, SIGNAL(colorChanged(QColor)),
		cb, SLOT(deselect()),
		Qt::DirectConnection);
	
	return cb;
}
