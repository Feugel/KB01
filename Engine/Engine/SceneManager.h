#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#ifndef UPDATABLE_H
#include "Updatable.h"
#endif
#ifndef RENDERABLE_H
#include "Renderable.h"
#endif

#ifndef TIMER_H
#include "Timer.h"
#endif

#include <map>
#include <algorithm>

class Kernel;
class Scene;

class SceneManager : public Updatable, public Renderable
{
public:
	//Create a SceneManager
	SceneManager(void);
	//Destroy this SceneManager
	virtual ~SceneManager(void);
	//Clean up the mess
	void Cleanup();
	//Load a Scene
	Scene* LoadScene(std::string fileName);
	//Update active scenes (implements Updatable)
	void Update(Timer* timer);
	//Render active scenes (implements Renderable)
	void Render();
private:
	//Keep track of the loaded scenes
	std::map<std::string, Scene*> scenes;
	//Kernel
	Kernel* kernel;
};

#endif