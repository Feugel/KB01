#include "Game.h"
#include "Renderer.h"
#include "DXRenderer.h"
#include "WindowManager.h"
#include "ResourceManager.h"

//includes for input
#include "InputMouse.h"
#include "InputKeyboard.h"
#include <iostream>

//TMP for loading a heightmap
#include "Terrain.h"
#include "ResourceHeightmap.h"
#include "ResourceTexture.h"
#include "Scene.h"

int main()
{
	Game* game = new Game();
	return game->Main();

	InputKeyboard* keyboard = new InputKeyboard(GetConsoleWindow());
	InputMouse* mouse = new InputMouse(GetConsoleWindow());

	bool init = keyboard ->InitKeyboard();
	bool mouseinit = mouse ->InitMouse();

	if (!init || !mouseinit)
		std::cout << "Init fout" << std::endl;

	keyboard ->DoAcquire();
	mouse->DoAcquire();

	bool stop = false;

	while (!stop)
	{
		if (keyboard->ProcessKBInput(DIK_Q))
		{
			std::cout << "Quit" << std::endl;
			stop = true;
		}

		if (keyboard->ProcessKBInput(DIK_W))
		{
			std::cout << "W was pressed" << std::endl;
		}

		if (keyboard->ProcessKBInput(DIK_S))
		{
			std::cout << "S was pressed" << std::endl;
		}

		if (keyboard->ProcessKBInput(DIK_D))
		{
			std::cout << "D was pressed" << std::endl;
		}

		if (keyboard->ProcessKBInput(DIK_A))
		{
			std::cout << "A was pressed" << std::endl;
		}

	MouseStruct ms = mouse->GetMouseInput();
	if (ms.button0 == true)
	{ 
		std::cout << "mouse btn0 was pressed" << std::endl;
		//if (ms.positionX == true)
		std::cout << "mouse x pos: " << ms.positionX << std::endl;
		std::cout << "mouse y pos: " << ms.positionY << std::endl;
	} 
	if (ms.button1 == true)
	{ 
		std::cout << "mouse btn0 was pressed" << std::endl;
		std::cout << "mouse x pos: " << ms.positionX << std::endl;
		std::cout << "mouse y pos: " << ms.positionY << std::endl;
	} 
	if (ms.button2 == true)
	{ 
		std::cout << "mouse btn0 was pressed" << std::endl;
		std::cout << "mouse x pos: " << ms.positionX << std::endl;
		std::cout << "mouse y pos: " << ms.positionY << std::endl;
	} 
	}




}

int Game::Main()
{
	LogManager::Instance()->Log("%s", "Starting up");
	LogManager::Instance()->Log("%s", "Creating Kernel");
	kernel = new Kernel();

	Window* window = new Window(NULL, kernel->GetWindowManager());
	// Window registration test
	if(kernel->GetWindowManager()->RegisterWindow(window))
	{
		LogManager::Instance()->Log("%s", "Window registered");
		LogManager::Instance()->Log("%s", "Adding Renderer (DX9)");
		Renderer* renderer = new DXRenderer();
		window->SetRenderer(renderer);
		window->GetRenderer()->Init(window);
		initheightmap(kernel, window);
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not create Window!");
	}

	kernel->Start();
	return 0;
}

void Game::initheightmap(Kernel* kernal, Window* window ){
	
	Scene* scene = new Scene();
	Terrain* ter = new Terrain();
	ResourceHeightmap* heightmap = kernel->GetResourceManager()->GetHeightmap("heightmap2.bmp");
	ter->SetHeightmap(heightmap);
	ter->SetTexture(ResourceManager::Instance()->GetTexture("heightmap-texture.png", window->GetRenderer()->GetDevice()));
//	ResourceTexture* texture = kernal->GetResourceManager()->GetTexture("heightmap.bmp");
//	ter->SetTexture(texture);
	scene->SetTerrain(ter);
	window->GetManager()->RegisterScene(window, scene);
}
