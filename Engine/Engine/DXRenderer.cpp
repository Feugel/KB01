#include "DXRenderer.h"
#include <vector>
#include "Vertex.h"
#include "LogManager.h"
#include "Window.h"
#include "WindowManager.h"
#include "Scene.h"

//Terain inports
#include "Terrain.h"
#include "ResourceHeightmap.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices
LPDIRECT3DVERTEXBUFFER9 g_hVB = NULL; // Buffer to hold Heightmapvertices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
	FLOAT tu, tv;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


DXRenderer::DXRenderer()
{	
}

DXRenderer::~DXRenderer(void)
{
	Cleanup();
}

// initializing directx and adding the window to renderer
void DXRenderer::Init(Window* window)
{
	wind = window;
	// Initialize Direct3D
    if( SUCCEEDED( InitD3D() ) )
    {
    }
}

// actual initializing of directx called by init
HRESULT DXRenderer::InitD3D()
{
	HWND hWnd = wind->GetWindowHandle();

    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    //setting up parameters and zeroing memmory
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	//setting the actual parameters
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = 1920;
	d3dpp.BackBufferWidth = 1080;
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	//setting the renderstates of the d3d device
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    return S_OK;
}

//cleanup called by destructor
VOID DXRenderer::Cleanup()
{
	//clear vertex buffer
    if( g_pVB != NULL )
        g_pVB->Release();

	//clear heigtmap vertex buffer
	if( g_hVB != NULL )
        g_hVB->Release();

	//release device
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}


//Sets up the world, view, and projection transform matrices. (still the default from tutorial and has to be replaced)
VOID DXRenderer::SetupMatrices()
{
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

	UINT iTime = timeGetTime() % 100000;
    FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 100000.0f;
    D3DXMatrixRotationY( &matWorld, fAngle );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    D3DXVECTOR3 vEyePt( -255.0f, 350.0f, -255.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 125.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}


//called before render. Clears the backbuffer and calls beginscene
VOID DXRenderer::RenderStart()
{
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Starting Render");
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
	g_pd3dDevice->BeginScene();
}

//TODO render models and skybox and position camera
//Renders the heightmap
VOID DXRenderer::Render()
{
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Rendering");
	SetupMatrices();

	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Rendering Heightmap");
	//setting streamsource to the heightmap
	LPDIRECT3DVERTEXBUFFER9 heightmap = wind->GetManager()->GetSceneByWindow(wind->GetWindowHandle())->GetTerrain()->GetHeightmap()->GetHeightmapBuffer();

	g_pd3dDevice->SetStreamSource( 0, heightmap, 0, sizeof( CUSTOMVERTEX ) );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

	//heigt and width of heightmap
	int width = wind->GetManager()->GetSceneByWindow(wind->GetWindowHandle())->GetTerrain()->GetHeightmap()->width;
	int height = wind->GetManager()->GetSceneByWindow(wind->GetWindowHandle())->GetTerrain()->GetHeightmap()->height;
	//amount of triangels in the heightmap
	int amount = (width * 2 -2) * (height - 1);
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, amount);

	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Done Rendering");
}

//called after render. calls endscene
VOID DXRenderer::RenderEnd()
{
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Ending Render");
	g_pd3dDevice->EndScene();
}

//presents the backbuffer to the window
VOID DXRenderer::Present()
{
	LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "Present Render");
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

VOID* DXRenderer::GetDevice()
{
	return g_pd3dDevice;
}