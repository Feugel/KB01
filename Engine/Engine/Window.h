#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <string>

class WindowManager; // make sure we can reference the manager from here; maybe change this to a friend class?
class Renderer;
class LogManager;

class Window
{
public:
	//Default constructor.
	//Uses default width and height, and 'Engine' as title.
	Window(HINSTANCE hInstance, WindowManager* manager);
	//Constructor specifying width and height including custom title.
	Window(HINSTANCE hInstance, WindowManager* manager, int width, int height, std::string title);
	//Destructor
	//Calls Cleanup(), then deletes the objects
	virtual ~Window();
	//Cleans up the mess this Window created.
	virtual void Cleanup();
	//Gets the handle to this window.
	virtual HWND GetWindowHandle();
	//Makes the window visible on screen.
	virtual void DisplayWindow(bool fullscreen);
	//Set the renderer
	void SetRenderer(Renderer* renderer);	
	//Get the Renderer
	Renderer* GetRenderer();
	//Call the entire Render stack
	void Render();
	//Get the manager
	WindowManager* GetManager();
	//Get the name
	std::string GetName();
	//Set the name
	void SetName(std::string name);
private:
	//Creates the window and registers the window class
	virtual void Create(int width, int height, std::string title);
	//Initialises the Window class
	virtual void Initialise(void);
	//Convert from std::string to std::wstring
	std::wstring s2ws(const std::string& s);
	//Window name; also used as title
	std::string name;
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