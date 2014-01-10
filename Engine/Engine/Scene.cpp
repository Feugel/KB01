#include "Scene.h"


Scene::Scene(void)
{
	isActive = false;
}


Scene::~Scene(void)
{
	Cleanup();
}

void Scene::Cleanup()
{
	entities.clear();
	terrain->Cleanup();
}

void Scene::Render()
{
	for(int i = entities.size(); i > 0; --i)
	{
		terrain->Render();
		if(entities[i]->CanRender())
			entities[i]->Render();
	}
}

void Scene::Update(Timer* timer)
{
	for(int i = entities.size(); i > 0; --i)
	{
		if(entities[i]->CanUpdate())
			entities[i]->Update(timer);
	}
}

void Scene::AddEntity(Entity* entity)
{
	auto iterator = std::find_if(entities.begin(), entities.end(), [&entity](Entity* ent) { return true; });
	if(iterator != entities.end())
	{
		LogManager::Instance()->Log(LogLevel::INFO, "This entity has already been added to the current scene!");
	}
	else
		entities.push_back(entity);
}

std::vector<Entity*> Scene::GetEntities()
{
	return entities;
}

void Scene::RemoveEntity(Entity* entity)
{
	auto item = std::find(entities.begin(), entities.end(), entity);
	entities.erase(item, item+1);
}

Terrain* Scene::GetTerrain()
{
	return terrain;
}

void Scene::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}