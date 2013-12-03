#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "Entity.h"
class EntityModel :
	public Entity
{
public:
	EntityModel(void);
	virtual ~EntityModel(void);
	void Cleanup();
};

#endif