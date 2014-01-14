#ifndef RENDERER_H
#define RENDERER_H

//#include <Windows.h>
#include "Window.h"

class Window;

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual void RenderStart();
	virtual void Render();
	virtual void RenderEnd();
	virtual void Present();
	virtual void Init(Window* window);
};

#endif //RENDERER_H

