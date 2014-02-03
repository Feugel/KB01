#ifndef RESOURCETEXTURELOADER_H
#define RESOURCETEXTURELOADER_H

#include "ResourceTexture.h"

class ResourceTextureLoader
{
public:
	ResourceTextureLoader(void);
	virtual ~ResourceTextureLoader(void);
	virtual void Cleanup() = 0;
	virtual ResourceTexture* LoadFile(LPCWSTR fileName, void* device) = 0;
};

#endif