#include "WindowManager.h"

WindowManager::WindowManager()
{
	numWindows = 0;
}

WindowManager::~WindowManager()
{
	Cleanup();
}

void WindowManager::Cleanup()
{

}

bool WindowManager::CreateWnd()
{
	PushWindow(new Window(NULL));
	return true;
}

void WindowManager::PushWindow(Window* wnd)
{
	numWindows ++;
}

void WindowManager::PopWindow(Window* wnd)
{
	numWindows --;
}

int WindowManager::GetNumWindows()
{
	return numWindows;
}