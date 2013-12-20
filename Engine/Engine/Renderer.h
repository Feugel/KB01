#pragma once
#include <Windows.h>

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual void RenderStart();
	virtual void Render();
	virtual void RenderEnd();
	virtual void Present();
	virtual void Init(HWND hwnd);
};

