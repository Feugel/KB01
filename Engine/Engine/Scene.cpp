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

void Scene::Initialize(Renderer* renderer)
{
	this->terrain->Initialize(renderer);
	std::for_each(entities.begin(), entities.end(), [renderer](std::pair<std::string, Entity*> item)
	{
		item.second->Initialize(renderer);
	});
}

void Scene::Render(Renderer* renderer)
{
	terrain->Render(renderer);
	std::for_each(entities.begin(), entities.end(), [&renderer](std::pair<std::string, Entity*> item){ if(item.second->CanRender()) item.second->Render(renderer); } );
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
		LogManager::Instance()->Log(LogLevel::INFO, "%s - %s", __FUNCTION__, "This entity has already been added to the current scene!");
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

void Scene::AddModel(EntityModel* models)
{
	Models.push_back(models);
}

std::vector <EntityModel*> Scene::GetModels()
{
	return Models;
}

void Scene::SetName(std::string name)
{
	this->name = name;
}

std::string Scene::GetName()
{
	return this->name;
}