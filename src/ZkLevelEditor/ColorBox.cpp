#include "ColorBox.h"
#include "ColorPaletteWidget.h"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

ColorBox::ColorBox(QWidget * parent)
	: QWidget(parent)
{
	
}

ColorBox::~ColorBox()
{
	
}

void ColorBox::setColor(QColor color)
{
	this->color = color;
}

QColor ColorBox::getColor() const
{
	return color;
}

QSize ColorBox::sizeHint() const
{
	return QSize(32, 32);
}

void ColorBox::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.fillRect(rect(), color);
}

void ColorBox::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		//emit selected(this);
		event->accept();
	}
	else if (event->button() == Qt::RightButton)
	{
		QColor c = QColorDialog::getColor(color, this);
		if (c.isValid())
		{
			color = c;
			update();
		}
		
		event->accept();
	}
	
	QWidget::mousePressEvent(event);
}
