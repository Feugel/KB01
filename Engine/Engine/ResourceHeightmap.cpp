#include "ResourceHeightmap.h"


ResourceHeightmap::ResourceHeightmap(void)
{
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