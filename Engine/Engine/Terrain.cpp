#include "Terrain.h"


Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}

void Terrain::Cleanup()
{

}

void Terrain::Render()
{

}

ResourceHeightmap* Terrain::GetHeightmap()
{
	return heightmap;
}

void Terrain::SetHeightmap(ResourceHeightmap* heightmap)
{
	this->heightmap = heightmap;
}

ResourceTexture* Terrain::GetTexture()
{
	return texture;
}

void Terrain::SetTexture(ResourceTexture* texture)
{
	this->texture = texture;
}