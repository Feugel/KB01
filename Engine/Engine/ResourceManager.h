#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceTexture.h"
#include "ResourceModel.h"
#include "ResourceHeightmap.h"
#include "ResourceTextureLoader.h"

class ResourceManager
{
public:
	ResourceManager(void);
	virtual ~ResourceManager(void);
	void Cleanup(void);
	ResourceTexture* LoadTexture(LPCWSTR fileName);
	ResourceModel* LoadModel(LPCWSTR fileName);
	ResourceHeightmap* LoadHeightmap(LPCWSTR fileName);
private:
	ResourceTextureLoader* textureLoader;
};

#endif