#include "Window.h"


Window::Window(void)
{
}


Window::~Window(void)
{
}

void Window::Cleanup()
{

}

bool Create(int width, int height, char * title, bool fullscreen)
{
	WNDCLASSEX window;

    HINSTANCE hInstance;

    hInstance = GetModuleHandle(NULL);
    window.cbSize = sizeof(WNDCLASSEX);
    window.cbClsExtra = 0;
    window.cbWndExtra = 0;
    window.hbrBackground = NULL;
    window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    window.hCursor = LoadCursor(NULL, IDC_ARROW);
    window.hInstance = hInstance;
	window.lpfnWndProc = Window::WndProc;
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hwnd, msg, wParam, lParam);
}

//int WINAPI Window::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	// the handle for the window, filled by a function
//    HWND hWnd;
//    // this struct holds information for the window class
//    WNDCLASSEX wc;
//
//    // clear out the window class for use
//    ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//    // fill in the struct with the needed information
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//    wc.hInstance = hInstance;
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//    wc.lpszClassName = L"WindowClass1";
//
//    // register the window class
//    RegisterClassEx(&wc);
//
//    // create the window and use the result as the handle
//    hWnd = CreateWindowEx(NULL,
//                          L"WindowClass1",    // name of the window class
//                          L"Our First Windowed Program",   // title of the window
//                          WS_OVERLAPPEDWINDOW,    // window style
//                          300,    // x-position of the window
//                          300,    // y-position of the window
//                          500,    // width of the window
//                          400,    // height of the window
//                          NULL,    // we have no parent window, NULL
//                          NULL,    // we aren't using menus, NULL
//                          hInstance,    // application handle
//                          NULL);    // used with multiple windows, NULL
//
//    // display the window on the screen
//    ShowWindow(hWnd, nCmdShow);
//
//    // enter the main loop:
//
//    // this struct holds Windows event messages
//    MSG msg;
//
//    // wait for the next message in the queue, store the result in 'msg'
//    while(GetMessage(&msg, NULL, 0, 0))
//    {
//        // translate keystroke messages into the right format
//        TranslateMessage(&msg);
//
//        // send the message to the WindowProc function
//        DispatchMessage(&msg);
//    }
//
//    // return this part of the WM_QUIT message to Windows
//    return msg.wParam;
//}