#include <QtCore>

#include <SFML/Window.hpp>

#include "GraphicsConfig.hpp"

using namespace Zk::Game;

GraphicsConfig::GraphicsConfig()
{
	videoMode = sf::VideoMode::getDesktopMode();
	fullscreen = false;
}

QDataStream & Zk::Game::operator<<(QDataStream & ds, const GraphicsConfig & gc)
{
	quint32 w = gc.videoMode.width;
	quint32 h = gc.videoMode.height;
	quint32 bpp = gc.videoMode.bitsPerPixel;

	ds << w << h << bpp << gc.fullscreen;

	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, GraphicsConfig & gc)
{
	quint32 w, h, bpp;
	ds >> w >> h >> bpp >> gc.fullscreen;

	gc.videoMode = sf::VideoMode(w, h, bpp);

	return ds;
}
