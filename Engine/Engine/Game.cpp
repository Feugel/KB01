#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "ResourceManager.h"

//TMP for loading a heightmap
#include "Terrain.h"
#include "ResourceHeightmap.h"
#include "ResourceTexture.h"
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
		initheightmap(kernel, window);
		window->SetRenderer(renderer);
		

		window->GetRenderer()->Init(window);
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Could not create Window!");
	}

	kernel->Start();
	return 0;
}

void Game::initheightmap(Kernel* kernal, Window* window ){
	
	Scene* scene = new Scene();
	Terrain* ter = new Terrain();
	ResourceHeightmap* heightmap = kernel->GetResourceManager()->GetHeightmap("heightmap.bmp");
	ter->SetHeightmap(heightmap);
//	ResourceTexture* texture = kernal->GetResourceManager()->GetTexture("heightmap.bmp");
//	ter->SetTexture(texture);
	scene->SetTerrain(ter);
	window->GetManager()->RegisterScene(window, scene);
}
