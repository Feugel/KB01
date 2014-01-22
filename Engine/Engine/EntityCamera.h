#ifndef ENTITYCAMERA_H
#define ENTITYCAMERA_H

#ifndef ENTITY_H
#include "Entity.h"
#endif

class EntityCamera :
	public Entity
{
public:
	EntityCamera(void);
	virtual ~EntityCamera(void);
	void Cleanup();
	void Initialize(Renderer* renderer);
	void Update(Timer* timer);
	void Render(Renderer* renderer);
	bool CanUpdate();
	bool CanRender();
};

#endif