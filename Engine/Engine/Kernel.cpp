#include "Kernel.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LogManager.h"

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
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Initializing Kernel");
	winMan = WindowManager::Instance();
	winMan->SetKernel(this);
	resMan = ResourceManager::Instance();
	sceneMan = SceneManager::Instance();
	inputMan = InputManager::Instance();
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Kernel Initialized");
}

void Kernel::Cleanup()
{
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Cleaning up Kernel");
	winMan->Cleanup();
	resMan->Cleanup();
	sceneMan->Cleanup();
	inputMan->Cleanup();
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Kernel cleaned");
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
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Starting Kernel functions");
	isFinished = false;
	MSG msg;
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Starting Game Loop");
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
				case WM_KEYDOWN:		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_KEYDOWN"); break;	// handle input on this?
				case WM_KEYUP:			LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_KEYUP"); break;		// handle input on this?
				case WM_SIZE:			LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_SIZE"); break;
				case WM_ENTERSIZEMOVE:	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_ENTERSIZEMOVE"); break;
				case WM_INPUT:			LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_INPUT"); break;
				case WM_LBUTTONDOWN:	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_LBUTTONDOWN"); break;
				case WM_LBUTTONUP:		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_LBUTTONUP"); break;
				case WM_RBUTTONDOWN:	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_RBUTTONDOWN"); break;
				case WM_RBUTTONUP:		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_RBUTTONUP"); break;
				case WM_MOUSEHWHEEL:	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_MOUSEHWHEEL"); break;
				case WM_MOUSEWHEEL:		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_MOUSEWHEEL"); break;
				case WM_SIZING:			LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Caught message: WM_SIZING"); break;
			}
			/* Translate virtual-key messages into character messages */
			TranslateMessage(&msg);
			/* Send message to WindowProcedure */
			DispatchMessage(&msg);
		}
		//LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Running Kernel::Update");
		this->Update(timer); // make calls to all manager's 'Update' functions
		//LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Kernel::Update done");
		
		//LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Running Kernel::Render");
		this->Render(); // make calls to necessary manager's 'Render' functions
		//LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Kernel::Render done");

	}
	while(WM_QUIT != msg.message && !this->isFinished);
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Kernel stopping.");
	timer->Stop();
	// clean up
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Calling Cleanup");
	this->Cleanup();
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Cleanup done. Bye-bye!");
}

void Kernel::Stop()
{
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Stopping Kernel");
	isFinished = true;
}

void Kernel::Update(Timer* timer)
{
	sceneMan->Update(timer);
	inputMan->Update();
}

void Kernel::Render()
{
	winMan->Render();
}