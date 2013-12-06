#include "Kernel.h"

Kernel::Kernel()
{
	Initialise();
	////Quick Thought: make all Managers inherit from a base class 'Manager', so we can keep a set of them around (Map<identifier, Manager> ?)and make them implement basic methods like Update / Render?
}

Kernel::~Kernel()
{
	Cleanup();
}

void Kernel::Initialise()
{
	LogManager::Instance()->Log("Initializing Kernel");
	ZeroMemory(&winMan, sizeof(*winMan));
	//ZeroMemory(&resMan, sizeof(*resMan));
	//ZeroMemory(&sceneMan, sizeof(*sceneMan));
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

void Kernel::Start()
{
	LogManager::Instance()->Log("Starting Kernel functions");
	isFinished = false;
	do {
		LogManager::Instance()->Log("Running Kernel::Update");
		this->Update(); // make calls to all manager's 'Update' functions
		LogManager::Instance()->Log("Kernel::Update done");
		//LogManager::Instance()->Log("Running Kernel::Render");
		//this->Render(); // make calls to necessary manager's 'Render' functions
		//LogManager::Instance()->Log("Kernel::Render done");
	}
	while(!this->isFinished);
}

void Kernel::Stop()
{
	LogManager::Instance()->Log("Stopping Kernel");
	isFinished = true;
}

void Kernel::Update()
{

}