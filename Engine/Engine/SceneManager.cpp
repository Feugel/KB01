#include "SceneManager.h"
#include "Kernel.h"
#include "ResourceManager.h"
#include "Scene.h"

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
	std::for_each(scenes.begin(), scenes.end(), [timer](std::pair<std::string, Scene*> item)
	{
		if(item.second->isActive)
			item.second->Update(timer);
	});
}

void SceneManager::Render()
{
	std::for_each(scenes.begin(), scenes.end(), [] (std::pair<std::string, Scene*> item)
	{
		if(item.second->isActive)
			item.second->Render();
	});
}

Scene* SceneManager::LoadScene(std::string fileName)
{
	//return this->kernel->GetResourceManager()->GetScene(fileName);
	return new Scene();
}