#include "ResourceManager.h"
#include "ResourceDXTextureLoader.h"
#include "ResourceDXHeightmapLoader.h"
#include "ResourceDXModelLoader.h"

ResourceManager::ResourceManager()
{
	//move this to a Set method or specific Initialise function (InitDX, InitOGL etc)
	textureLoader = new ResourceDXTextureLoader();
	heightmapLoader = new ResourceDXHeightmapLoader();
	modelLoader = new ResourceDXModelLoader();
}

ResourceManager::~ResourceManager()
{
	Cleanup();
	delete textureLoader;
	delete heightmapLoader;
	delete modelLoader;
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
	if(NULL != modelLoader)
	{
		modelLoader->Cleanup();
	}
	textures.clear();
	models.clear();
}

ResourceTexture* ResourceManager::GetTexture(std::string fileName)
{
	auto iterator = textures.find(fileName);
	if(iterator != textures.end())
		return iterator->second;

	ResourceTexture* texture = LoadTexture(fileName);
	texture->SetFilename(fileName);
	textures.insert(std::make_pair(texture->GetFilename(), texture));
	return texture;
}

ResourceTexture* ResourceManager::LoadTexture(std::string fileName)
{
	return textureLoader->LoadFile(s2ws(fileName).c_str());
}

ResourceModel* ResourceManager::GetModel(std::string fileName)
{
	auto iterator = models.find(fileName);
	if(iterator != models.end())
		return iterator->second;

	ResourceModel* model = LoadModel(fileName);
	model->SetFilename(fileName);
	models.insert(std::make_pair(model->GetFilename(), model));
	return model;
}

ResourceModel* ResourceManager::LoadModel(std::string fileName)
{
	return modelLoader->LoadFile(s2ws(fileName).c_str());
}

ResourceHeightmap* ResourceManager::GetHeightmap(std::string fileName)
{
	return LoadHeightmap(fileName);
}

ResourceHeightmap* ResourceManager::LoadHeightmap(std::string fileName)
{
	return heightmapLoader->LoadFile(s2ws(fileName).c_str());
}

std::wstring ResourceManager::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}