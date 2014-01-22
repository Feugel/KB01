#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Updatable.h"
#include "Renderable.h"

class Entity : public Updatable
{
public:
	Entity(void);
	virtual ~Entity(void);
	virtual std::string GetName() = 0;
	virtual void Cleanup() = 0;
	virtual void Initialize(Renderer* renderer) = 0;
	virtual void Update(Timer* timer) = 0;
	virtual void Render(Renderer* renderer) = 0;
	virtual bool CanUpdate() = 0;
	virtual bool CanRender() = 0;
};

#endif