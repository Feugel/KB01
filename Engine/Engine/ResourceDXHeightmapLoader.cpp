#include "ResourceDXHeightmapLoader.h"
#include <iomanip>
#include <sstream>

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

ResourceHeightmap* ResourceDXHeightmapLoader::LoadFile(LPCWSTR fileName)
{
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;

	std::ifstream bitmapFile(fileName, std::ios::binary);
	if (!bitmapFile)
	{
		return NULL;
	}
	
	// Read in file header.
	bitmapFile.read((char*)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	if(bitmapFileHeader.bfType != 0x4d42)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Specified file is not a Bitmap!");
	}

	// Read in the bitmap info header.
	bitmapFile.read((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
	if(40 != bitmapInfoHeader.biSize)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "Specified file's INFO header is larger than 40 bytes!");
	}

	int width = bitmapInfoHeader.biWidth;
	int height = bitmapInfoHeader.biHeight;
	unsigned char* bitmapImage = new unsigned char[width * height * 3];
	bitmapFile.seekg(bitmapFileHeader.bfOffBits, std::ios::beg);

	// Store the image data.
	bitmapFile.read((char*)bitmapImage, width * height * 3);

	int numCellsWide = width -1;
	int numCellsHigh = height -1;
	int numVerticesWide = width;
	int numVerticesHigh = height;
	int numberVertices = width * height;
	int numberTriangles = numCellsWide * numCellsHigh * 2;

	int cellWidth = 1;
	int cellHeight = 1;

	// Create the terrain vertices.
	Vertex* vertices = new Vertex[numberVertices];
	int k = 0;
	for (int z = 0; z < numVerticesHigh; z++)
	{
		for (int x = 0; x < numVerticesWide; x++)
		{
			int index = z * numVerticesWide + x;
			vertices[index].x = x * cellWidth;
			vertices[index].y = (float)bitmapImage[k];
			vertices[index].z = z * cellHeight;
			vertices[index].tu = vertices[index].x / (numCellsWide * cellWidth);
			vertices[index].tv = vertices[index].z / (numCellsHigh * cellHeight);

			k += 3;
		}
	}

	ResourceHeightmap* heightMap = new ResourceHeightmap();
	heightMap->SetHeightmapData(vertices);
	heightMap->width = width;
	heightMap->height = height;

	return heightMap;
}