#include "SceneManager.h"
#include "Kernel.h"
#include "ResourceManager.h"
#include "Scene.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	Cleanup();
}

SceneManager* SceneManager::Instance()
{
	if(!instance)
		instance = new SceneManager();
	return instance;
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

void SceneManager::Render(Renderer* renderer)
{
	std::for_each(scenes.begin(), scenes.end(), [&renderer] (std::pair<std::string, Scene*> item)
	{
		if(item.second->isActive)
			item.second->Render(renderer);
	});
}

Scene* SceneManager::LoadScene(std::string fileName, Renderer* renderer)
{
	Scene* scene = ResourceManager::Instance()->GetScene(fileName);
	scene->Initialize(renderer);
	scenes.insert(std::make_pair(scene->GetName(), scene));
	
	return scene;
}