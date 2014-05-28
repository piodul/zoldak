#pragma once

namespace Zk {
namespace Game {

class GameSystem;

class Game
{
public:
	Game(GameSystem & gameSys);
	~Game();
	
	
	
private:
	GameSystem & gameSys;
	
};

}}
