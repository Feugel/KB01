#include "InputManager.h"
#include "LogManager.h"
#include "InputObserver.h"

InputManager* InputManager::inputManager = NULL;

//Creates the keyboard and mouse so they can get initialized and updated later
InputKeyboard* keyboard = new InputKeyboard(GetConsoleWindow());
InputMouse* mouse = new InputMouse(GetConsoleWindow());

//Constructor for InputManager
InputManager::InputManager()
{
	Initialize();
}

//Destructor for InputManager
InputManager::~InputManager()
{
	Cleanup();
	if(NULL != inputManager)
		delete inputManager;
}

void InputManager::Cleanup()
{
	keyboard->SaveReleaseDevice();
	mouse->SaveReleaseDevice();
	
}

InputManager* InputManager::Instance()
{
	if(NULL == inputManager)
		inputManager = new InputManager();
	return inputManager;
}

//Initialize input
void InputManager::Initialize()
{
	bool keyboardinit = keyboard ->InitKeyboard();
	bool mouseinit = mouse ->InitMouse();

	if (!keyboardinit || !mouseinit)
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to initialize input");
	else
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Input initialized");
}

//Update inputs
void InputManager::Update()
{
	bool keyboardacquire = keyboard->DoAcquire();
	bool mouseacquire = mouse->DoAcquire();
	if (!keyboardacquire || !mouseacquire)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to acquire input");
		return;
	}	
	else
	{
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Input acquired");
		char* keyBuffer = keyboard->getKeyBuffer();
		MouseStruct mouseStruct = mouse->GetMouseInput();
		NotifyObservers(mouseStruct, keyBuffer );
		mouse->ResetMouseStruct();
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Input updated, observers notified");
	}
	
}
//this method adds an observer to the vector of observers
bool InputManager::AddObserver( InputObserver* observer )
{
	std::vector<InputObserver*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	//Return false if the observer is already in the vector. This is not expected. But there is nothing really wrong either
	if ( temp != m_ObserverVec.end() )
	{
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "InputObserver is already in the vector");
		return false;
	}
	else
	{
	m_ObserverVec.push_back(observer);
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "InputObserver added to vector");
	return true;
	}
	
}

//This method removes an observer from the vector
bool InputManager::RemoveObserver( InputObserver* observer )
{
	std::vector<InputObserver*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	//Return false if the observer could not be found (and evidently can’t be removed.
	if ( temp == m_ObserverVec.end() )
	{
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "InputObserver could not be found");
		return false;
	}
	else
	{
		m_ObserverVec.erase(remove(m_ObserverVec.begin(), m_ObserverVec.end(), observer));
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "InputObserver removed from vector");
	return true;
	}
		
	
}

//This Method is very important, it triggers all Notify() methods of all observers.
//The specific code in each class that inherits from observer will be executed
bool InputManager::NotifyObservers(MouseStruct mouseStruct, char* keyBuffer)
{
	std::vector<InputObserver*>::iterator it;
	std::vector<InputObserver*>::iterator begin = m_ObserverVec.begin();
	std::vector<InputObserver*>::iterator end = m_ObserverVec.end();
	for (it = begin; it < end; ++it)
	{
		(*it)->Notify(mouseStruct, keyBuffer);
	}
	//Return false if there are no observers in the vector
	return (m_ObserverVec.size() > 0);
}

