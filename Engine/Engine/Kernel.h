#ifndef KERNEL_H
#define KERNEL_H

#include "LogManager.h"
#include "Updatable.h"
#include "Renderable.h"
//#include "InputManager.h"

class WindowManager;
class SceneManager;
class ResourceManager;
class InputManager;

class Kernel : public Updatable, public Renderable
{
public:
	Kernel(void);
	virtual ~Kernel(void);
	void Initialise(void);
	void Start(void);
	void Stop(void);
	void Update(Timer* timer);
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