#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "Window.h"
#include <vector>	 // std::vector
#include <algorithm> // find()

class WindowManager
{
public:
	WindowManager(void);
	virtual ~WindowManager(void);
	void Cleanup();
	bool RegisterWindow(Window* window);
	bool ReleaseWindow(Window* window);
	std::vector<Window*> GetWindows();
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	void PushWindow(Window* wnd);
	void PopWindow(Window* window);
	std::vector<Window*> windows;
};

#endif