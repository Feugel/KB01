#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

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

//THE main method that creates a new Game
int main()
{
	Game* game = new Game();
	return game->Main();
}

//Main method from Game that creates a new Kernel. 
//This also creates a new Window in which the renderer will be made shortly after.
//All these steps will be logged and taken care of by the LogManager.
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

//The initgame method receives a kernel and a window. 
//A new scene gets loaded and the method LoadScene loads a .xml file and renders this in the current window.
void Game::initgame(Kernel* kernel, Window* window )
{
	Scene* scene = kernel->GetSceneManager()->LoadScene("level01.xml", window->GetRenderer());
	window->GetManager()->RegisterScene(window, scene);
}
