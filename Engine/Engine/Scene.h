#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <map>
#include <algorithm>
#include <vector>

#include "Updatable.h"
#include "Renderable.h"

class LogManager;
class Entity;
class Terrain;
class EntityModel;

class Scene : public Updatable, public Renderable
{
public:
	// constructor
	Scene(void);
	//destructor; calls Cleanup()
	virtual ~Scene(void);
	//Clears the Entities list and cleans up the Terrain.
	void Cleanup();
	virtual void Initialize(Renderer* renderer);
	//Update the Scene's active Entities
	virtual void Update(Timer* timer);
	//Render the renderable Entities
	virtual void Render(Renderer* renderer);
	//Get all Entities in this Scene
	virtual std::map<std::string, Entity*> GetEntities();
	//Add an Entity to the Scene
	virtual void AddEntity(Entity* entity);
	//Remove an entity from the Scene
	virtual void RemoveEntity(Entity* entity);
	//Get the Terrain
	virtual Terrain* GetTerrain();
	//Set the Terrain
	virtual void SetTerrain(Terrain* terrain);
	//Add A model to the scene
	void AddModel(EntityModel* models);
	//Get ModelArray
	std::vector <EntityModel*> GetModels();
	//Set name
	void SetName(std::string);
	//Get Name
	std::string GetName();
	//Get the Scene's status (Active/Inactive)
	bool isActive;
private:
	//The Entities
	std::map<std::string, Entity*> entities;
	//The Terrain
	Terrain* terrain;
	//Models. Should be refactored to std::map<std::string, EntityModel*>
	std::vector <EntityModel*> Models;
	//The Name identifying this Scene
	std::string name;
};

#endif