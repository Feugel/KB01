#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
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
	ResourceManager(void);
	virtual ~ResourceManager(void);
	void Cleanup(void);
	void Initialize();
	ResourceTexture* GetTexture(LPCWSTR fileName);
	ResourceModel* GetModel(LPCWSTR fileName);
	ResourceHeightmap* GetHeightmap(LPCWSTR fileName);
	Scene* GetScene(LPCWSTR fileName);
private:
	ResourceTexture* LoadTexture(LPCWSTR fileName);
	ResourceModel* LoadModel(LPCWSTR fileName);
	ResourceHeightmap* LoadHeightmap(LPCWSTR fileName);
	Scene* LoadScene(LPCWSTR fileName);
	ResourceTextureLoader* textureLoader;
	ResourceHeightmapLoader* heightmapLoader;
	ResourceModelLoader* modelLoader;
	std::vector<ResourceTexture*> textures;
	std::vector<ResourceModel*> models;
};

#endif