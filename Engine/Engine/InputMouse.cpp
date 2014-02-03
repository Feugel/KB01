#include "InputMouse.h"
#include "dinput.h"

#include "LogManager.h"

InputMouse::InputMouse( HWND argHwnd )
{
	const int MOUSEBUFFER = 8;
	

	dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj			= 0;
	dipdw.diph.dwHow			= DIPH_DEVICE;
	dipdw.dwData				= MOUSEBUFFER;
	hwnd						= argHwnd;
	dInput						= NULL;
	dDevice						= NULL;

	ResetMouseStruct();
}

//Destructor for InputMouse
InputMouse::~InputMouse()
{

}

//Initializing the InputMouse (creating the device and setting the coopertive level)
bool InputMouse::InitMouse()
{
	//DirectInput8Create should be done only once in manager
	HRESULT result = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL );
	if( FAILED( result ) )
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to create mouse DirectInput8");
		return false;
	} 

	//Creates the right DirectInput device and logs this if failed
	result = dInput->CreateDevice( GUID_SysMouse, &dDevice, NULL );
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to create mouse DirectInput device.");
		return false;
	}

	//Sets the right DataFormat and logs this if failed
	result = dDevice->SetDataFormat( &c_dfDIMouse );
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to set mouse DataFormat.");
		return false;
	}

	//Sets the right cooperativeLevel and lots this if failed
	result = dDevice->SetCooperativeLevel( hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND );
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to set mouse CooperativeLevel");
		return false;
	}

	//Sets the right mouse Property and logs this if failed
	result = dDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to set mouse Property");
		return false;
	}
	
	//Logs the succesfully registered mouse.
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Succesfully registered mouse input device");
	return true;
}

//Mousestruct to get the Mouse input and use DoAcquire if needed.
MouseStruct InputMouse::GetMouseInput()
{
	if(!SUCCEEDED( dDevice->Poll()))
	{
		DoAcquire();
	}
	
	SetTheMouseBuffer();

	return bufferedMouse;
}


//Acquiring the device, trying it multiple times to make sure it's found. 
bool InputMouse::DoAcquire()
{
	int times = 5;	// Number of times to try acquire
	for( int i = 0; i < times; i++ )
	{
		if( SUCCEEDED( dDevice->Acquire() ) )
			return true;
	}
	LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Unable to acquire mouse.");
	return false;
}

//Setting the buffer for the mouse and getting the device-data
void InputMouse::SetTheMouseBuffer()
{
	DIDEVICEOBJECTDATA od;
	DWORD elements = 1;

	HRESULT hr = dDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );
	//&elements = number of elements in deviceData. 

	// Switch case to get the data from the mouse
	switch (od.dwOfs) 
	{
		// Mouse horizontal motion
		case DIMOFS_X:
			bufferedMouse.positionX += static_cast<long>(od.dwData);
			break;

		// Mouse vertical motion
		case DIMOFS_Y:
			bufferedMouse.positionY += static_cast<long>(od.dwData);
			break;

		// Mouse left button
		case DIMOFS_BUTTON0:
			if ( (long)od.dwData == 0 )
			{
				bufferedMouse.button0 = false;
			}
			else
			{
				bufferedMouse.button0 = true;
			}
			break;

		// Mouse left button
		case DIMOFS_BUTTON1:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button1 = false;
			}
			else
			{
				bufferedMouse.button1 = true;
			}
			break;

		// Mousewheel button
		case DIMOFS_BUTTON2:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button2 = false;
			}
			else
			{
				bufferedMouse.button2 = true;
			}
			break;
		
		// Button 3
		case DIMOFS_BUTTON3:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button3 = false;
			}
			else
			{
				bufferedMouse.button3 = true;
			}
			break;

		// Button 4
		case DIMOFS_BUTTON4:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button4 = false;
			}
			else
			{
				bufferedMouse.button4 = true;
			}
			break;

		// Button 5
		case DIMOFS_BUTTON5:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button5 = false;
			}
			else
			{
				bufferedMouse.button5 = true;
			}
			break;

		// Button 6
		case DIMOFS_BUTTON6:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button6 = false;
			}
			else
			{
				bufferedMouse.button6 = true;
			}
			break;

		// Button 7
		case DIMOFS_BUTTON7:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button7 = false;
			}
			else
			{
				bufferedMouse.button7 = true;
			}
			break;

		// Mouse wheel
		case DIMOFS_Z:
			bufferedMouse.z += static_cast<long>(od.dwData);
			break;
	}
}

//Cleaning up the mess left if a mouse device is lost
void InputMouse::SaveReleaseDevice() 
{ 
	if( dInput )
	{ 
		if( dDevice )
		{ 
			dDevice->Unacquire();
			dDevice->Release();
			dDevice = NULL;
		} 
		dInput->Release();
		dInput = NULL;
	} 
} 

//Sets the bufferedMouse
void InputMouse::ResetMouseStruct()
{
	bufferedMouse.positionX = 0;
	bufferedMouse.positionY = 0;
	bufferedMouse.z = 0;
	bufferedMouse.button0 = false;
	bufferedMouse.button1 = false;
	bufferedMouse.button2 = false;
	bufferedMouse.button3 = false;
	bufferedMouse.button4 = false;
	bufferedMouse.button5 = false;
	bufferedMouse.button6 = false;
	bufferedMouse.button7 = false;	
}
