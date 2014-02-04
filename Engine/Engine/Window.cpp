#include "Window.h"
#include "WindowManager.h"
#include "Renderer.h"
#include "LogManager.h"

//Constructor for Window
Window::Window(HINSTANCE hInstance, WindowManager* manager)
{
	this->hInst = hInstance;
	this->manager = manager;
	this->Initialise();
	this->Create(CW_USEDEFAULT, CW_USEDEFAULT, "Engine");
}

//Overloaded constructor for Window
Window::Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, std::string title)
{
	this->hInst = hInstance;
	this->manager = manager;
	this->name = title;
	this->Initialise();
	this->Create(width, height, title);
}

//Destructor for Window
Window::~Window(void)
{
	Cleanup();
}

void Window::Cleanup()
{
	//TODO: clean up the mess
}

//HWND Window handler for Window.
HWND Window::GetWindowHandle()
{
	return hWnd;
}

//Initialise method for Window.
void Window::Initialise() // Should be moved to Manager to ensure one time run; we dont need to register multiple window classes
{
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Initializing Window");
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
		LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Class registered successfully");
	} else {
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Class NOT REGISTERED");
		LogManager::Instance()->Log("%lu", ::GetLastError());
	}
}

//This method from Window Creates a new window, given the right attributes and logs this with using the LogManager.
void Window::Create(int width, int height, std::string title)
{
	LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Creating Window Handle");
	hWnd = CreateWindowEx(0,	//Default Window ExStyle
		Wnd.lpszClassName,		//Class Name
		s2ws(title).c_str(),	//Title
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
		LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Handle created");
	}
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Creation of Window Handle failed!");
		throw(::GetLastError());
	}
}

//This method is to display the window with a given boolean. 
void Window::DisplayWindow(bool fullscreen)
{
	if(hWnd)
	{
		LogManager::Instance()->Log("%s - %s", __FUNCTION__, "Making screen visible");
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
		LogManager::Instance()->Log(LogLevel::WARNING, "%s - %s", __FUNCTION__, "Window Handle not initialized when calling DisplayWindow!");
	}
}


//This method sets the Renderer
void Window::SetRenderer(Renderer* renderer)
{
	this->renderer = renderer;
}

//This method gets the Manager of the window.
WindowManager* Window::GetManager()
{
	return this->manager;
}

//This method gets the Name of the window.
std::string Window::GetName()
{
	return name;
}

//This method sets the name of the window.
void Window::SetName(std::string name)
{
	this->name = name;
}

//This method returns the Renderer from the window
Renderer* Window::GetRenderer()
{
	return renderer;
}

//This method Starts the renderer and Ends it.
void Window::Render()
{
	renderer->RenderStart();
	renderer->Render();
	renderer->RenderEnd();
	renderer->Present();
}

//This method converts a string into a wide-string
std::wstring Window::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}