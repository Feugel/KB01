#include "Game.h"

int Game::Main()
{
	logger = LogManager::Instance();
	logger->Log("Starting up");
	
	logger->Log("Creating Kernel");
	kernel = new Kernel();



	return 0;
}