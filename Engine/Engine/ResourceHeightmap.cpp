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
	vertices.clear();
}

std::vector<Vertex*> ResourceHeightmap::GetHeightmapData()
{
	return vertices;
}

void ResourceHeightmap::SetHeightmapData(std::vector<Vertex*> vertices)
{
	if(!this->vertices.empty())
	{
		Cleanup();
	}
	this->vertices = vertices;
}