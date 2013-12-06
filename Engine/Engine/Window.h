#ifndef WINDOW_H
#define WINDOW_H

#include "LogManager.h"
#include <windows.h>

class WindowManager;

class Window
{
public:
	Window(HINSTANCE hInstance, WindowManager* manager);
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, wchar_t* title);
	HWND GetWindowHandle();
	void DisplayWindow(bool fullscreen);
	virtual ~Window();
	void Cleanup();
private:
	void Create(int width, int height, wchar_t* title);
	void Initialise(void);
	//Renderer renderer;
	HWND hWnd;
	HINSTANCE hInst;
	WNDCLASS Wnd;
	WindowManager* manager;
};

#endif