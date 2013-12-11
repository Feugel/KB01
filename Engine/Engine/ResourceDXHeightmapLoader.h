#ifndef RESOURCEDXHEIGHTMAPLOADER_H
#define RESOURCEDXHEIGHTMAPLOADER_H

#include "LogManager.h"
#include "ResourceHeightmapLoader.h"
#include <fstream>
#include "Vertex.h"

typedef unsigned char BYTE;

class ResourceDXHeightmapLoader :
	public ResourceHeightmapLoader
{
public:
	ResourceDXHeightmapLoader(void);
	virtual ~ResourceDXHeightmapLoader(void);
	void Cleanup();
	ResourceHeightmap* LoadFile(LPCWSTR fileName);
};

#endif