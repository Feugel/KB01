#ifndef KERNEL_H
#define KERNEL_H
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"

class Kernel
{
public:

private:
	void Cleanup();
	ResourceManager* resMan;
	WindowManager* winMan;
	SceneManager* sceneMan;
};
#endif