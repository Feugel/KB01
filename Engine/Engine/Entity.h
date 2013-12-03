#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);
	virtual void Cleanup();
};

#endif