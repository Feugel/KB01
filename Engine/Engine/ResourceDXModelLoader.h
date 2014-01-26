#ifndef RESOURCEDXMODELLOADER_H
#define RESOURCEDXMODELLOADER_H

#ifndef LOGMANAGER_H
#include "LogManager.h"
#endif
#include "ResourceModelLoader.h"

#include <ostream>

class ResourceDXModelLoader :
	public ResourceModelLoader
{
public:
	ResourceDXModelLoader(void);
	virtual ~ResourceDXModelLoader(void);
	void Cleanup();
	ResourceModel* LoadFile(LPCWSTR fileName, VOID* device);
private:
};

#endif