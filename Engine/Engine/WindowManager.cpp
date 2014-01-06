#include "WindowManager.h"
#include "Window.h"
#include "Kernel.h"

WindowManager::WindowManager(Kernel* kernel)
{
	this->kernel = kernel;
	windows.clear(); // make sure we get clean memory
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

bool WindowManager::RegisterWindow(Window* window)
{
	if(std::find(windows.begin(), windows.end(), window) == windows.end())
	{
		PushWindow(window);
		window->DisplayWindow(false);
		return true;
	}
	else
	{
		return false;
	}
}

bool WindowManager::ReleaseWindow(Window* window)
{
	if(std::find(windows.begin(), windows.end(), window) == windows.end())
	{
		PopWindow(window);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool WindowManager::ReleaseWindow(HWND hwnd)
{
	auto iterator = std::find_if(windows.begin(), windows.end(), [&hwnd](Window* window){ return window->GetWindowHandle() == hwnd; });
	if(iterator != windows.end())
	{
		PopWindow(*iterator);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

void WindowManager::PushWindow(Window* wnd)
{
	windows.push_back(wnd);
}

void WindowManager::PopWindow(Window* window)
{
	auto item = std::find(windows.begin(), windows.end(), window);
	windows.erase(item, item+1);
}

std::vector<Window*> WindowManager::GetWindows()
{
	return windows;
}

void WindowManager::Render()
{
	for(int i = windows.size(); i > 0; --i)
	{
		windows[i-1]->GetRenderer()->RenderStart();
		windows[i-1]->GetRenderer()->Render();
		windows[i-1]->GetRenderer()->RenderEnd();
		windows[i-1]->GetRenderer()->Present();
	}
}

Kernel* WindowManager::GetKernel()
{
	return kernel;
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