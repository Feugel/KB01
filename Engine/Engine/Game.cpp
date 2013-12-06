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
	// does not reach the next line...
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

	MSG msg;
	/* Run the message loop. It will run until GetMessage() returns 0 */
	LogManager::Instance()->Log("Starting Message Loop");
	while(GetMessage(&msg, 0, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&msg);
		/* Send message to WindowProcedure */
		DispatchMessage(&msg);
	}

	return 0;
}