#ifndef RESOURCEDXHEIGHTMAPLOADER_H
#define RESOURCEDXHEIGHTMAPLOADER_H

#include "ResourceHeightmapLoader.h"
#include <stdio.h>
#include <iostream>

typedef unsigned char BYTE;

class ResourceDXHeightmapLoader :
	public ResourceHeightmapLoader
{
public:
	ResourceDXHeightmapLoader(void);
	virtual ~ResourceDXHeightmapLoader(void);
	ResourceHeightmap* LoadFile(LPCWSTR fileName);
};

#endif