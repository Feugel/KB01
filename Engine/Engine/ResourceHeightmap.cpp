#include "ResourceHeightmap.h"
#include "LogManager.h"

ResourceHeightmap::ResourceHeightmap(void)
{
	ZeroMemory(&heightmapbuffer, sizeof(LPDIRECT3DVERTEXBUFFER9));
}


ResourceHeightmap::~ResourceHeightmap(void)
{
	Cleanup();
	delete &this->vertices;
}

void ResourceHeightmap::Cleanup()
{

}

Vertex* ResourceHeightmap::GetHeightmapData()
{
	return vertices;
}

void ResourceHeightmap::SetHeightmapData(Vertex* vertices)
{
	this->vertices = vertices;
}

LPDIRECT3DVERTEXBUFFER9 ResourceHeightmap::GetHeightmapBuffer()
{
	return heightmapbuffer;
}

void ResourceHeightmap::SetHeightmapBuffer(LPDIRECT3DVERTEXBUFFER9 buffer)
{
	heightmapbuffer = buffer;
}