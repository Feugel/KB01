#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "ResourceManager.h"

//TMP for loading a heightmap
#include "Terrain.h"
#include "ResourceHeightmap.h"
#include "Scene.h"

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
		initheightmap(kernel, window);

		window->GetRenderer()->Init(window);
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Could not create Window!");
	}
	
	//kernel->GetResourceManager()->GetTexture(L"");
	
	//kernel->GetResourceManager()->GetModel(L"");

	kernel->Start();
	return 0;
}

void Game::initheightmap(Kernel* kernal, Window* window ){
	
	Scene* scene = new Scene();
	Terrain* ter = new Terrain();
	ter->SetHeightmap( kernel->GetResourceManager()->GetHeightmap(L"heightmap.bmp") );
	scene->SetTerrain(ter);
	window->GetManager()->RegisterScene(window, scene);
}
