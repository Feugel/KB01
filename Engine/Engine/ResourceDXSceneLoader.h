#ifndef RESOURCEDXSCENELOADER_H
#define RESOURCEDXSCENELOADER_H

#include "resourcesceneloader.h"

class ResourceDXSceneLoader :
	public ResourceSceneLoader
{
public:
	ResourceDXSceneLoader(void);
	virtual ~ResourceDXSceneLoader(void);
	virtual Scene* LoadFile(std::string fileName);
};

#endif