#ifndef RESOURCESCENELOADER_H
#define RESOURCESCENELOADER_H

#include <string>

class Scene;

class ResourceSceneLoader
{
public:
	ResourceSceneLoader(void);
	virtual ~ResourceSceneLoader(void);
	virtual Scene* LoadFile(std::string fileName) = 0;
};

#endif