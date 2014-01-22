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
	void Initialize(Renderer* renderer);
	void Update(Timer* timer);
	void Render(Renderer* renderer);
	void GetPosition(); // return matrix with x, y, z
	void SetPosition();
	void GetRotation(); // return float with degrees / radians
	void SetRotation();
	ResourceModel* GetModel();
	void SetModel(ResourceModel* model);
	bool CanUpdate;
	bool CanRender;
private:
	ResourceModel* model;
	//add the position/rotation attributes
	float x, y, z, rotation_x, rotation_y, scale;
};

#endif