#include "ResourceManager.h"
#include "ResourceDXTextureLoader.h"
#include "ResourceDXHeightmapLoader.h"

ResourceManager::ResourceManager()
{
	//move this to a Set method or specific Initialise function (InitDX, InitOGL etc)
	textureLoader = NULL;
	textureLoader = new ResourceDXTextureLoader();
	heightmapLoader = NULL;
	heightmapLoader = new ResourceDXHeightmapLoader();
}

ResourceManager::~ResourceManager()
{
	Cleanup();
	delete textureLoader;
	delete heightmapLoader;
}

void ResourceManager::Cleanup()
{
	if(NULL != textureLoader)
	{
		(*textureLoader).Cleanup();
	}
	if(NULL != heightmapLoader)
	{
		(*heightmapLoader).Cleanup();
	}
}

ResourceTexture* ResourceManager::LoadTexture(LPCWSTR fileName)
{
	//if does not exist in list, load from file
	//otherwise, return the one in the list

	//for now, always load new
	return textureLoader->LoadFile(fileName);
}

ResourceHeightmap* ResourceManager::LoadHeightmap(LPCWSTR fileName)
{
	return heightmapLoader->LoadFile(fileName);
}