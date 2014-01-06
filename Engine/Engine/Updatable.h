#ifndef UPDATABLE_H
#define UPDATABLE_H

#ifndef TIMER_H
#include "Timer.h"
#endif

class Updatable
{
public:
	virtual void Update(Timer* timer) = 0;
};

#endif