#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <algorithm>

#ifndef RESOURCETEXTURE_H
#include "ResourceTexture.h"
#endif
#ifndef RESOURCEMODEL_H
#include "ResourceModel.h"
#endif
#ifndef RESOURCEHEIGHTMAP
#include "ResourceHeightmap.h"
#endif
#ifndef MANAGER_H
#include "Manager.h"
#endif

#include "ResourceTextureLoader.h"
#include "ResourceHeightmapLoader.h"

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
private:
	ResourceTexture* LoadTexture(LPCWSTR fileName);
	ResourceModel* LoadModel(LPCWSTR fileName);
	ResourceHeightmap* LoadHeightmap(LPCWSTR fileName);
	ResourceTextureLoader* textureLoader;
	ResourceHeightmapLoader* heightmapLoader;
	//ResourceModelLoader* modelLoader;
	std::vector<ResourceTexture*> textures;
};

#endif