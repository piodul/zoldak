#include <QtCore>
#include <QtGui>

#include <SFML/Window.hpp>

#include <vector>

#include "GraphicsTab.h"

using namespace Zk::Game;

GraphicsTab::GraphicsTab(QWidget * parent)
	: QWidget(parent)
{
	QLabel * resolutionsLabel = new QLabel("Screen resolution:");
	
	resolutionsBox = new QComboBox();
	resolutionsBox->setEditable(false);
	populateResolutionsBox();
	
	fullscreenBox = new QCheckBox("Fullscreen mode");
	
	QVBoxLayout * mainLayout = new QVBoxLayout();
	mainLayout->addWidget(resolutionsLabel);
	mainLayout->addWidget(resolutionsBox);
	mainLayout->addWidget(fullscreenBox);
	mainLayout->addStretch();
	
	this->setLayout(mainLayout);
}

GraphicsTab::~GraphicsTab()
{
	
}

void GraphicsTab::populateResolutionsBox()
{
	while (resolutionsBox->count() > 0)
		resolutionsBox->removeItem(0);
	
	const std::vector<sf::VideoMode> & modes = sf::VideoMode::getFullscreenModes();
	for (const sf::VideoMode vm : modes)
	{
		QString itemText = QString("%1x%2, %3bpp")
			.arg(vm.width).arg(vm.height).arg(vm.bitsPerPixel);
		
		QList<QVariant> values {
			vm.width, vm.height, vm.bitsPerPixel
		};
		
		resolutionsBox->addItem(itemText, values);
	}
}
