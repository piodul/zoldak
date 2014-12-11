#include <SFML/Window.hpp>

#include <QtCore>

#include <map>

#include "InputAction.hpp"
#include "../InputSystem.hpp"

using namespace Zk::Game;

static const std::map<sf::Keyboard::Key, const char*> keyToName {
	{ sf::Keyboard::A,			"A" },
	{ sf::Keyboard::B,			"B" },
	{ sf::Keyboard::C,			"C" },
	{ sf::Keyboard::D,			"D" },
	{ sf::Keyboard::E,			"E" },
	{ sf::Keyboard::F,			"F" },
	{ sf::Keyboard::G,			"G" },
	{ sf::Keyboard::H,			"H" },
	{ sf::Keyboard::I,			"I" },
	{ sf::Keyboard::J,			"J" },
	{ sf::Keyboard::K,			"K" },
	{ sf::Keyboard::L,			"L" },
	{ sf::Keyboard::M,			"M" },
	{ sf::Keyboard::N,			"N" },
	{ sf::Keyboard::O,			"O" },
	{ sf::Keyboard::P,			"P" },
	{ sf::Keyboard::Q,			"Q" },
	{ sf::Keyboard::R,			"R" },
	{ sf::Keyboard::S,			"S" },
	{ sf::Keyboard::T,			"T" },
	{ sf::Keyboard::U,			"U" },
	{ sf::Keyboard::V,			"V" },
	{ sf::Keyboard::W,			"W" },
	{ sf::Keyboard::X,			"X" },
	{ sf::Keyboard::Y,			"Y" },
	{ sf::Keyboard::Z,			"Z" },
	{ sf::Keyboard::Num0,		"Numpad 0" },
	{ sf::Keyboard::Num1,		"Numpad 1" },
	{ sf::Keyboard::Num2,		"Numpad 2" },
	{ sf::Keyboard::Num3,		"Numpad 3" },
	{ sf::Keyboard::Num4,		"Numpad 4" },
	{ sf::Keyboard::Num5,		"Numpad 5" },
	{ sf::Keyboard::Num6,		"Numpad 6" },
	{ sf::Keyboard::Num7,		"Numpad 7" },
	{ sf::Keyboard::Num8,		"Numpad 8" },
	{ sf::Keyboard::Num9,		"Numpad 9" },
	{ sf::Keyboard::Escape,		"[Escape]" },
	{ sf::Keyboard::LControl,	"[Left Control]" },
	{ sf::Keyboard::LShift,		"[Left Shift]" },
	{ sf::Keyboard::LAlt,		"[Left Alt]" },
	{ sf::Keyboard::LSystem,	"[Left System]" },
	{ sf::Keyboard::RControl,	"[Right Control]" },
	{ sf::Keyboard::RShift,		"[Right Shift]" },
	{ sf::Keyboard::RAlt,		"[Right Alt]" },
	{ sf::Keyboard::RSystem,	"[Right System]" },
	{ sf::Keyboard::Menu,		"[Menu" },
	{ sf::Keyboard::LBracket,	"(" },
	{ sf::Keyboard::RBracket,	")" },
	{ sf::Keyboard::SemiColon,	";" },
	{ sf::Keyboard::Comma,		"," },
	{ sf::Keyboard::Period,		"." },
	{ sf::Keyboard::Quote,		"'" },
	{ sf::Keyboard::Slash,		"/ [Slash]" },
	{ sf::Keyboard::BackSlash,	"\\" },
	{ sf::Keyboard::Tilde,		"~" },
	{ sf::Keyboard::Equal,		"=" },
	{ sf::Keyboard::Dash,		"- [Dash]" },
	{ sf::Keyboard::Space,		"[Space]" },
	{ sf::Keyboard::Return,		"[Enter]" },
	{ sf::Keyboard::BackSpace,	"[Backspace]" },
	{ sf::Keyboard::Tab,		"[Tab]" },
	{ sf::Keyboard::PageUp,		"[PageUp]" },
	{ sf::Keyboard::PageDown,	"[PageDown]" },
	{ sf::Keyboard::End,		"[End]" },
	{ sf::Keyboard::Home,		"[Home]" },
	{ sf::Keyboard::Insert,		"[Insert]" },
	{ sf::Keyboard::Delete,		"[Delete]" },
	{ sf::Keyboard::Add,		"+" },
	{ sf::Keyboard::Subtract,	"- [Subtract]" },
	{ sf::Keyboard::Multiply,	"*" },
	{ sf::Keyboard::Divide,		"/ [Divide]" },
	{ sf::Keyboard::Left,		"[Left]" },
	{ sf::Keyboard::Right,		"[Right]" },
	{ sf::Keyboard::Up,			"[Up]" },
	{ sf::Keyboard::Down,		"[Down]" },
	{ sf::Keyboard::Numpad0,	"[Numpad0]" },
	{ sf::Keyboard::Numpad1,	"[Numpad1]" },
	{ sf::Keyboard::Numpad2,	"[Numpad2]" },
	{ sf::Keyboard::Numpad3,	"[Numpad3]" },
	{ sf::Keyboard::Numpad4,	"[Numpad4]" },
	{ sf::Keyboard::Numpad5,	"[Numpad5]" },
	{ sf::Keyboard::Numpad6,	"[Numpad6]" },
	{ sf::Keyboard::Numpad7,	"[Numpad7]" },
	{ sf::Keyboard::Numpad8,	"[Numpad8]" },
	{ sf::Keyboard::Numpad9,	"[Numpad9]" },
	{ sf::Keyboard::F1,			"[F1]" },
	{ sf::Keyboard::F2,			"[F2]" },
	{ sf::Keyboard::F3,			"[F3]" },
	{ sf::Keyboard::F4,			"[F4]" },
	{ sf::Keyboard::F5,			"[F5]" },
	{ sf::Keyboard::F6,			"[F6]" },
	{ sf::Keyboard::F7,			"[F7]" },
	{ sf::Keyboard::F8,			"[F8]" },
	{ sf::Keyboard::F9,			"[F9]" },
	{ sf::Keyboard::F10,		"[F10]" },
	{ sf::Keyboard::F11,		"[F11]" },
	{ sf::Keyboard::F12,		"[F12]" },
	{ sf::Keyboard::F13,		"[F13]" },
	{ sf::Keyboard::F14,		"[F14]" },
	{ sf::Keyboard::F15,		"[F15]" },
	{ sf::Keyboard::Pause,		"[Pause]" }
};

static const std::map<sf::Mouse::Button, const char*> mouseButtonToName {
	{ sf::Mouse::Left,			"[Mouse Left]" },
	{ sf::Mouse::Right,			"[Mouse Right]" },
	{ sf::Mouse::Middle,		"[Mouse Middle]" },
	{ sf::Mouse::XButton1,		"[Mouse XButton1]" },
	{ sf::Mouse::XButton2,		"[Mouse XButton2]" }
};

static const std::map<sf::Mouse::Button, int> mouseButtonSFMLToManyMouse {
	{ sf::Mouse::Left,			0 },
	{ sf::Mouse::Right,			1 },
	{ sf::Mouse::Middle,		2 },
	{ sf::Mouse::XButton1,		3 },
	{ sf::Mouse::XButton2,		4 }
};

const char * InputAction::getName() const
{
	if (type == Type::Key)
	{
		auto it = keyToName.find(key);
		return (it != keyToName.end()) ? it->second : "[Unknown Key]";
	}
	else
	{
		auto it = mouseButtonToName.find(mouseButton);
		return (it != mouseButtonToName.end())
				? it->second : "[Unknown Mouse Button]";
	}
}

bool InputAction::isTriggered(MouseDeviceHandle mdh) const
{
	if (type == Type::Key)
		return sf::Keyboard::isKeyPressed(key);
	else
		return mdh.isButtonPressed(mouseButtonSFMLToManyMouse.at(mouseButton));
}

QDataStream & Zk::Game::operator<<(QDataStream & ds, const InputAction & ia)
{
	ds << (qint8)ia.getType();
	if (ia.getType() == InputAction::Type::Key)
		ds << (qint32)ia.getKey();
	else
		ds << (qint32)ia.getMouseButton();

	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, InputAction & ia)
{
	qint8 type;
	qint32 param;

	ds >> type;
	ds >> param;

	if ((InputAction::Type)type == InputAction::Type::Key)
		ia = InputAction((sf::Keyboard::Key)param);
	else
		ia = InputAction((sf::Mouse::Button)param);

	return ds;
}
