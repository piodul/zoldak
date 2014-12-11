#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Zk {
namespace Game {

class MouseDeviceHandle;

struct mouseInfo_t
{
	mouseInfo_t();

	sf::Vector3i absolutePos;
	sf::Vector3i relativePos;
	int buttons;
	bool connected;
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void pollInput();
	void resetMice();
	MouseDeviceHandle getMouseDeviceHandle(int mouseID) const;
	int getMiceCount() const;

private:
	void initManyMouse();
	void quitManyMouse();

	std::shared_ptr<int> token;
	std::vector<mouseInfo_t> mouseInfos;

	bool manyMouseInitialized;
};

class MouseDeviceHandle
{
public:
	MouseDeviceHandle();
	MouseDeviceHandle(std::weak_ptr<int> token, const mouseInfo_t * info);
	~MouseDeviceHandle();

	bool isValid() const;
	bool isConnected() const;

	sf::Vector3i getAbsolutePosition() const;
	sf::Vector3i getRelativePosition() const;

	bool isButtonPressed(int btn) const;

private:
	std::weak_ptr<int> token;

	const mouseInfo_t * info;
};

}}
