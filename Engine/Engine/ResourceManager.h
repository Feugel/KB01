#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <algorithm>

#ifndef SCENE_H
#include "Scene.h"
#endif
#ifndef RESOURCETEXTURE_H
#include "ResourceTexture.h"
#endif
#ifndef RESOURCEMODEL_H
#include "ResourceModel.h"
#endif
#ifndef RESOURCEHEIGHTMAP
#include "ResourceHeightmap.h"
#endif

#include "ResourceTextureLoader.h"
#include "ResourceHeightmapLoader.h"
#include "ResourceModelLoader.h"

class ResourceManager
{
public:
	virtual ~ResourceManager(void);
	static ResourceManager* Instance();
	void Cleanup(void);
	void Initialize();
	ResourceTexture* GetTexture(std::string fileName, VOID* device);
	ResourceModel* GetModel(std::string fileName);
	ResourceHeightmap* GetHeightmap(std::string fileName);
	Scene* GetScene(std::string fileName);
private:
	ResourceManager(void);
	ResourceTexture* LoadTexture(std::string fileName, VOID* device);
	ResourceModel* LoadModel(std::string fileName);
	ResourceHeightmap* LoadHeightmap(std::string fileName);
	Scene* LoadScene(std::string fileName);
	std::wstring s2ws(const std::string& s);
	static ResourceManager* instance;
	ResourceTextureLoader* textureLoader;
	ResourceHeightmapLoader* heightmapLoader;
	ResourceModelLoader* modelLoader;
	std::map<std::string, ResourceTexture*> textures;
	std::map<std::string, ResourceModel*> models;
};

#endif