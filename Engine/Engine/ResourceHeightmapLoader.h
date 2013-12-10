#ifndef RESOURCEHEIGHTMAPLOADER_H
#define RESOURCEHEIGHTMAPLOADER_H

#include "ResourceHeightmap.h"

class ResourceHeightmapLoader
{
public:
	ResourceHeightmapLoader(void);
	virtual ~ResourceHeightmapLoader(void);
	virtual ResourceHeightmap* LoadFile(LPCWSTR fileName) = 0;
};

#endif