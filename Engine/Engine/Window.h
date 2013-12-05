#ifndef WINDOW_H
#define WINDOW_H

#include "LogManager.h"
#include <windows.h>
#include <windowsx.h>
class WindowManager;

class Window
{
public:
	Window(HINSTANCE hIns, WindowManager* manager);
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, char* title, bool fullscreen);
	HWND GetWindowHandle();
	virtual ~Window();
	void Cleanup();
private:
	void Create(HINSTANCE hInstance, int width, int height, char* title, bool fullscreen);
	//Renderer renderer;
	HWND hWnd;
	HINSTANCE hInst;
	WNDCLASS Wnd;
	WindowManager* manager;
};

#endif