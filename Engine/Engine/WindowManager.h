#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "Window.h"

class WindowManager
{
public:
	WindowManager(void);
	virtual ~WindowManager(void);
	void Cleanup();
	bool CreateWnd();
	bool ReleaseWindow();
	int GetNumWindows();
private:
	void PushWindow(Window* wnd);
	void PopWindow(Window* wnd);
	Window* window; // Should be some kind of array or list
	int numWindows;
};

#endif