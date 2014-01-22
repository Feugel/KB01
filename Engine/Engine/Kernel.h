#ifndef KERNEL_H
#define KERNEL_H

#include "Updatable.h"

class LogManager;
class WindowManager;
class SceneManager;
class ResourceManager;
class InputManager;

class Kernel : public Updatable
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
	InputManager* GetInputManager(void);
	void Cleanup(void);
private:
	ResourceManager* resMan;
	WindowManager* winMan;
	SceneManager* sceneMan;
	InputManager* inputMan;
	bool isFinished;
};
#endif