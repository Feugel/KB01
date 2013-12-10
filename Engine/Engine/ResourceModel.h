#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <d3dx9.h>

class ResourceModel
{
public:
	ResourceModel(void);
	virtual ~ResourceModel(void);
	void Cleanup();
};

#endif