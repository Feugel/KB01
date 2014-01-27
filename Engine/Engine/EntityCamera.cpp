#include "EntityCamera.h"
#include "LogManager.h"

#define KEYDOWN(name, key) (name[key] & 0x80)

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

void EntityCamera::Notify(MouseStruct mouseStruct, char* keyBuffer)
{
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s %d", __FUNCTION__, "Input Mouse Delta X: ",mouseStruct.positionX," captured by EntityCamera");
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s %d", __FUNCTION__, "Input Mouse Delta Y: ",mouseStruct.positionY," captured by EntityCamera");
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