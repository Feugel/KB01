#ifndef RESOURCEMODELLOADER_H
#define RESOURCEMODELLOADER_H

#include "ResourceModel.h"

class ResourceModelLoader
{
public:
	ResourceModelLoader(void);
	virtual ~ResourceModelLoader(void);
	virtual void Cleanup() = 0;
	virtual ResourceModel* LoadFile(LPCWSTR fileName) = 0;
};

#endif