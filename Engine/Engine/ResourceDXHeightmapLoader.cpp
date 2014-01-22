#include "ResourceDXHeightmapLoader.h"
#include <iomanip>
#include <sstream>

struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
	FLOAT tu, tv;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


ResourceDXHeightmapLoader::ResourceDXHeightmapLoader(void)
{
}


ResourceDXHeightmapLoader::~ResourceDXHeightmapLoader(void)
{
	Cleanup();
}

void ResourceDXHeightmapLoader::Cleanup()
{

}

ResourceHeightmap* ResourceDXHeightmapLoader::LoadFile(std::string fileName, VOID* device)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned char height;
	int m_terrainWidth, m_terrainHeight;

	// Open the height map file in binary.
	error = fopen_s(&filePtr, fileName.c_str(), "rb");
	if(error != 0)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not open heightmap file!");
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not read BITMAPFILEHEADER!");
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not read BITMAPINFOHEADER!");
	}

	// Save the dimensions of the terrain.
	m_terrainWidth = bitmapInfoHeader.biWidth;
	m_terrainHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = m_terrainWidth * m_terrainHeight * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not allocate memory for the image contents!");
	}

	// Move to the beginning of the bitmap data.
	error = fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		int eof = feof(filePtr);
		int err = ferror(filePtr);
		LogManager::Instance()->Log("%s", "Byte count does not match image size. Heightmap will be rendered incorrectly.");
		if(eof > 0)
			LogManager::Instance()->Log("%s %d %s %d", "End of File reached before buffer could be filled entirely. Expected", imageSize, "pixels, found", count);
		else if (err > 0)
			LogManager::Instance()->Log("%s", "An error occurred while reading the file.");
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "An error occurred while closing the file!");
	}

	// Create the structure to hold the height map data.
	Vertex* m_heightMap = new Vertex[m_terrainWidth * m_terrainHeight];
	if(!m_heightMap)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not allocate memory for the heightmap data!");;
	}

	// Initialize the position in the image data buffer.
	k = 0;

	// Read the image data into the height map.
	for(j = 0; j < m_terrainHeight; j++)
	{
		for(i = 0; i < m_terrainWidth; i++)
		{
			height = bitmapImage[k];
			
			index = (m_terrainHeight * j) + i;

			m_heightMap[index].x  = (float) i;
			m_heightMap[index].y  = (float) height;
			m_heightMap[index].z  = (float) j;
			m_heightMap[index].tu = (float) i / m_terrainWidth;
			m_heightMap[index].tv = (float) j / m_terrainHeight;

			k+=3;
		}
	}
	ResourceHeightmap* heightMap = new ResourceHeightmap();
	heightMap->SetHeightmapData(m_heightMap);
	heightMap->width = m_terrainWidth;
	heightMap->height = m_terrainHeight;
	heightMap->numTriangles = ((m_terrainHeight - 1) * (m_terrainWidth - 1));
	heightMap->numVertices = ((m_terrainWidth * m_terrainHeight -2) * 2 ) + m_terrainWidth * 2 /*m_terrainWidth * m_terrainHeight*/;

	CUSTOMVERTEX* g_Vertices = new CUSTOMVERTEX[heightMap->numVertices];
	count = 0;

	for(int z = 0; z < heightMap->height - 1; z++) {
		//if even move the right
		if ( z % 2 == 0)
		{
			for( int x = 1; x <= heightMap->width; x ++)
			{
				g_Vertices[count].x = x - (heightMap->width / 2);
				g_Vertices[count].y = m_heightMap[(x-1) + z * 256].y;
				g_Vertices[count].z = z - (heightMap->height / 2);
				g_Vertices[count].color = 0xffffffff;
				g_Vertices[count].tu = g_Vertices[count].x / heightMap->width;
				g_Vertices[count].tv = g_Vertices[count].z / heightMap->height;
				count ++;
				g_Vertices[count].x = x - (heightMap->width / 2);
				g_Vertices[count].y = m_heightMap[(x -1) + (z + 1) * 256].y;
				g_Vertices[count].z = z - ((heightMap->height / 2) - 1);
				g_Vertices[count].color = 0xffffffff;
				g_Vertices[count].tu = g_Vertices[count].x / heightMap->width;
				g_Vertices[count].tv = g_Vertices[count].z / heightMap->height;
				count ++;
			}
		}
		//if odd move to the left
		else
		{
			for( int x = heightMap->width; x > 0; x --)
			{
				g_Vertices[count].x = x - (heightMap->width / 2);
				g_Vertices[count].y = m_heightMap[(x - 1) + z * 256].y;
				g_Vertices[count].z = z - (heightMap->height / 2);
				g_Vertices[count].color = 0xffffffff;
				g_Vertices[count].tu = g_Vertices[count].x / heightMap->width;
				g_Vertices[count].tv = g_Vertices[count].z / heightMap->height;
				count ++;
				g_Vertices[count].x = x - (heightMap->width / 2);
				g_Vertices[count].y = m_heightMap[(x - 1) + (z + 1) * 256].y;
				g_Vertices[count].z = z - ((heightMap->height / 2) - 1);
				g_Vertices[count].color = 0xffffffff;
				g_Vertices[count].tu = g_Vertices[count].x / heightMap->width;
				g_Vertices[count].tv = g_Vertices[count].z / heightMap->height;
				count ++;
			}
		}
	}
	LPDIRECT3DVERTEXBUFFER9 tmp = NULL;
	// Create the vertex buffer.
	if( FAILED( ((LPDIRECT3DDEVICE9)device)->CreateVertexBuffer( heightMap->numVertices * sizeof( CUSTOMVERTEX ),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &tmp, NULL ) ) )
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not create VertexBuffer!");
	}
	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( tmp->Lock( 0, heightMap->numVertices * sizeof( CUSTOMVERTEX ), ( void** )&pVertices, 0 ) ) )
		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Could not aquire memory lock!");
	memcpy( pVertices, g_Vertices , heightMap->numVertices * sizeof( CUSTOMVERTEX ));
	tmp->Unlock();

	// Release the bitmap image data.
	delete [] bitmapImage;
	bitmapImage = 0;

	heightMap->SetHeightmapBuffer(tmp);

	return heightMap;
}