#include "GameSystem.h"

#include "Lobby/LobbyWindow.h"

using namespace Zk::Game;

int main(int argc, char ** argv)
{
	GameSystem gs(argc, argv);
	
	LobbyWindow lw;
	lw.show();
	
	return gs.exec();
}
