#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#ifndef ENTITY_H
#include "Entity.h"
#endif

class EntityModel :
	public Entity
{
public:
	EntityModel(void);
	virtual ~EntityModel(void);
	void Cleanup();
	void Update(Timer* timer);
};

#endif