#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "Window.h"
#include "ResourceManager.h"

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
	if(kernel->GetWindowManager()->RegisterWindow(window))
	{
		LogManager::Instance()->Log("Window registered");
		LogManager::Instance()->Log("Adding Renderer (DX9)");
		Renderer* renderer = new DXRenderer();
		window->SetRenderer(renderer);
		window->GetRenderer()->Init(window->GetWindowHandle());
		renderer->InitHeightMap(kernel->GetResourceManager()->GetHeightmap(L"heightmap.bmp"));
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Could not create Window!");
	}
	
	//kernel->GetResourceManager()->GetTexture(L"");
	kernel->GetResourceManager()->GetHeightmap(L"heightmap.bmp");
	//kernel->GetResourceManager()->GetModel(L"");

	kernel->Start();
	return 0;
}