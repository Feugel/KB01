#include "Window.h"
#include "WindowManager.h"

Window::Window(HINSTANCE hInstance, WindowManager* manager)
{
	this->hInst = hInstance;
	this->manager = manager;
	this->Create(hInst, CW_USEDEFAULT, CW_USEDEFAULT, "", false);
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

void Window::Create(HINSTANCE hInstance, int width, int height, char* title, bool fullscreen)
{
	LogManager::Instance()->Log("Creating Window");
	Wnd.hInstance = hInstance;
	/* The Window structure */
	Wnd.hInstance = hInstance;
    Wnd.lpszClassName = L"Window";
	Wnd.lpfnWndProc = WindowManager::WindowProcedure;      /* This function is called by windows */
    Wnd.style = CS_DBLCLKS;                 /* Catch double-clicks */
    Wnd.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    Wnd.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    Wnd.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    Wnd.hCursor = LoadCursor (NULL, IDC_ARROW);
    Wnd.lpszMenuName = NULL;                 /* No menu */
    Wnd.cbClsExtra = 0;                      /* No extra bytes after the window class */
    Wnd.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    Wnd.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	LogManager::Instance()->Log("Registering Window Class");
	if( RegisterClassEx(&Wnd))
    {
		LogManager::Instance()->Log("Creating Window Handle");
        hWnd = CreateWindowExA(0,	//Default Window ExStyle
			"Window",				//Class Name
			title,					//Title
            WS_OVERLAPPEDWINDOW,	//Window Style
			CW_USEDEFAULT,			//Window X
			CW_USEDEFAULT,			//Window Y
            width,					//Window width
			height,					//Window height
			0,						//Window Parent (none)
			0,						//No menu
			hInstance,				//hInstance
			0);						//lpParams

        if(hWnd)
        {
			LogManager::Instance()->Log("Handle created");
			LogManager::Instance()->Log("Making screen visible");
			/* Make the window visible on the screen */
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            MSG msg;
			/* Run the message loop. It will run until GetMessage() returns 0 */
            while(GetMessage(&msg, 0, 0, 0))
			{
				/* Translate virtual-key messages into character messages */
				TranslateMessage(&msg);
				/* Send message to WindowProcedure */
				DispatchMessage(&msg);
			}
        }
		else
		{
			LogManager::Instance()->Log(LogLevel::WARNING, "Creation of Window Handle failed!");
		}
    }
	else
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Registering Window Class failed!");
	}
}
