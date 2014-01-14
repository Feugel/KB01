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
#ifndef WINDOW_H
#include "Window.h"
#endif
#ifndef SCENE_H
#include "Scene.h"
#endif

#include <vector>
#include <map>
#include <algorithm>

class Kernel;

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
	Scene* LoadScene(LPCWSTR fileName);
	//Loops through the loaded scenes and returns only the active ones.
	std::vector<Scene*> GetActiveScenes();
	//Update active scenes (implements Updatable)
	void Update(Timer* timer);
	//Render active scenes (implements Renderable)
	void Render();
private:
	//Keep track of the loaded scenes
	std::vector<Scene*> scenes;
	//Kernel
	Kernel* kernel;
};

#endif