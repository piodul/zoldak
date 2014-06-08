#pragma once

#include <array>

namespace Zk {
namespace Game {

class InputConfig;

class Config
{
public:
	Config();
	~Config();
	
	std::array<InputConfig*, 2> playerInputConfig;
};

}}
