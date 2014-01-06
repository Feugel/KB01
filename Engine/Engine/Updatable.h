#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "Timer.h"

class Updatable
{
public:
	virtual void Update(Timer* timer) = 0;
};

#endif