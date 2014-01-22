#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <strsafe.h>
#include "Renderer.h"
#include "Window.h"



class DXRenderer : public Renderer 
{
public:
	DXRenderer();
	virtual ~DXRenderer(void);
	void Init(Window* window);
	void RenderStart();
	void Render();
	void RenderEnd();
	void Present();
	void* GetDevice();
	
private:
	HRESULT InitD3D();
	HRESULT InitGeometry();
	HRESULT InitHeightMap();
	void Cleanup();
	void SetupMatrices();
	Window* wind;

};

