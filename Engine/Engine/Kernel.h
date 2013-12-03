#ifndef KERNEL_H
#define KERNEL_H

#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "LogManager.h"

class Kernel
{
public:
	Kernel(void);
	virtual ~Kernel(void);
	void Initialise(void);
	WindowManager* GetWindowManager(void);
	ResourceManager* GetResourceManager(void);
	SceneManager* GetSceneManager(void);
private:
	void Cleanup(void);
	ResourceManager* resMan;
	WindowManager* winMan;
	SceneManager* sceneMan;
};
#endif