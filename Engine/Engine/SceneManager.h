#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#ifndef UPDATABLE_H
#include "Updatable.h"
#endif
#ifndef TIMER_H
#include "Timer.h"
#endif
#ifndef ENTITY_H
#include "Entity.h"
#endif

#include <vector>

class SceneManager : public Updatable
{
public:
	SceneManager(void);
	virtual ~SceneManager(void);
	void Cleanup();
	void Update(Timer* timer);
private:
	std::vector<Entity> entities;
};

#endif