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
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)


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
	// Initialize Direct3D
    if( SUCCEEDED( InitD3D(window) ) )
    {
		// Initialize Heightmap
		if ( SUCCEEDED( InitHeightMap(window) ) ){

		}
    }
}

// actual initializing of directx called by init
HRESULT DXRenderer::InitD3D(Window* window)
{
	HWND hWnd = window->GetWindowHandle();

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

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	//setting the renderstates of the d3d device
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    return S_OK;
}

HRESULT DXRenderer::InitHeightMap(Window* window)
{

	Scene* scene = window->GetManager()->GetSceneByWindow(window);
	if (scene != NULL)
	{
		Terrain* terrain = scene->GetTerrain();

		LogManager::Instance()->Log(LogLevel::INFO, "Starting InitHeightMap");
		//width and height of the heightmap
		int width = 256;
		int height = 256;
		//amount of vertices in the buffer
		int amount = ((width * height -2) * 2 ) + width * 2; 
		CUSTOMVERTEX* g_Vertices = new CUSTOMVERTEX[amount];
		
		std::vector<Vertex*> heightmapdata = terrain->GetHeightmap()->GetHeightmapData();

		//curent position in the array
		int count = 0;

		for(int z = 0; z < height - 1; z++) {
			//if even move the right right
			if ( z % 2 == 0)
			{
				for( int x = 1; x <= width; x ++)
				{
					g_Vertices[count].x = x - 125.0f;
					g_Vertices[count].y = heightmapdata[x + z* 255]->y;
					g_Vertices[count].z = z - 125.0f;
					g_Vertices[count].color = 0xffffffff;
					count ++;
					g_Vertices[count].x = x - 125.0f;
					g_Vertices[count].y = heightmapdata[x + (z + 1)* 255]->y;
					g_Vertices[count].z = z - 124.0f;
					g_Vertices[count].color = 0xffffffff;
					count ++;
				}
			}
			//if odd move to the left
			else
			{
				for( int x = width; x > 0; x --)
				{
					g_Vertices[count].x = x - 125.0f;
					g_Vertices[count].y = heightmapdata[x + z* 255]->y;
					g_Vertices[count].z = z - 125.0f;
					g_Vertices[count].color = 0xffffffff;
					count ++;
					g_Vertices[count].x = x - 125.0f;
					g_Vertices[count].y = heightmapdata[x + (z + 1)* 255]->y;
					g_Vertices[count].z = z - 124.0f;
					g_Vertices[count].color = 0xffffffff;
					count ++;
				}
			}
		
		}
		// Create the vertex buffer.
		if( FAILED( g_pd3dDevice->CreateVertexBuffer( amount * sizeof( CUSTOMVERTEX ),
														0, D3DFVF_CUSTOMVERTEX,
														D3DPOOL_DEFAULT, &g_hVB, NULL ) ) )
		{
			return E_FAIL;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if( FAILED( g_hVB->Lock( 0, amount * sizeof( CUSTOMVERTEX ), ( void** )&pVertices, 0 ) ) )
			return E_FAIL;
		memcpy( pVertices, g_Vertices , amount * sizeof( CUSTOMVERTEX ));
		g_hVB->Unlock();

		return S_OK;
		LogManager::Instance()->Log(LogLevel::INFO, "Finished InitHeightMap");
	} else
	{
		return E_FAIL;
	}

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
	LogManager::Instance()->Log(LogLevel::INFO, "Starting Render");
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
	g_pd3dDevice->BeginScene();
}

//TODO render models and skybox and position camera
//Renders the heightmap
VOID DXRenderer::Render()
{
	LogManager::Instance()->Log(LogLevel::INFO, "Rendering");
	SetupMatrices();

	LogManager::Instance()->Log(LogLevel::INFO, "Rendering Heightmap");
	//setting streamsource to the heightmap
	g_pd3dDevice->SetStreamSource( 0, g_hVB, 0, sizeof( CUSTOMVERTEX ) );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

	//heigt and width of heightmap
	int width = 256;
	int height = 256;
	//amount of triangels in the heightmap
	int amount = (width * 2 -2) * (height - 1);
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, amount);

	LogManager::Instance()->Log(LogLevel::INFO, "Done Rendering");
}

//called after render. calls endscene
VOID DXRenderer::RenderEnd()
{
	LogManager::Instance()->Log(LogLevel::INFO, "Ending Render");
	g_pd3dDevice->EndScene();
}

//presents the backbuffer to the window
VOID DXRenderer::Present()
{
	LogManager::Instance()->Log(LogLevel::INFO, "Present Render");
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
