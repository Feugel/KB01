#include "InputKeyboard.h"
#include "dinput.h"

#include "LogManager.h"

//#include <allegro.h>

#define KEYDOWN(name, key) (name[key] & 0x80) 




/**
 * Function:	InputKeyboard::InputKeyboard(...)
 * Description:	InputKeyboard constructor
 * @ param hWnd:
 *   Pointer to windowHandle, used to set the "SetCooperativeLevel" 
 */
InputKeyboard::InputKeyboard( HWND argHwnd )
{
	dInput = NULL; 
	dDevice	= NULL; 
	hwnd = argHwnd;

	InitKeyboard();
}


/**
 * Function:	InputKeyboard::~InputKeyboard()
 * Description:	InputKeyboard destructor
 */
InputKeyboard::~InputKeyboard()
{

}


/**
 * Function:	InputKeyboard::InitKeyboard()
 * Description:	initializing the keyboard (creating the device and setting the coopertive level)
 */
bool InputKeyboard::InitKeyboard()
{
	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL ); 
	if FAILED( hr ) 
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to create keyboard DirectInput8");
		return false; 
	}

	//Creates the right DirectInput device and logs this if failed
	hr = dInput->CreateDevice( GUID_SysKeyboard, &dDevice, NULL );
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to create keyboard DirectInput device.");
		return false; 
	}

	//Sets the right DataFormat and logs this if failed
	hr = dDevice->SetDataFormat( &c_dfDIKeyboard ); 
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to set keyboard DataFormat.");
		return false; 
	} 

	//Sets the right cooperativeLevel and lots this if failed
	hr = dDevice->SetCooperativeLevel( hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND );
	if FAILED( hr )
	{ 
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to set keyboard CooperativeLevel");
		return false; 
	} 

	//Logs the succesfully registered keyboard
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Succesfully registered keyboard input device");
	return true; 
}

/**
 * Function:	InputKeyboard::saveReleaseDevice() 
 * Description:	Cleaning up the mess left if a keyboard is lost
 */
void InputKeyboard::SaveReleaseDevice() 
{ 
	if (dInput) 
	{ 
		if (dDevice) 
		{ 
			dDevice->Unacquire(); 
			dDevice->Release();
			dDevice = NULL; 
		} 
		dInput->Release();
		dInput = NULL; 
	} 
} 


/**
 * Function:	InputKeyboard::ProcessKBInput(...)
 * Description:	Method to see if the keyboardbuffer can be red or that a aquire is needed
 * @ param argIsToggle
 *	 Boolean to see if the key that is pressed a togglebutton is
 * @ param argKeyIsPressed
 *	 Byte containing the key that must be checked
 */
bool InputKeyboard::ProcessKBInput( byte argKeyIsPressed ) 
{ 
	if(!SUCCEEDED( dDevice->Poll() ))
	{
		DoAcquire();
	}
	
	dDevice->GetDeviceState( sizeof( keyBuffer ) , (LPVOID)&keyBuffer );

	// Check if keybuffer contains given key
	int pressed = KEYDOWN( keyBuffer, argKeyIsPressed );

	// pressed == 0 or 128 (0x80); meaning false or true
	if( pressed == 0 )
	{
		return false;
	}
	else
	{
		return true;
	}

	if (KEYDOWN( keyBuffer, DIK_W ) || KEYDOWN( keyBuffer, DIK_UP ))
		;//Move forward
	else if (KEYDOWN( keyBuffer, DIK_A || KEYDOWN( keyBuffer, DIK_LEFT )))
		;//Move left
	else if (KEYDOWN( keyBuffer, DIK_S || KEYDOWN( keyBuffer, DIK_DOWN )))
		;//Move backward
	else if (KEYDOWN( keyBuffer, DIK_D || KEYDOWN( keyBuffer, DIK_RIGHT)))
		;//Move right


}

//a method to return the keyBuffer
char* InputKeyboard::getKeyBuffer()
{ 
	return keyBuffer;
}

/**
 * Function:	InputKeyboard::DoAcquire()
 * Description:	Aquiring the device, multiple times to make sure it gets it
 */
bool InputKeyboard::DoAcquire()
{

	int times = 5;
	for( int i = 0; i < times; i++ )
	{
		if( SUCCEEDED( dDevice->Acquire() ) )
		{
			return true;
		}
	}
	//Use LogManager method to write all the data to the log file
	LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to acquire keyboard.");
	return false;
}
