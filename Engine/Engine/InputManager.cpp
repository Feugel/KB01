//#include "LogManager.h"
//#include "InputManager.h"
//#include "InputKeyboard.h"
//#include "InputMouse.h"
//
//
//InputManager::InputManager()
//{
//}
//
//InputManager::~InputManager()
//{
//	Cleanup();
//}
//
//void InputManager::Initialize()
//{
//	InputKeyboard* keyboard = new InputKeyboard(GetConsoleWindow());
//	InputMouse* mouse = new InputMouse(GetConsoleWindow());
//
//	bool keyboardinit = keyboard ->InitKeyboard();
//	bool mouseinit = mouse ->InitMouse();
//
//	if (!keyboardinit || !mouseinit)
//		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to initialize input");
//
//	keyboard ->DoAcquire();
//	mouse->DoAcquire();
//}
//
//InputStruct InputManager::Update()
//{
//	MouseStruct ms = mouse->GetMouseInput();
//}