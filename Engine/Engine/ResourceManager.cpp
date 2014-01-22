#include "ResourceManager.h"
#include "ResourceDXTextureLoader.h"
#include "ResourceDXHeightmapLoader.h"
#include "ResourceDXModelLoader.h"

ResourceManager* ResourceManager::instance = NULL;

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

ResourceManager* ResourceManager::Instance()
{
	if(!instance)
		instance = new ResourceManager();
	return instance;
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

ResourceTexture* ResourceManager::GetTexture(std::string fileName, VOID* device)
{
	auto iterator = textures.find(fileName);
	if(iterator != textures.end())
		return iterator->second;

	ResourceTexture* texture = LoadTexture(fileName, device);
	texture->SetFilename(fileName);
	textures.insert(std::make_pair(texture->GetFilename(), texture));
	return texture;
}

ResourceTexture* ResourceManager::LoadTexture(std::string fileName, VOID* device)
{
	return textureLoader->LoadFile(s2ws(fileName).c_str(), device);
}

ResourceModel* ResourceManager::GetModel(std::string fileName, VOID* device)
{
	auto iterator = models.find(fileName);
	if(iterator != models.end())
		return iterator->second;

	ResourceModel* model = LoadModel(fileName, device);
	model->SetFilename(fileName);
	models.insert(std::make_pair(model->GetFilename(), model));
	return model;
}

ResourceModel* ResourceManager::LoadModel(std::string fileName, VOID* device)
{
	return modelLoader->LoadFile(s2ws(fileName).c_str());
}

ResourceHeightmap* ResourceManager::GetHeightmap(std::string fileName, VOID* device)
{
	return LoadHeightmap(fileName, device);
}

ResourceHeightmap* ResourceManager::LoadHeightmap(std::string fileName, VOID* device)
{
	return heightmapLoader->LoadFile(fileName, device);
}

Scene* ResourceManager::GetScene(std::string fileName)
{
	return new Scene();
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