#include "ResourceManager.h"
#include "ResourceDXTextureLoader.h"

ResourceManager::ResourceManager()
{
	//move this to a Set method or specific Initialise function (InitDX, InitOGL etc)
	textureLoader = NULL;
	textureLoader = new ResourceDXTextureLoader();
}

ResourceManager::~ResourceManager()
{
	Cleanup();
	delete textureLoader;
}

void ResourceManager::Cleanup()
{
	if(NULL != textureLoader)
	{
		(*textureLoader).Cleanup();
	}
}

ResourceTexture* ResourceManager::LoadTexture(LPCWSTR fileName)
{
	//if does not exist in list, load from file
	//otherwise, return the one in the list

	//for now, always load new
	return textureLoader->LoadFile(fileName);
}