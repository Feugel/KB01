#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#ifndef ENTITY_H
#include "Entity.h"
#endif

#ifndef RESOURCEMODEL_H
#include "ResourceModel.h"
#endif

class EntityModel :
	public Entity
{
public:
	EntityModel(void);
	virtual ~EntityModel(void);
	void Cleanup();
	void Update(Timer* timer);
	void Render();
	bool CanUpdate;
	bool CanRender;
private:
	ResourceModel* model;
};

#endif