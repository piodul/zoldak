#include <SFML/Graphics.hpp>
#include "../ManyMouse/manymouse.h"

#include "InputSystem.hpp"

#include <QDebug>

using namespace Zk::Game;

static const int TOKEN_NUMBER = 2 * 3 * 7;

mouseInfo_t::mouseInfo_t()
{
	absolutePos = sf::Vector3i(0, 0, 0);
	relativePos = sf::Vector3i(0, 0, 0);
	buttons = 0;
	connected = false;
}

InputSystem::InputSystem()
{
	manyMouseInitialized = false;
	initManyMouse();
}

InputSystem::~InputSystem()
{
	quitManyMouse();
}

void InputSystem::pollInput()
{
	ManyMouseEvent mme;

	for (mouseInfo_t & mouse : mouseInfos)
		mouse.relativePos = sf::Vector3i();

	while (ManyMouse_PollEvent(&mme))
	{
		mouseInfo_t & currMouse = mouseInfos[mme.device];

		switch (mme.type)
		{
		case MANYMOUSE_EVENT_ABSMOTION:
			if (mme.item == 0)
			{
				currMouse.relativePos.y += mme.value - currMouse.absolutePos.x;
				currMouse.absolutePos.x = mme.value;
			}
			else if (mme.item == 1)
			{
				currMouse.relativePos.y += mme.value - currMouse.absolutePos.y;
				currMouse.absolutePos.y = mme.value;
			}
			break;

		case MANYMOUSE_EVENT_RELMOTION:
			if (mme.item == 0)
			{
				currMouse.relativePos.x += mme.value;
				currMouse.absolutePos.x += mme.value;
			}
			else if (mme.item == 1)
			{
				currMouse.relativePos.y += mme.value;
				currMouse.absolutePos.y += mme.value;
			}
			break;

		case MANYMOUSE_EVENT_BUTTON:
			if (mme.value)
				currMouse.buttons |= 1 << mme.item;
			else
				currMouse.buttons &= ~(1 << mme.item);
			break;

		case MANYMOUSE_EVENT_SCROLL:
			currMouse.relativePos.z += (mme.value > 0) ? 1 : -1;
			currMouse.absolutePos.z += (mme.value > 0) ? 1 : -1;
			break;

		case MANYMOUSE_EVENT_DISCONNECT:
			currMouse.connected = false;
			qDebug() << "Mouse no." << mme.device << "disconnected!";
			break;

		case MANYMOUSE_EVENT_MAX:
			//Impossibru
			break;

		}
	}
}

void InputSystem::resetMice()
{
	quitManyMouse();
	initManyMouse();
}

MouseDeviceHandle InputSystem::getMouseDeviceHandle(int mouseID) const
{
	if (0 <= mouseID && mouseID < getMiceCount())
		return MouseDeviceHandle(token, &mouseInfos[mouseID]);
	else
		return MouseDeviceHandle(std::weak_ptr<int>(), nullptr);
}

int InputSystem::getMiceCount() const
{
	return mouseInfos.size();
}

void InputSystem::initManyMouse()
{
	if (manyMouseInitialized)
		return;

	int mouseCount = ManyMouse_Init();

	if (mouseCount > 0)
	{
		qDebug() << "Found" << mouseCount << "mouse devices";
		qDebug() << "Driver:" << ManyMouse_DriverName();

		mouseInfos.reserve(mouseCount);
		for (int i = 0; i < mouseCount; i++)
		{
			qDebug() << "Mouse no." << i;
			qDebug() << " " << ManyMouse_DeviceName(i);

			mouseInfo_t mit;
			mit.connected = true;
			mouseInfos.push_back(mit);
		}

		token = std::make_shared<int>(TOKEN_NUMBER);
		manyMouseInitialized = true;
	}
	else
		qDebug() << "No mice found!";
}

void InputSystem::quitManyMouse()
{
	if (!manyMouseInitialized)
		return;

	ManyMouse_Quit();
	token = nullptr;
	manyMouseInitialized = false;
}

MouseDeviceHandle::MouseDeviceHandle()
{
	this->token = std::shared_ptr<int>();
	this->info = nullptr;
}

MouseDeviceHandle::MouseDeviceHandle(
	std::weak_ptr<int> token,
	const mouseInfo_t * info
)
{
	this->token = token;
	this->info = info;
}

MouseDeviceHandle::~MouseDeviceHandle()
{

}

bool MouseDeviceHandle::isValid() const
{
	return !token.expired();
}

bool MouseDeviceHandle::isConnected() const
{
	if (token.expired())
		return false;

	return info->connected;
}

sf::Vector3i MouseDeviceHandle::getAbsolutePosition() const
{
	if (token.expired())
		return sf::Vector3i();

	return info->absolutePos;
}

sf::Vector3i MouseDeviceHandle::getRelativePosition() const
{
	if (token.expired())
		return sf::Vector3i();

	return info->relativePos;
}

bool MouseDeviceHandle::isButtonPressed(int btn) const
{
	if (token.expired())
		return false;

	return (info->buttons & (1 << btn)) != 0;
}
