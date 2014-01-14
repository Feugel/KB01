#ifndef GAME_H
#define GAME_H

#include "LogManager.h"
#include "Kernel.h"
#include "Window.h"

class Game
{
public:
	int Main();
	void initheightmap(Kernel* kernal, Window* window);
private:
	LogManager* logger;
	Kernel* kernel;
};

#endif