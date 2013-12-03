#include "Kernel.h"

Kernel::Kernel()
{
	Initialise();
}

Kernel::~Kernel()
{
	Cleanup();
}

void Kernel::Initialise()
{
	LogManager::Instance()->Log("Initializing Kernel");
	winMan = new WindowManager();
	/*resMan = new ResourceManager();
	sceneMan = new SceneManager();*/
	LogManager::Instance()->Log("Kernel Initialized");
}

void Kernel::Cleanup()
{
	LogManager::Instance()->Log("Cleaning up Kernel");
	winMan->Cleanup();
	delete winMan;
	/*resMan->Cleanup();
	delete resMan;
	sceneMan->Cleanup();
	delete sceneMan;*/
	LogManager::Instance()->Log("Kernel cleaned");
}

ResourceManager* Kernel::GetResourceManager()
{
	return resMan;
}

WindowManager* Kernel::GetWindowManager()
{
	return winMan;
}

SceneManager* Kernel::GetSceneManager()
{
	return sceneMan;
}