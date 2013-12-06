#ifndef WINDOW_H
#define WINDOW_H

#include "LogManager.h"
#include <windows.h>

class WindowManager;

class Window
{
public:
	//<summary>
	//Default constructor.
	//Uses default width and height, and 'Engine' as title.
	//</summary>
	Window(HINSTANCE hInstance, WindowManager* manager);
	//<summary>
	//Constructor specifying width and height including custom title.
	//</summary>
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, wchar_t* title);
	//<summary>
	//Gets the handle to this window.
	//</summary>
	HWND GetWindowHandle();
	//<summary>
	//Makes the window visible on screen.
	//</summary>
	void DisplayWindow(bool fullscreen);
	//<summary>
	//Destructor
	//Calls Cleanup()
	//</summary>
	virtual ~Window();
	//<summary>
	//Cleans up the mess this Window created.
	//</summary>
	void Cleanup();
private:
	//<summary>
	//Creates the window and registers the window class
	//</summary>
	void Create(int width, int height, wchar_t* title);
	//<summary>
	//Initialises the Window class
	//</summary>
	void Initialise(void);
	//Renderer renderer;
	HWND hWnd;
	HINSTANCE hInst;
	WNDCLASSEX Wnd;
	WindowManager* manager;
};

#endif