#pragma once
#include <Windows.h>
#include "ResourceHeightmap.h"

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual HRESULT Renderer::InitHeightMap(ResourceHeightmap* heightmap);
	virtual void RenderStart();
	virtual void Render();
	virtual void RenderEnd();
	virtual void Present();
	virtual void Init(HWND hwnd);
};

