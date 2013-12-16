#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"

int main()
{
	Game* game = new Game();
	return game->Main();
}

int Game::Main()
{
	LogManager::Instance()->Log("Starting up");
	LogManager::Instance()->Log("Creating Kernel");
	kernel = new Kernel();

	Window* window = new Window(NULL, kernel->GetWindowManager());
	// Window registration test
	Renderer* renderer = new DXRenderer();
	window->SetRenderer(renderer);
	

	if(kernel->GetWindowManager()->RegisterWindow(window))
	{
		LogManager::Instance()->Log("Window created");
		
		while (1==1)
		{
			window->GetRenderer()->Render();
		}

		if(kernel->GetWindowManager()->RegisterWindow(window))
		{
			LogManager::Instance()->Log(LogLevel::WARNING, "Registered same window twice!");
		}
		else
		{
			LogManager::Instance()->Log(LogLevel::WARNING, "Window is already registered!");
			Window* window2 = new Window(NULL, kernel->GetWindowManager());
			if(kernel->GetWindowManager()->RegisterWindow(window2))
			{
				LogManager::Instance()->Log(LogLevel::INFO, "Registered new window successfully!");
			}
		}
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Could not create Window!");
	}

	//kernel->GetResourceManager()->LoadTexture(L"");
	kernel->GetResourceManager()->LoadHeightmap(L"heightmap.bmp");
	//kernel->GetResourceManager()->LoadModel(L"");

	kernel->Start();
	return 0;
}