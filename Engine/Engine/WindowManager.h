#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "Window.h"
#include <vector>	 // std::vector
#include <algorithm> // find()

class WindowManager
{
public:
	//Default constructor.
	WindowManager(void);
	//Destructor.
	//Calls Cleanup and then destroys all local variables.
	virtual ~WindowManager(void);
	//Cleans up the mess this WindowManager created.
	//Keeps variables in memory to enable a reset.
	void Cleanup();
	//Pushes the window at the back of the vector.
	bool RegisterWindow(Window* window);
	//Simply removes a window from the vector and cleans up afterwards.
	bool ReleaseWindow(Window* window);
	//Remove a window by it's handle
	bool ReleaseWindow(HWND hwnd);
	//Returns the vector containing the windows.
	std::vector<Window*> GetWindows();
	//Render on all windows
	void RenderAll(void);
	//Window Procedure used by all Windows.
	//On quit it releases the window.
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	//Adds a window to the vector if it does not yet exist.
	void PushWindow(Window* wnd);
	//Removes a window from the vector
	void PopWindow(Window* window);
	//Local Vector to keep track of all instatiated windows.
	std::vector<Window*> windows;
};

#endif