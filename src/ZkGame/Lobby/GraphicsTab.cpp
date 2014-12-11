#include <QtCore>
#include <QtGui>

#include <SFML/Window.hpp>

#include <vector>

#include "../Config/Config.hpp"
#include "../Config/GraphicsConfig.hpp"
#include "GraphicsTab.hpp"

using namespace Zk::Game;

GraphicsTab::GraphicsTab(Config & config, QWidget * parent)
	: QWidget(parent), config(config)
{
	QLabel * resolutionsLabel = new QLabel("Screen resolution:");

	resolutionsBox = new QComboBox();
	resolutionsBox->setEditable(false);
	populateResolutionsBox();
	connect(resolutionsBox, SIGNAL(currentIndexChanged(int)),
			this, SLOT(changeResolution(int)));

	fullscreenBox = new QCheckBox("Fullscreen mode");
	fullscreenBox->setCheckState(
		config.graphicsConfig.fullscreen ? Qt::Checked : Qt::Unchecked
	);
	connect(fullscreenBox, SIGNAL(toggled(bool)),
			this, SLOT(changeFullscreenOption(bool)));

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

void GraphicsTab::changeResolution(int index)
{
	const std::vector<sf::VideoMode> & modes = sf::VideoMode::getFullscreenModes();
	config.graphicsConfig.videoMode = modes[index];
}

void GraphicsTab::changeFullscreenOption(bool full)
{
	config.graphicsConfig.fullscreen = full;
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

	for (int i = 0; i < resolutionsBox->count(); i++)
	{
		if (config.graphicsConfig.videoMode == modes[i])
		{
			resolutionsBox->setCurrentIndex(i);
			break;
		}
	}
}
