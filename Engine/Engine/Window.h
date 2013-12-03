#include <windows.h>
#include <windowsx.h>
class Window
{
public:
	virtual ~Window(void);
	virtual void Cleanup();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Create(int width, int height, char* title, bool fullscreen);
private:
	HWND hWnd;
	HDC hDC;
    HGLRC hRC;
};

