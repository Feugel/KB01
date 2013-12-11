#ifndef WINDOW_H
#define WINDOW_H

#include "LogManager.h"
#include <windows.h>
#include "Renderer.h"

class WindowManager; // make sure we can reference the manager from here; maybe change this to a friend class?

class Window
{
public:
	//Default constructor.
	//Uses default width and height, and 'Engine' as title.
	Window(HINSTANCE hInstance, WindowManager* manager);
	//Constructor specifying width and height including custom title.
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, wchar_t* title);
	//Gets the handle to this window.
	virtual HWND GetWindowHandle();
	//Makes the window visible on screen.
	virtual void DisplayWindow(bool fullscreen);
	////Get the Renderer
	Renderer* GetRenderer(void);
	////Set the renderer
	void SetRenderer(Renderer* renderer);
	//Destructor
	//Calls Cleanup(), then deletes the objects
	virtual ~Window();
	//Cleans up the mess this Window created.
	virtual void Cleanup();
private:
	//Creates the window and registers the window class
	virtual void Create(int width, int height, wchar_t* title);
	//Initialises the Window class
	virtual void Initialise(void);
	//Renderer
	Renderer* renderer;
	//Window Handle
	HWND hWnd;
	//Window Instance Handle
	HINSTANCE hInst;
	//Window
	WNDCLASSEX Wnd;
	//WindowManager
	WindowManager* manager;
};

#endif