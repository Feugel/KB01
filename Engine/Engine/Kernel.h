#ifndef KERNEL_H
#define KERNEL_H

#include "ResourceManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "LogManager.h"
//#include "InputManager.h"

class Kernel
{
public:
	Kernel(void);
	virtual ~Kernel(void);
	void Initialise(void);
	void Start(void);
	void Stop(void);
	void Update(void);
	void Render(void);
	WindowManager* GetWindowManager(void);
	ResourceManager* GetResourceManager(void);
	SceneManager* GetSceneManager(void);
	void Cleanup(void);
private:
	ResourceManager* resMan;
	WindowManager* winMan;
	SceneManager* sceneMan;
	bool isFinished;
};
#endif