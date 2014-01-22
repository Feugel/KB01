#ifndef RESOURCEDXHEIGHTMAPLOADER_H
#define RESOURCEDXHEIGHTMAPLOADER_H

#include "LogManager.h"
#include "ResourceHeightmapLoader.h"
#include <fstream>
#include <string>
#include "Vertex.h"

typedef unsigned char BYTE;

class ResourceDXHeightmapLoader :
	public ResourceHeightmapLoader
{
public:
	ResourceDXHeightmapLoader(void);
	virtual ~ResourceDXHeightmapLoader(void);
	void Cleanup();
	/*ResourceHeightmap* LoadFile(LPCWSTR fileName);*/
	ResourceHeightmap* LoadFile(std::string fileName, VOID* device);
};

#endif