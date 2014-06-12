#include "ColorPaletteWidget.h"
#include "ColorBox.h"

#include <QtCore>
#include <QtGui>

#include <vector>

using namespace Zk::LevelEditor;

static const int NUM_COLUMNS = 4;
static const int MINIMUM_ROWS = 2;

ColorPaletteWidget::ColorPaletteWidget(int rows, QWidget * parent)
	: QWidget(parent)
{
	moreButton = new QPushButton("More");
	lessButton = new QPushButton("Less");
	
	numRows = 0;
	
	QVBoxLayout * layout = new QVBoxLayout();
	QHBoxLayout * buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(moreButton);
	buttonsLayout->addWidget(lessButton);
	layout->addLayout(buttonsLayout);
	
	setLayout(layout);
	
	connect(moreButton, SIGNAL(pressed()),
			this, SLOT(addRow()));
	connect(lessButton, SIGNAL(pressed()),
			this, SLOT(removeRow()));
	
	setRowCount(rows);
	
	if (numRows > 0)
		boxes[0]->select();
}

ColorPaletteWidget::~ColorPaletteWidget()
{
	
}

void ColorPaletteWidget::fromColorList(const std::vector<QColor> & colors)
{
	int rows = (int)(colors.size() + NUM_COLUMNS - 1) / NUM_COLUMNS;
	setRowCount(rows);
	
	int i;
	for (i = 0; i < (int)colors.size(); i++)
		boxes[i]->setColor(colors[i]);
	
	for (; i < boxes.size(); i++)
		boxes[i]->setColor(QColor(Qt::black));
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

void ColorPaletteWidget::addRow()
{
	QHBoxLayout * innerLayout = new QHBoxLayout();
	for (int i = 0; i < NUM_COLUMNS; i++)
	{
		ColorBox * cb = createColorBox();
		innerLayout->addWidget(cb);
		boxes << cb;
	}
	
	QVBoxLayout * layout = (QVBoxLayout*)this->layout();
	layout->insertLayout(numRows, innerLayout);
	
	numRows++;
}

void ColorPaletteWidget::removeRow()
{
	if (numRows <= MINIMUM_ROWS)
		return;
	
	//Usuwamy ostatni rządek z boxami
	delete layout()->takeAt(numRows - 1);
	
	//Usuwamy boxy
	for (int i = 0; i < NUM_COLUMNS; i++)
		delete boxes.takeLast();
	
	numRows--;
}

void ColorPaletteWidget::clear()
{
	setRowCount(0);
}

void ColorPaletteWidget::setRowCount(int count)
{
	if (count < 0)
		return;
	
	while (numRows < count)
		addRow();
	
	while (numRows > count)
		removeRow();
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
