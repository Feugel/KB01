#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <windows.h>
#include "EntityCamera.h"

struct InputStruct
{
	int MousePositionX;
	int MousePositionY;
	int MouseZ;
	bool MouseButton0;
	bool MouseButton1;
	bool MouseButton2;
	bool MouseButton3;
	bool MouseButton4;
	bool MouseButton5;
	bool MouseButton6;
	bool MouseButton7;
	bool KeyboardInput(byte);
};

class InputManager
{
public:
	//Destructor.
	//Calls Cleanup and then destroys all local variables.
	virtual ~InputManager(void);
	//Cleans up the mess this InputManager created.
	//Keeps variables in memory to enable a reset.
	void Cleanup();

	void Initialize();

	struct Update();

	//Get the instance
	static InputManager* Instance();
	////Pushes the camera at the back of the vector.
	//bool RegisterListener();
	////Simply removes a camera from the vector and cleans up afterwards.
	//bool ReleaseListener();
	////Remove a camera by it's handle
	//bool ReleaseListener(HWND hwnd);

private:
	//Default constructor.
	InputManager();                                             
};

#endif