#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	Cleanup();
	//Delete objects
}

void SceneManager::Cleanup(void)
{
	scenes.clear();
}

void SceneManager::Update(Timer* timer)
{
	for(int i = scenes.size(); i > 0; --i)
	{
		if(scenes[i]->isActive)
			scenes[i]->Update(timer);
	}
}

void SceneManager::Render()
{
	for(int i = scenes.size(); i > 0; --i)
	{
		if(scenes[i]->isActive)
			scenes[i]->Render();
	}
}

std::vector<Scene*> SceneManager::GetActiveScenes()
{
	std::vector<Scene*> active;
	std::for_each(scenes.begin(), scenes.end(), [&active](Scene* scene) { if(scene->isActive) active.push_back(scene); } );
	return active;
}