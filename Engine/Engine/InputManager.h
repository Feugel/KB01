#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "InputKeyboard.h"
#include "InputMouse.h"

#include <windows.h>
#include <vector>
#include <algorithm>

class InputObserver;

class InputManager
{
public:
	//Destructor.
	//Calls Cleanup and then destroys all local variables.
	virtual ~InputManager(void);

	//Get the current InputManager instance.
	static InputManager* Instance();

	bool AddObserver(InputObserver* observer);
    bool RemoveObserver(InputObserver* observer);
    bool NotifyObservers(MouseStruct mouseStruct, char* keyBuffer);


	//Cleans up the mess this InputManager created.
	//Keeps variables in memory to enable a reset.
	void Cleanup();

	void Initialize();

	void Update();


private:
	std::vector<InputObserver*> m_ObserverVec;
	InputManager();
	static InputManager* inputManager;
};

#endif