#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "Entity.h"
#include "Matrix.h"

class ResourceModel;
class ResourceTexture;

class EntityModel : public Entity
{
public:
	EntityModel(std::string name);
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
	void SetModel(ResourceModel*);
	void SetModel(std::string);
	ResourceTexture* GetTexture();
	void SetTexture(ResourceTexture*);
	void SetTexture(std::string);
	bool CanUpdate();
	bool CanRender();
	std::string GetName();
private:
	//The Model's frame
	ResourceModel* model;
	//The texture
	ResourceTexture* texture;
	//Add the position/rotation attributes
	Matrix position;
	//The entities identifying name
	std::string name;
	//The Model file name
	std::string modelFileName;
	//The texture file name
	std::string textureFileName;
};

#endif