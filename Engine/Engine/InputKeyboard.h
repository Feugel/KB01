#ifndef INPUTKEYBOARD_H
#define INPUTKEYBOARD_H

#include "windows.h"
#include <dinput.h>


class InputKeyboard
{
public:
	InputKeyboard(HWND);
	virtual ~InputKeyboard();
	void Cleanup();

	bool InitKeyboard();
	void SaveReleaseDevice();
	bool DoAcquire();
	bool ProcessKBInput(byte);
	//Move();
	

private:
	HWND hwnd;
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 dDevice;
	
	char keyBuffer[256];
};

#endif