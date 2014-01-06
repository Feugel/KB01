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

}

void SceneManager::Update(Timer* timer)
{
	for(int i = entities.size(); i > 0; --i)
	{
		entities[i].Update(timer);
	}
}