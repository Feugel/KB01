//#include "LogManager.h"
//#include "InputManager.h"
//#include "InputKeyboard.h"
//#include "InputMouse.h"
//
////Creates the keyboard and mouse so they can get initialized and updated later
//InputKeyboard* keyboard = new InputKeyboard(GetConsoleWindow());
//InputMouse* mouse = new InputMouse(GetConsoleWindow());
//
////Constructor for InputManager
//InputManager::InputManager()
//{
//}
//
////Destructor for InputManager
//InputManager::~InputManager()
//{
//	Cleanup();
//}
//
////
//void InputManager::Initialize()
//{
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
//
//InputStruct InputManager::Update()
//{
//	
//	MouseStruct ms = mouse->GetMouseInput();
//}