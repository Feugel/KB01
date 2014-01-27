#include "EntityModel.h"
#include "ResourceModel.h"

EntityModel::EntityModel(void)
{
	
}


EntityModel::~EntityModel(void)
{
}

void EntityModel::Initialize(Renderer* renderer)
{

}

void EntityModel::Cleanup()
{

}

void EntityModel::Update(Timer* timer)
{

}

void EntityModel::Render(Renderer* renderer)
{

}

Matrix EntityModel::GetPosition()
{
	return position;
}

void EntityModel::SetPosition(Matrix pos)
{
	position = pos;
}

float EntityModel::GetHRotation()
{
	return position.rotation_h;
}

void EntityModel::SetHRotation(float rotation)
{
	position.rotation_h = rotation;
}

float EntityModel::GetVRotation()
{
	return position.rotation_v;
}

void EntityModel::SetVRotation(float rotation)
{
	position.rotation_v = rotation;
}

ResourceModel* EntityModel::GetModel()
{
	return model;
}

void EntityModel::SetModel(ResourceModel* model)
{
	this->model = model;
}

std::string EntityModel::GetName()
{
	return NULL;
}

bool EntityModel::CanUpdate()
{
	return false;
}

bool EntityModel::CanRender()
{
	return true;
}