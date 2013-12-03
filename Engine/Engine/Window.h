#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <windowsx.h>

class Window
{
     private:
          HWND hWnd;
          HINSTANCE hInst;
          WNDCLASSEX Wnd;
     public:
          Window(HINSTANCE hIns);
		  virtual ~Window();
		  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		  void Cleanup();

//	Window(void);
//	Window(int width, int height, char* title, bool fullscreen);
//	virtual ~Window(void);
//	virtual void Cleanup(void);
//	WNDCLASSEX GetWindow(void);
//	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//private:
//	WNDCLASSEX Create(int width, int height, char* title, bool fullscreen);
//	HWND hWnd;
//	HDC hDC;
//    HGLRC hRC;
//	WNDCLASSEX window;
};

#endif