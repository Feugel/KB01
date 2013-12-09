#ifndef WINDOW_H
#define WINDOW_H

#include "LogManager.h"
#include <windows.h>
//#include "Renderer.h"

class WindowManager;

class Window
{
public:
	//Default constructor.
	//Uses default width and height, and 'Engine' as title.
	Window(HINSTANCE hInstance, WindowManager* manager);
	//Constructor specifying width and height including custom title.
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, wchar_t* title);
	//Gets the handle to this window.
	HWND GetWindowHandle();
	//Makes the window visible on screen.
	void DisplayWindow(bool fullscreen);
	//Get the Renderer
	//Renderer GetRenderer(void);
	//Destructor
	//Calls Cleanup()
	virtual ~Window();
	//Cleans up the mess this Window created.
	void Cleanup();
private:
	//Creates the window and registers the window class
	void Create(int width, int height, wchar_t* title);
	//Initialises the Window class
	void Initialise(void);
	//Renderer renderer;

	//
	HWND hWnd;
	//
	HINSTANCE hInst;
	//
	WNDCLASSEX Wnd;
	//
	WindowManager* manager;
};

#endif