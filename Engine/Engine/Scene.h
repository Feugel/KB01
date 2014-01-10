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
	Scene(void);
	virtual ~Scene(void);
	//Clears the Entities list and cleans up the Terrain.
	void Cleanup();
	//Update the Scene's active Entities
	void Update(Timer* timer);
	//Render the renderable Entities
	void Render();
	//Add an Entity to the Scene
	void AddEntity(Entity* entity);
	//Get this Scene's Entities
	std::vector<Entity*> GetEntities();
	//Remove an entity from the Scene
	void RemoveEntity(Entity* entity);
	//Get the Terrain
	Terrain* GetTerrain();
	//Set the Terrain
	void SetTerrain(Terrain* terrain);
	//Get the Scene's status (Active/Inactive)
	bool isActive;
private:
	//The Entities
	std::vector<Entity*> entities;
	//The Terrain
	Terrain* terrain;
	
};

#endif