#include "Terrain.h"
#include "ResourceManager.h"

Terrain::Terrain(void)
{
	
}


Terrain::~Terrain(void)
{
}

void Terrain::Cleanup()
{

}

void Terrain::Initialize(Renderer* renderer)
{
	this->texture = ResourceManager::Instance()->GetTexture(this->textureFileName, renderer->GetDevice());
	this->heightmap = ResourceManager::Instance()->GetHeightmap(this->heightmapFileName, renderer->GetDevice());
}

void Terrain::Render(Renderer* renderer)
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

void Terrain::SetHeightmap(std::string fileName)
{
	this->heightmapFileName = fileName;
}

ResourceTexture* Terrain::GetTexture()
{
	return texture;
}

void Terrain::SetTexture(ResourceTexture* texture)
{
	this->texture = texture;
}

void Terrain::SetTexture(std::string fileName)
{
	this->textureFileName = fileName;
}