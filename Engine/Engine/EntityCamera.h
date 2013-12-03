#ifndef ENTITYCAMERA_H
#define ENTITYCAMERA_H

#include "Entity.h"
class EntityCamera :
	public Entity
{
public:
	EntityCamera(void);
	virtual ~EntityCamera(void);
	void Cleanup();
};

#endif