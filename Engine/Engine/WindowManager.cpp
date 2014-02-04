#include "WindowManager.h"
#include "Window.h"
#include "Kernel.h"
#include "Scene.h"

WindowManager* WindowManager::instance = NULL;

//Constructor for WindowManager
WindowManager::WindowManager()
{
}

//Destructor for WindowManager
WindowManager::~WindowManager()
{
	Cleanup();
}

//This is the cleanup method for WindowManager
void WindowManager::Cleanup()
{
	windows.clear();
}

//This method creates a new WindowManager if there is no instance of it yet.
WindowManager* WindowManager::Instance()
{
	if(!instance)
		instance = new WindowManager();
	return instance;
}

//This is a boolean for RegisterWindow from WindowManager. 
bool WindowManager::RegisterWindow(Window* window)
{
	auto iterator = windows.find(window->GetWindowHandle());
	if(iterator == windows.end())
	{
		PushWindow(window);
		sceneMap[window] = NULL;
		window->DisplayWindow(false);
		return true;
	}
	else
	{
		return false;
	}
}

//This is a boolean for ReleaseWindow from WindowManager.
bool WindowManager::ReleaseWindow(Window* window)
{
	if(windows.count(window->GetWindowHandle()) == 1)
	{
		sceneMap.erase(window);
		PopWindow(window);
		return true;
	}
	else
	{
		return false;
	}
}

//This boolean returns the hwnd when the window is released.
bool WindowManager::ReleaseWindow(HWND hwnd)
{
	return ReleaseWindow(GetWindowByHandle(hwnd));
}

//
void WindowManager::RegisterScene(Window* window, Scene* scene)
{
	auto iterator = sceneMap.find(window);
	if(sceneMap.find(window) != sceneMap.end())
	{
		iterator->second = scene;
	}
	else
	{
		sceneMap[window] = scene;
	}
}

Scene* WindowManager::GetSceneByWindow(Window* window)
{
	auto iterator = sceneMap.find(window);
	if(sceneMap.find(window) != sceneMap.end())
	{
		return iterator->second;
	}
	else
	{
		return NULL;
	}
}

Scene* WindowManager::GetSceneByWindow(HWND window)
{
	return GetSceneByWindow(GetWindowByHandle(window));
}

void WindowManager::PushWindow(Window* wnd)
{
	windows[wnd->GetWindowHandle()] = wnd;
}

void WindowManager::PopWindow(Window* window)
{
	windows.erase(window->GetWindowHandle());
}

std::map<HWND, Window*> WindowManager::GetWindows()
{
	return windows;
}

void WindowManager::Render()
{
	std::for_each(windows.begin(), windows.end(), [](std::pair<HWND, Window*> item)
	{
		item.second->Render();
	});
}

Kernel* WindowManager::GetKernel()
{
	return kernel;
}

void WindowManager::SetKernel(Kernel* kernel)
{
	this->kernel = kernel;
}

Window* WindowManager::GetWindowByHandle(HWND hwnd)
{
	if(windows.count(hwnd) == 1)
		return windows[hwnd];
	else
		return NULL;
}

LRESULT CALLBACK WindowManager::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowManager *view;

    if (message == WM_NCCREATE)
    {
        CREATESTRUCT *cs = (CREATESTRUCT*) lParam; 
        view = (WindowManager*) cs->lpCreateParams;

        SetLastError(0);
        if (SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR) view) == 0)
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        view = (WindowManager*) GetWindowLongPtr(hwnd, GWL_USERDATA);
    }

    if (view)
        return view->WindowProc(hwnd, message, wParam, lParam);

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CLOSE:
			{
				this->ReleaseWindow(hwnd);
				DestroyWindow(hwnd);
				if(this->GetWindows().size() == 0)
					kernel->Stop();
			} break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}