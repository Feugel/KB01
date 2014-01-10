#include "Kernel.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"

Kernel::Kernel()
{
	Initialise();
}

Kernel::~Kernel()
{
	Cleanup();
	delete winMan;
	delete resMan;
	delete sceneMan;
}

void Kernel::Initialise()
{
	LogManager::Instance()->Log("Initializing Kernel");
	ZeroMemory(&winMan, sizeof(*winMan));
	ZeroMemory(&resMan, sizeof(*resMan));
	ZeroMemory(&sceneMan, sizeof(*sceneMan));
	//ZeroMemory(&inputMan, sizeof(*inputMan));
	winMan = new WindowManager(this);
	resMan = new ResourceManager();
	sceneMan = new SceneManager();
	//inputMan = new InputManager();
	LogManager::Instance()->Log("Kernel Initialized");
}

void Kernel::Cleanup()
{
	LogManager::Instance()->Log("Cleaning up Kernel");
	winMan->Cleanup();
	resMan->Cleanup();
	sceneMan->Cleanup();
	//inputMan->Cleanup();
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

InputManager* Kernel::GetInputManager()
{
	return inputMan;
}

void Kernel::Start()
{
	LogManager::Instance()->Log("Starting Kernel functions");
	isFinished = false;
	MSG msg;
	LogManager::Instance()->Log("Starting Game Loop");
	Timer* timer = new Timer();
	timer->Start();
	do
	{
		// Windows message loop; catches ALL MESSAGES right now.
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			// WM_CLOSE is handled in the WindowProcedure; it is NOT sent like a 'regular' message.
			switch(msg.message)
			{
				case WM_KEYDOWN:		LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_KEYDOWN"); break;	// handle input on this?
				case WM_KEYUP:			LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_KEYUP"); break;		// handle input on this?
				case WM_SIZE:			LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_SIZE"); break;
				case WM_ENTERSIZEMOVE:	LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_ENTERSIZEMOVE"); break;
				case WM_INPUT:			LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_INPUT"); break;
				case WM_LBUTTONDOWN:	LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_LBUTTONDOWN"); break;
				case WM_LBUTTONUP:		LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_LBUTTONUP"); break;
				case WM_RBUTTONDOWN:	LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_RBUTTONDOWN"); break;
				case WM_RBUTTONUP:		LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_RBUTTONUP"); break;
				case WM_MOUSEHWHEEL:	LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_MOUSEHWHEEL"); break;
				case WM_MOUSEWHEEL:		LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_MOUSEWHEEL"); break;
				case WM_SIZING:			LogManager::Instance()->Log(LogLevel::INFO, "Caught message: WM_SIZING"); break;
			}
			/* Translate virtual-key messages into character messages */
			TranslateMessage(&msg);
			/* Send message to WindowProcedure */
			DispatchMessage(&msg);
		}
		//LogManager::Instance()->Log("Running Kernel::Update");
		this->Update(timer); // make calls to all manager's 'Update' functions
		//LogManager::Instance()->Log("Kernel::Update done");
		
		//LogManager::Instance()->Log("Running Kernel::Render");
		this->Render(); // make calls to necessary manager's 'Render' functions
		//LogManager::Instance()->Log("Kernel::Render done");

	}
	while(WM_QUIT != msg.message && !this->isFinished);
	timer->Stop();
	// clean up
	this->Cleanup();
}

void Kernel::Stop()
{
	LogManager::Instance()->Log("Stopping Kernel");
	isFinished = true;
}

void Kernel::Update(Timer* timer)
{
	sceneMan->Update(timer);
	
}

void Kernel::Render()
{
	winMan->Render();
}