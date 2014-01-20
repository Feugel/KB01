#ifndef RESOURCEHEIGHTMAP_H
#define RESOURCEHEIGHTMAP_H

#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

class ResourceHeightmap
{
public:
	//Constructor
	ResourceHeightmap(void);
	//Destructor
	virtual ~ResourceHeightmap(void);
	//Clean up the mess created by this Resource
	void Cleanup();
	//Returns a Vertex* (dynamically sized array) with the heightmap data.
	Vertex* GetHeightmapData();
	//Set the heightmap data
	void SetHeightmapData(Vertex* vertices);
	//Map width
	int width;
	//Map height
	int height;
private:
	//The collection of vertices
	Vertex* vertices;
};

#endif