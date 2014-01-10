#include "Window.h"
#include "WindowManager.h"

Window::Window(HINSTANCE hInstance, WindowManager* manager)
{
	this->hInst = hInstance;
	this->manager = manager;
	this->Initialise();
	this->Create(CW_USEDEFAULT, CW_USEDEFAULT, L"Engine");
}

Window::Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, wchar_t* title)
{
	this->hInst = hInstance;
	this->manager = manager;
	this->Initialise();
	this->Create(width, height, title);
}

Window::~Window(void)
{
	Cleanup();
}

void Window::Cleanup()
{
	//TODO: clean up the mess
}

HWND Window::GetWindowHandle()
{
	return hWnd;
}

void Window::Initialise() // Should be moved to Manager to ensure one time run; we dont need to register multiple window classes
{
	LogManager::Instance()->Log("Initializing Window");
	/* The Window structure */
	Wnd.hInstance = hInst;
	Wnd.lpszClassName = L"Window";
	Wnd.lpfnWndProc = WindowManager::WindowProcedure;	/* This function is called by windows */
	Wnd.style = CS_GLOBALCLASS;							/* Make it a global class */
	Wnd.cbSize = sizeof (WNDCLASSEX);					// reserve space for window class

	/* Use default icon and mouse-pointer */
	Wnd.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	Wnd.hIconSm = LoadIcon (NULL, IDI_APPLICATION);	// set window icon
	Wnd.hCursor = LoadCursor (NULL, IDC_ARROW);
	Wnd.lpszMenuName = NULL;                 /* No menu */
	Wnd.cbClsExtra = 0;                      /* No extra bytes after the window class */
	Wnd.cbWndExtra = 0;                      /* structure or the window instance */
	// Set the background (will crash otherwise)
	Wnd.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	if(RegisterClassEx(&Wnd))
	{
		LogManager::Instance()->Log("Class registered successfully");
	} else {
		LogManager::Instance()->Log(LogLevel::WARNING, "Class NOT REGISTERED");
		LogManager::Instance()->Log(::GetLastError());
	}
}


void Window::Create(int width, int height, wchar_t* title)
{
	LogManager::Instance()->Log("Creating Window Handle");
	hWnd = CreateWindowEx(0,	//Default Window ExStyle
		Wnd.lpszClassName,		//Class Name
		title,					//Title
		WS_OVERLAPPEDWINDOW,	//Window Style
		CW_USEDEFAULT,			//Window X
		CW_USEDEFAULT,			//Window Y
		width,					//Window width
		height,					//Window height
		HWND_DESKTOP,			//Window Parent
		0,						//No menu
		Wnd.hInstance,			//hInstance
		this->manager);			//lpParams

	if(hWnd)
	{
		LogManager::Instance()->Log("Handle created");
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Creation of Window Handle failed!");
		throw(::GetLastError());
	}
}

void Window::DisplayWindow(bool fullscreen)
{
	if(hWnd)
	{
		LogManager::Instance()->Log("Making screen visible");
		/* Make the window visible on the screen */
		if(!fullscreen)
		{
			ShowWindow(hWnd, SW_SHOWDEFAULT);
		}
		else
		{
			ShowWindow(hWnd, SW_MAX);
		}
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Window Handle not initialized when calling DisplayWindow!");
	}
}

Renderer* Window::GetRenderer(void)
{
	return renderer;
}

void Window::SetRenderer(Renderer* renderer)
{
	this->renderer = renderer;
}

WindowManager* Window::GetManager()
{
	return this->manager;
}