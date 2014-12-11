#pragma once

#include <QtCore>

#include <SFML/Window.hpp>

#include <map>

#include "../InputSystem.hpp"

namespace Zk {
namespace Game {

class InputAction
{
public:
	enum class Type : char
	{
		Key,
		MouseButton
	};

	inline InputAction()
		: type(Type::Key), key(sf::Keyboard::Unknown)
	{}

	inline InputAction(sf::Keyboard::Key sfmlKey)
		: type(Type::Key), key(sfmlKey)
	{}
	inline InputAction(sf::Mouse::Button sfmlMouseButton)
		: type(Type::MouseButton), mouseButton(sfmlMouseButton)
	{}

	inline Type getType() const
	{ return type; }
	inline sf::Keyboard::Key getKey() const
	{ return key; }
	inline sf::Mouse::Button getMouseButton() const
	{ return mouseButton; }

	inline bool operator==(const InputAction & other)
	{
		if (type != other.type)
			return false;

		if (type == Type::Key)
			return key == other.key;
		else //type == MouseButton
			return mouseButton == other.mouseButton;
	}

	const char * getName() const;
	bool isTriggered(MouseDeviceHandle mdh) const;

private:
	Type type;
	union
	{
		sf::Keyboard::Key key;
		sf::Mouse::Button mouseButton;
	};
};

QDataStream & operator<<(QDataStream & ds, const InputAction & ia);
QDataStream & operator>>(QDataStream & ds, InputAction & ia);

}}
