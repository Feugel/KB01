#pragma once
#include <Windows.h>

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual void Render();
	virtual void Init(HWND hwnd);
};

