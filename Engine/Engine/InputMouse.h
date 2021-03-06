#ifndef INPUTMOUSE_H
#define INPUTMOUSE_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//Provides mousedata in a struct
struct MouseStruct
{
	int positionX;
	int positionY;
	int z;
	bool button0;
	bool button1;
	bool button2;
	bool button3;
	bool button4;
	bool button5;
	bool button6;
	bool button7;
};

//Provides mouse input
class InputMouse
{
public:
	InputMouse(HWND);
	bool InitMouse();
	bool DoAcquire();
	void SetTheMouseBuffer();
	void ResetMouseStruct();
	void SaveReleaseDevice();
	MouseStruct GetMouseInput();
	virtual ~InputMouse();
	void Cleanup();
	bool ProcessMouse();

private:
	DIPROPDWORD dipdw;
	HWND hwnd;
	char MouseBuffer[16];
	
	MouseStruct bufferedMouse;

	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 dDevice;
};

#endif