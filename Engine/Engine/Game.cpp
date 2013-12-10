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

	Window* window = new Window(NULL, kernel->GetWindowManager());
	// Window registration test
	if(kernel->GetWindowManager()->RegisterWindow(window))
	{
		logger->Log("Window created");
		if(kernel->GetWindowManager()->RegisterWindow(window))
		{
			logger->Log(LogLevel::WARNING, "Registered same window twice!");
		}
		else
		{
			logger->Log(LogLevel::WARNING, "Window is already registered!");
			Window* window2 = new Window(NULL, kernel->GetWindowManager());
			if(kernel->GetWindowManager()->RegisterWindow(window2))
			{
				logger->Log(LogLevel::INFO, "Registered new window successfully!");
			}
		}
	}
	else
	{
		logger -> Log(LogLevel::WARNING, "Could not create Window!");
	}

	kernel->GetResourceManager()->LoadTexture(L"");
	kernel->GetResourceManager()->LoadHeightmap(L"");
	//kernel->GetResourceManager()->LoadModel(L"");

	kernel->Start();
	return 0;
}