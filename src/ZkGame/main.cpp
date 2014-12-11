#include "GameSystem.hpp"

using namespace Zk::Game;

int main(int argc, char ** argv)
{
	GameSystem gs(argc, argv);

	return gs.exec();
}
