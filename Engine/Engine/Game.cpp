#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "ResourceManager.h"

//includes for input
#include "InputMouse.h"
#include "InputKeyboard.h"
#include <iostream>

//TMP for loading a game
#include "Terrain.h"
#include "ResourceHeightmap.h"
#include "ResourceTexture.h"
#include "Scene.h"
#include "ResourceModel.h"
#include "EntityModel.h"

int main()
{
	Game* game = new Game();
	return game->Main();
}

int Game::Main()
{
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Starting up");
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Creating Kernel");
	kernel = new Kernel();

	Window* window = new Window(NULL, kernel->GetWindowManager(), 1024, 576, "Engine");
	// Window registration test
	if(kernel->GetWindowManager()->RegisterWindow(window))
	{
		LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Window registered");
		LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Adding Renderer (DX9)");
		Renderer* renderer = new DXRenderer();
		window->SetRenderer(renderer);
		window->GetRenderer()->Init(window);
		initgame(kernel, window);
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Could not create Window!");
	}

	kernel->Start();
	return 0;
}

void Game::initgame(Kernel* kernel, Window* window ){
	
	Scene* scene = new Scene();
	Terrain* ter = new Terrain();
	ResourceHeightmap* heightmap = kernel->GetResourceManager()->GetHeightmap("heightmap.bmp", window->GetRenderer()->GetDevice());
	ter->SetHeightmap(heightmap);
	ter->SetTexture(ResourceManager::Instance()->GetTexture("heightmap-texture.png", window->GetRenderer()->GetDevice()));
	scene->SetTerrain(ter);
	
	for (int z = 10; z > 0; --z){   
		for (int i = 2; i > 0; --i){   
			ResourceModel* rmodel = kernel->GetResourceManager()->GetModel("tiger.x", window->GetRenderer()->GetDevice());
	
			Matrix location;
			location.x = ((float)i * 20) - 150;
			location.z =  ((float)z * 20) - 150;
			location.y = 150;
			location.rotation_v = (float)i * 100;
			location.rotation_h = 0;
			location.scale = 10;

			EntityModel* model = new EntityModel();
			model->SetModel(rmodel);
			model->SetPosition(location);
			scene->AddModel(model);
		}
	}
	
	window->GetManager()->RegisterScene(window, scene);
}
