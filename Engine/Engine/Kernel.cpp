#include "Kernel.h"
#include <sstream>

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
	ZeroMemory(&resMan, sizeof(*resMan));
	//ZeroMemory(&sceneMan, sizeof(*sceneMan));
	winMan = new WindowManager();
	resMan = new ResourceManager();
	/*sceneMan = new SceneManager();*/
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
	MSG msg;
	LogManager::Instance()->Log("Starting Game Loop");
	do
	{
		// Windows message loop; catches ALL MESSAGES right now. Should probably only catch WM_CLOSE, WM_DESTROY and WM_QUIT?
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			LogManager::Instance()->Log(msg.message);
			if(161 == msg.message) // for some reason WM_CLOSE does not work here
			{
				this->GetWindowManager()->ReleaseWindow(msg.hwnd);
			}
			/* Translate virtual-key messages into character messages */
			TranslateMessage(&msg);
			/* Send message to WindowProcedure */
			DispatchMessage(&msg);
		}
		//LogManager::Instance()->Log(GetWindowManager()->GetWindows().size());
		//LogManager::Instance()->Log("Running Kernel::Update");
		this->Update(); // make calls to all manager's 'Update' functions
		//LogManager::Instance()->Log("Kernel::Update done");
		//LogManager::Instance()->Log("Running Kernel::Render");
		//this->Render(); // make calls to necessary manager's 'Render' functions
		
		//LogManager::Instance()->Log("Kernel::Render done");
	}
	while(WM_QUIT != msg.message && !this->isFinished);
}

void Kernel::Stop()
{
	LogManager::Instance()->Log("Stopping Kernel");
	isFinished = true;
}

void Kernel::Update()
{

}