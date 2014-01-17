#ifndef INPUTMOUSE_H
#define INPUTMOUSE_H

#include "WinDef.h"


class InputMouse
{
public:
	InputMouse(HWND);
	bool InitMouse();
	bool DoAcquire();
	void SetTheMouseBuffer();
	void ResetMouseStruct()
	MouseStruct GetMouseInput();
	virtual ~InputMouse(void);
	void Cleanup();

private:
	
	
}

#endif