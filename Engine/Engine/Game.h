#ifndef GAME_H
#define GAME_H

#include "LogManager.h"
#include "Kernel.h"

class Game
{
public:
	int Main();
private:
	LogManager* logger;
	Kernel* kernel;
};

#endif