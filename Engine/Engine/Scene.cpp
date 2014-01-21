#include "Scene.h"
#include "LogManager.h"
#include "Entity.h"
#include "Terrain.h"

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
	terrain->Render();
	std::for_each(entities.begin(), entities.end(), [](std::pair<std::string, Entity*> item){ if(item.second->CanRender()) item.second->Render(); } );
}

void Scene::Update(Timer* timer)
{
	std::for_each(entities.begin(), entities.end(), [timer](std::pair<std::string, Entity*> item){ if(item.second->CanUpdate()) item.second->Update(timer); } );
}

void Scene::AddEntity(Entity* entity)
{
	auto iterator = entities.find(entity->GetName());
	if(iterator != entities.end())
	{
		LogManager::Instance()->Log(LogLevel::INFO, "%s", "This entity has already been added to the current scene!");
	}
	else
	{
		entities.erase(entity->GetName()); // map might add a key when using Find.
		entities.insert(std::make_pair(entity->GetName(), entity));
	}
}

std::map<std::string, Entity*> Scene::GetEntities()
{
	return entities;
}

void Scene::RemoveEntity(Entity* entity)
{
	entities.erase(entity->GetName());
}

Terrain* Scene::GetTerrain()
{
	return terrain;
}

void Scene::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}