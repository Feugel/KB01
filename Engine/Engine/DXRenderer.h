#include "Renderer.h"
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <strsafe.h>


class DXRenderer : public Renderer 
{
public:
	DXRenderer();
	virtual ~DXRenderer(void);
	void Init(HWND hwnd);
	void RenderStart();
	void Render();
	void RenderEnd();
	void Present();

	
private:
	HRESULT InitD3D( HWND hWnd );
	HRESULT InitGeometry();
	void Cleanup();
	void SetupMatrices();


};

