#ifndef INPUTKEYBOARD_H
#define INPUTKEYBOARD_H

#include "windows.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//Provides keyboard input
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

	char* getKeyBuffer();
	

private:
	HWND hwnd;
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 dDevice;
	
	char keyBuffer[256];
};

#endif