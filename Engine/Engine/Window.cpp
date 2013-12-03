#include "Window.h"

Window::Window(HINSTANCE hInstance)
{
	hInst = hInstance;
	Wnd.hInstance = hInstance;
	/* The Window structure */
	Wnd.hInstance = hInstance;
    Wnd.lpszClassName = L"Window";
    Wnd.lpfnWndProc = WndProc;      /* This function is called by windows */
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
	
	if( RegisterClassEx(&Wnd))
    {
        hWnd = CreateWindowEx(0,	//Default Window ExStyle
			L"Window",				//Class Name
			L"Engine",				//Title
            WS_OVERLAPPEDWINDOW,	//Default Window Style
			CW_USEDEFAULT,			//Window X
			CW_USEDEFAULT,			//Window Y
            CW_USEDEFAULT,			//Window width
			CW_USEDEFAULT,			//Window height
			0,						//Window Parent
			0,						//No menu
			hInstance,				//hInstance
			0);						//lpParams
        if(hWnd)
        {
			/* Make the window visible on the screen */
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            MSG msg;
			/* Run the message loop. It will run until GetMessage() returns 0 */
            while(GetMessage(&msg, 0, 0, 0))
			{
				/* Translate virtual-key messages into character messages */
				TranslateMessage(&msg);
				/* Send message to WindowProcedure */
				DispatchMessage(&msg) ;
			}
        }
    }
}

Window::~Window(void)
{
	Cleanup();
}

void Window::Cleanup()
{
	
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
    {
        case WM_CLOSE:
            {
                PostQuitMessage(WM_QUIT);
            } break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
