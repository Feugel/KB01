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
	
}

HWND Window::GetWindowHandle()
{
	return hWnd;
}

void Window::Create(int width, int height, wchar_t* title)
{
	LogManager::Instance()->Log("Creating Window Handle");
	hWnd = CreateWindowExW(0,	//Default Window ExStyle
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
		0);						//lpParams
	if(hWnd)
	{
		LogManager::Instance()->Log("Handle created");
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Creation of Window Handle failed!");
	}
}

void Window::Initialise()
{
	LogManager::Instance()->Log("Creating Window");
	/* The Window structure */
	Wnd.hInstance = hInst;
	Wnd.lpszClassName = L"Window";
	Wnd.lpfnWndProc = WindowManager::WindowProcedure;      /* This function is called by windows */
	Wnd.style = CS_DBLCLKS;                 /* Catch double-clicks */
	Wnd.cbSize = sizeof (WNDCLASSEX);		// reserve space for window class

	/* Use default icon and mouse-pointer */
	Wnd.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	Wnd.hIconSm = LoadIcon (NULL, IDI_APPLICATION);	// set window icon
	Wnd.hCursor = LoadCursor (NULL, IDC_ARROW);
	Wnd.lpszMenuName = NULL;                 /* No menu */
	Wnd.cbClsExtra = 0;                      /* No extra bytes after the window class */
	Wnd.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default color as the background of the window */
	Wnd.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	
	RegisterClassEx(&Wnd);
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