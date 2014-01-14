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
		textureLoader->Cleanup();
	}
	if(NULL != heightmapLoader)
	{
		heightmapLoader->Cleanup();
	}
	textures.clear();
	//models.clear();
}

ResourceTexture* ResourceManager::GetTexture(LPCWSTR fileName)
{
	auto iterator = std::find_if(textures.begin(), textures.end(), [&fileName](ResourceTexture* texture) { return std::wcscmp(texture->GetFilename(), fileName) == 0; });
	if(iterator != textures.end())
		return *iterator;

	ResourceTexture* texture = LoadTexture(fileName);
	textures.push_back(texture);
	return texture;
}

ResourceTexture* ResourceManager::LoadTexture(LPCWSTR fileName)
{
	return textureLoader->LoadFile(fileName);
}

ResourceModel* ResourceManager::GetModel(LPCWSTR fileName)
{
	return LoadModel(fileName);
}

ResourceModel* ResourceManager::LoadModel(LPCWSTR fileName)
{
	return NULL;
}

ResourceHeightmap* ResourceManager::GetHeightmap(LPCWSTR fileName)
{
	return LoadHeightmap(fileName);
}

ResourceHeightmap* ResourceManager::LoadHeightmap(LPCWSTR fileName)
{
	return heightmapLoader->LoadFile(fileName);
}

