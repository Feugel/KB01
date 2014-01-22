#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Renderer.h"

class Renderable
{
public:
	virtual void Render(Renderer* renderer) = 0;
};

#endif