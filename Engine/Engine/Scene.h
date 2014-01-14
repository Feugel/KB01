#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <algorithm>

#ifndef LOGMANAGER_H
#include "LogManager.h"
#endif

#ifndef UPDATABLE_H
#include "Updatable.h"
#endif

#ifndef RENDERABLE_H
#include "Renderable.h"
#endif

#ifndef ENTITY_H
#include "Entity.h"
#endif
#ifndef TERRAIN_H
#include "Terrain.h"
#endif

class Scene : public Updatable, public Renderable
{
public:
	// constructor
	Scene(void);
	//destructor; calls Cleanup()
	virtual ~Scene(void);
	//Clears the Entities list and cleans up the Terrain.
	void Cleanup();
	//Update the Scene's active Entities
	virtual void Update(Timer* timer);
	//Render the renderable Entities
	virtual void Render();
	//Get all Entities in this Scene
	virtual std::vector<Entity*> GetEntities();
	//Add an Entity to the Scene
	virtual void AddEntity(Entity* entity);
	//Remove an entity from the Scene
	virtual void RemoveEntity(Entity* entity);
	//Get the Terrain
	virtual Terrain* GetTerrain();
	//Set the Terrain
	virtual void SetTerrain(Terrain* terrain);
	//Get the Scene's status (Active/Inactive)
	bool isActive;
private:
	//The Entities
	std::vector<Entity*> entities;
	//The Terrain
	Terrain* terrain;
	
};

#endif