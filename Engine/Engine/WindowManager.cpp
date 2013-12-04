#include "WindowManager.h"

WindowManager::WindowManager()
{

}

WindowManager::~WindowManager()
{
	Cleanup();
}

void WindowManager::Cleanup()
{
	while(windows.size() != 0)
	{
		windows.pop_back();
	}
}

bool WindowManager::CreateWnd()
{
	PushWindow(new Window(NULL, this));
	return true;
}

bool WindowManager::ReleaseWindow()
{
	PopWindow();
	return true;
}

void WindowManager::PushWindow(Window* wnd)
{
	windows.push_back(wnd);
}

void WindowManager::PopWindow()
{
	windows.pop_back();
}

std::vector<Window*> WindowManager::GetWindows()
{
	return windows;
}

LRESULT CALLBACK WindowManager::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
    {
        case WM_CLOSE:
            {
				DestroyWindow(hwnd);
            } break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}