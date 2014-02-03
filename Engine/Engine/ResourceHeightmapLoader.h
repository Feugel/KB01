#ifndef RESOURCEHEIGHTMAPLOADER_H
#define RESOURCEHEIGHTMAPLOADER_H

#include "ResourceHeightmap.h"
#include <string>

class ResourceHeightmapLoader
{
public:
	ResourceHeightmapLoader(void);
	virtual ~ResourceHeightmapLoader(void);
	virtual void Cleanup() = 0;
	/*virtual ResourceHeightmap* LoadFile(LPCWSTR fileName) = 0;*/
	virtual ResourceHeightmap* LoadFile(std::string fileName, void* device) = 0;
};

#endif