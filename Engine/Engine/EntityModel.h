#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "Entity.h"
#include "Matrix.h"

class ResourceModel;

class EntityModel : public Entity
{
public:
	EntityModel(void);
	virtual ~EntityModel(void);
	void Cleanup();
	void Initialize(Renderer* renderer);
	void Update(Timer* timer);
	void Render(Renderer* renderer);
	Matrix GetPosition();
	void SetPosition(Matrix position);
	float GetHRotation();
	void SetHRotation(float rotation);
	float GetVRotation();
	void SetVRotation(float rotation);
	ResourceModel* GetModel();
	void SetModel(ResourceModel* model);
	bool CanUpdate();
	bool CanRender();
	std::string GetName();
	
private:
	ResourceModel* model;
	//add the position/rotation attributes
	Matrix position;
};

#endif