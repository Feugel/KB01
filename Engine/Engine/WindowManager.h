#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "Window.h"
#include <vector>	 // std::vector
#include <algorithm> // find()

class WindowManager
{
public:
	//<summary>
	//Default constructor.
	//</summary>
	WindowManager(void);
	//<summary>
	//Destructor.
	//Calls Cleanup and then destroys all local variables.
	//</summary>
	virtual ~WindowManager(void);
	//<summary>
	//Cleans up the mess this WindowManager created.
	//Keeps variables in memory to enable a reset.
	//</summary>
	void Cleanup();
	//<summary>
	//Pushes the window at the back of the vector.
	//</summary>
	bool RegisterWindow(Window* window);
	//<summary>
	//Simply removes a window from the vector and cleans up afterwards.
	//</summary>
	bool ReleaseWindow(Window* window);
	//<summary>
	//Returns the vector containing the windows.
	//</summary>
	std::vector<Window*> GetWindows();
	//<summary>
	//Window Procedure used by all Windows.
	//On quit it releases the window.
	//</summary>
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	//<summary>
	//Adds a window to the vector if it does not yet exist.
	//</summary>
	void PushWindow(Window* wnd);
	//<summary>
	//Removes a window from the vector
	//</summary>
	void PopWindow(Window* window);
	//<summary>
	//Local Vector to keep track of all instatiated windows.
	//</summary>
	std::vector<Window*> windows;
};

#endif