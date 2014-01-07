#include "DXRenderer.h"
#include "ResourceHeightmap.h"
#include <vector>
#include "Vertex.h"

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
void DXRenderer::Init(HWND hWnd)
{
	// Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Temp for creating a cube (repace by model's and heightmaps
        if( SUCCEEDED( InitGeometry() ) )
        {
	
        }
     }
}

// actual initializing of directx called by init
HRESULT DXRenderer::InitD3D( HWND hWnd )
{
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
	d3dpp.BackBufferHeight = 1280;
	d3dpp.BackBufferWidth = 720;

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

// temp methode to create a cube as model
HRESULT DXRenderer::InitGeometry()
{
   
    CUSTOMVERTEX g_Vertices[] =
    {
		//side 1 (front)
        {  -1.0f,	1.0f,	-1.0f, 0xff0000ff }, 
        {  -1.0f,	-1.0f,	-1.0f, 0xff0000ff }, 
		{  1.0f,	1.0f,	-1.0f, 0xff0000ff }, 
		
		{  1.0f,	1.0f,	-1.0f, 0xff0000ff }, 
        {  -1.0f,	-1.0f,	-1.0f, 0xff0000ff }, 
        {  1.0f,	-1.0f,	-1.0f, 0xff0000ff }, 

		//side 2 (back)
        {  -1.0f,	1.0f,	1.0f, 0xffff0000 }, 
        {  1.0f,	1.0f,	1.0f, 0xffff0000 }, 
        {  -1.0f,	-1.0f,	1.0f, 0xffff0000 }, 

        {  1.0f,	1.0f,	1.0f, 0xffff0000 }, 
        {  1.0f,	-1.0f,	1.0f, 0xffff0000 }, 
		{  -1.0f,	-1.0f,	1.0f, 0xffff0000 }, 

		//side 3 (left)
		{  -1.0f,	1.0f,	-1.0f, 0xff00ff00 }, 
		{  -1.0f,	1.0f,	1.0f,  0xff00ff00 }, 
		{  -1.0f,	-1.0f,	-1.0f, 0xff00ff00 }, 

		{  -1.0f,	-1.0f,	-1.0f, 0xff00ff00 }, 
		{  -1.0f,	1.0f,	1.0f,  0xff00ff00 }, 
		{  -1.0f,	-1.0f,	1.0f,  0xff00ff00 }, 
		
		//side 4 (right)
		{  1.0f,	1.0f,	-1.0f, 0xffffff00 }, 
		{  1.0f,	-1.0f,	-1.0f, 0xffffff00 }, 
		{  1.0f,	1.0f,	1.0f,  0xffffff00 }, 

		{  1.0f,	-1.0f,	-1.0f, 0xffffff00 }, 
		{  1.0f,	-1.0f,	1.0f,  0xffffff00 }, 
		{  1.0f,	1.0f,	1.0f,  0xffffff00 }, 

		//side 5 (top)
		{  -1.0f,	1.0f,	-1.0f, 0xff00ffff }, 
		{  1.0f,	1.0f,	-1.0f, 0xff00ffff }, 
		{  1.0f,	1.0f,	1.0f,  0xff00ffff }, 

		{  -1.0f,	1.0f,	-1.0f, 0xff00ffff }, 
		{  1.0f,	1.0f,	1.0f,  0xff00ffff }, 
		{  -1.0f,	1.0f,	1.0f,  0xff00ffff }, 

		//side 5 (bottom)
		{  -1.0f,	-1.0f,	-1.0f, 0xff00ffff },
		{  1.0f,	-1.0f,	1.0f,  0xff00ffff },
		{  1.0f,	-1.0f,	-1.0f, 0xff00ffff },

		{  1.0f,	-1.0f,	1.0f,  0xff00ffff },
		{  -1.0f,	-1.0f,	-1.0f, 0xff00ffff },
		{  -1.0f,	-1.0f,	1.0f,  0xff00ffff },

    };

    // Create the vertex buffer.
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 36 * sizeof( CUSTOMVERTEX ),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer.
    VOID* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
    g_pVB->Unlock();

    return S_OK;
}


HRESULT DXRenderer::InitHeightMap(ResourceHeightmap* heightmap)
{
		//width and height of the heightmap
		int width = 256;
		int height = 256;
		//amount of vertices in the buffer
		int amount = ((width * height -2) * 2 ) + width * 2; 
		CUSTOMVERTEX* g_Vertices = new CUSTOMVERTEX[amount];
		
		std::vector<Vertex*> heightmapdata = heightmap->GetHeightmapData();


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
		
	
}





//cleanup called by destructor
VOID DXRenderer::Cleanup()
{
    if( g_pVB != NULL )
        g_pVB->Release();

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
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
	g_pd3dDevice->BeginScene();
}

//does the actual rendering. todo render models and heightmap
VOID DXRenderer::Render()
{
	SetupMatrices();
	g_pd3dDevice->SetStreamSource( 0, g_hVB, 0, sizeof( CUSTOMVERTEX ) );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

	//heigt and width of heightmap
	int width = 256;
	int height = 256;
	//amount of vertices in the buffer
	int amount = (width * 2 -2) * (height - 1);
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, amount);
}

//called after render. calls endscene
VOID DXRenderer::RenderEnd()
{
	g_pd3dDevice->EndScene();
}

//presents the backbuffer to the window
VOID DXRenderer::Present()
{
	 g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
