#ifndef ENTITYCAMERA_H
#define ENTITYCAMERA_H

#ifndef ENTITY_H
#include "Entity.h"
#endif

#include "InputObserver.h"
#include "InputMouse.h"
#include "InputManager.h"

class EntityCamera :
	public InputObserver, Entity
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
	//std::string GetName();
	//void Notify(MouseStruct mouseStruct, char* keyBuffer);
};

#endif