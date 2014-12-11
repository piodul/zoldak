#pragma once

#include <QtCore>

#include <SFML/Window.hpp>

namespace Zk {
namespace Game {

class GraphicsConfig
{
public:
	GraphicsConfig();

	friend QDataStream & operator<<(QDataStream & ds, const GraphicsConfig & gc);
	friend QDataStream & operator>>(QDataStream & ds, GraphicsConfig & gc);

	sf::VideoMode videoMode;
	bool fullscreen;
};

QDataStream & operator<<(QDataStream & ds, const GraphicsConfig & gc);
QDataStream & operator>>(QDataStream & ds, GraphicsConfig & gc);

}}
