#include "EntityCamera.h"

EntityCamera::EntityCamera(void)
{
	InputManager::Instance()->AddObserver(this);
}

InputObserver::InputObserver(void)
{
}

EntityCamera::~EntityCamera(void)
{
	Cleanup();
}

InputObserver::~InputObserver(void)
{
}

void EntityCamera::Cleanup()
{
	InputManager::Instance()->RemoveObserver(this);
}

void Notify(MouseStruct mouseStruct, char* keyBuffer)
{
	
}

void EntityCamera::Initialize(Renderer* renderer)
{

}

void EntityCamera::Update(Timer* timer)
{

}

void EntityCamera::Render(Renderer* renderer)
{

}

bool EntityCamera::CanUpdate()
{
	return true;
}

bool EntityCamera::CanRender()
{
	return true;
}