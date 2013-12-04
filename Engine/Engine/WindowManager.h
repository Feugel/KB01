#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "Window.h"
#include <vector>

class WindowManager
{
public:
	WindowManager(void);
	virtual ~WindowManager(void);
	void Cleanup();
	bool CreateWnd();
	bool ReleaseWindow();
	std::vector<Window*> GetWindows();
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	void PushWindow(Window* wnd);
	void PopWindow();
	std::vector<Window*> windows;
};

#endif