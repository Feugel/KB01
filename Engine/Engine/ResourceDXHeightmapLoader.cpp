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

//ResourceHeightmap* ResourceDXHeightmapLoader::LoadFile(LPCWSTR fileName)
//{
//	BITMAPFILEHEADER bitmapFileHeader;
//	BITMAPINFOHEADER bitmapInfoHeader;
//
//	std::ifstream bitmapFile(fileName, std::ios::binary);
//	if (!bitmapFile)
//	{
//		return NULL;
//	}
//	
//	// Read in file header.
//	bitmapFile.read((char*)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
//	if(bitmapFileHeader.bfType != 0x4d42)
//	{
//		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Specified file is not a Bitmap!");
//	}
//
//	// Read in the bitmap info header.
//	bitmapFile.read((char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
//	if(40 != bitmapInfoHeader.biSize)
//	{
//		LogManager::Instance()->Log(LogLevel::WARNING, "%s", "Specified file's INFO header is larger than 40 bytes!");
//	}
//
//	int width = bitmapInfoHeader.biWidth;
//	int height = bitmapInfoHeader.biHeight;
//	unsigned char* bitmapImage = new unsigned char[width * height * 3];
//	bitmapFile.seekg(bitmapFileHeader.bfOffBits, std::ios::beg);
//
//	// Store the image data.
//	bitmapFile.read((char*)bitmapImage, width * height * 3);
//
//	int numCellsWide = width -1;
//	int numCellsHigh = height -1;
//	int numVerticesWide = width;
//	int numVerticesHigh = height;
//	int numberVertices = width * height;
//	int numberTriangles = numCellsWide * numCellsHigh * 2;
//
//	int cellWidth = 1;
//	int cellHeight = 1;
//
//	// Create the terrain vertices.
//	Vertex* vertices = new Vertex[numberVertices];
//	int k = 0;
//	for (int z = 0; z < numVerticesHigh; z++)
//	{
//		for (int x = 0; x < numVerticesWide; x++)
//		{
//			int index = z * numVerticesWide + x;
//			vertices[index].x = x * cellWidth;
//			vertices[index].y = (float)bitmapImage[k];
//			vertices[index].z = z * cellHeight;
//			vertices[index].tu = vertices[index].x / (numCellsWide * cellWidth);
//			vertices[index].tv = vertices[index].z / (numCellsHigh * cellHeight);
//
//			k += 3;
//		}
//	}
//
//	ResourceHeightmap* heightMap = new ResourceHeightmap();
//	heightMap->SetHeightmapData(vertices);
//	heightMap->width = width;
//	heightMap->height = height;
//	heightMap->numTriangles = numberTriangles;
//	heightMap->numVertices = numberVertices;
//
//	return heightMap;
//}

ResourceHeightmap* ResourceDXHeightmapLoader::LoadFile(std::string fileName)
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
		return false;
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
			LogManager::Instance()->Log("%s", "End of File reached before buffer could be filled entirely.");
		else if (err > 0)
			LogManager::Instance()->Log("%s", "An error occurred while reading the file.");
		//return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	// Create the structure to hold the height map data.
	Vertex* m_heightMap = new Vertex[m_terrainWidth * m_terrainHeight];
	if(!m_heightMap)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k=0;

	// Read the image data into the height map.
	for(j = 0; j < m_terrainHeight; j++)
	{
		for(i = 0; i < m_terrainWidth; i++)
		{
			height = bitmapImage[k];
			
			index = (m_terrainHeight * j) + i;

			m_heightMap[index].x = (float)i;
			m_heightMap[index].y = (float)height;
			m_heightMap[index].z = (float)j;

			k+=3;
		}
	}
	// Release the bitmap image data.
	delete [] bitmapImage;
	bitmapImage = 0;


	ResourceHeightmap* heightMap = new ResourceHeightmap();
	heightMap->SetHeightmapData(m_heightMap);
	heightMap->width = m_terrainWidth;
	heightMap->height = m_terrainHeight;
	heightMap->numTriangles = ((m_terrainHeight - 1) * (m_terrainWidth - 1));
	heightMap->numVertices = m_terrainWidth * m_terrainHeight;

	return heightMap;
}