#include "Game.h"

int main()
{
	Game* game = new Game();
	return game->Main();
}

int Game::Main()
{
	logger = LogManager::Instance();
	logger->Log("Starting up");
	
	logger->Log("Creating Kernel");
	kernel = new Kernel();

	if(kernel->GetWindowManager()->CreateWnd())
	{
		logger->Log("Window created");
		while(kernel->GetWindowManager()->GetNumWindows() != 0)
		{
			
		}
	}
	else
	{
		logger -> Log(LogLevel::WARNING, "Could not create Window!");
	}

	return 0;
}