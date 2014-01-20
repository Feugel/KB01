//#ifndef INPUTMOUSE_H
//#define INPUTMOUSE_H
//
//#include "WinDef.h"
//
//
//class InputMouse
//{
//public:
//	InputMouse(HWND);
//	bool InitMouse();
//	bool DoAcquire();
//	void SetTheMouseBuffer();
//	void ResetMouseStruct();
//	void SaveReleaseDevice();
//	MouseStruct GetMouseInput();
//	virtual ~InputMouse(void);
//	void Cleanup();
//	MouseStruct struct MouseStruct
//	{
//		int mouse_x;
//		int mouse_y;
//	};
//
//private:
//	DIPROPDWORD dipdw;
//	HWND hwnd;
//	
//	LPDIRECTINPUT8 dInput;
//	LPDIRECTINPUTDEVICE8 dDevice;
//}
//
//#endif