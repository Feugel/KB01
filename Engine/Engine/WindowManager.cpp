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
		sceneMap[window] = NULL;
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
	if(std::find(windows.begin(), windows.end(), window) != windows.end())
	{
		PopWindow(window);
		sceneMap[window]->Cleanup();
		sceneMap.erase(window);
		return true;
	}
	else
	{
		return false;
	}
}

bool WindowManager::ReleaseWindow(HWND hwnd)
{
	return ReleaseWindow(GetWindowByHandle(hwnd));
}

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

Window* WindowManager::GetWindowByHandle(HWND hwnd)
{
	auto iterator = std::find_if(windows.begin(), windows.end(), [&hwnd](Window* window){ return window->GetWindowHandle() == hwnd; });
	if(iterator != windows.end())
	{
		return *iterator;
	}
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