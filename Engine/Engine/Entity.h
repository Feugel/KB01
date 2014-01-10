#ifndef ENTITY_H
#define ENTITY_H

#ifndef UPDATABLE_H
#include "Updatable.h"
#endif
#ifndef RENDERABLE_H
#include "Renderable.h"
#endif
#ifndef TIMER_H
#include "Timer.h"
#endif

class Entity : public Updatable
{
public:
	Entity(void);
	virtual ~Entity(void);
	virtual void Cleanup() = 0;
	virtual void Update(Timer* timer) = 0;
	virtual void Render() = 0;
	virtual bool CanUpdate() = 0;
	virtual bool CanRender() = 0;
};

#endif