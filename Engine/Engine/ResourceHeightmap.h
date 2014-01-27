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
	//Initialize the buffer
	void InitBuffer();
	//Returns a Vertex* (dynamically sized array) with the heightmap data.
	Vertex* GetHeightmapData();
	//Set the heightmap data
	void SetHeightmapData(Vertex* vertices);
	//Returns the heightmapbuffer
	LPDIRECT3DVERTEXBUFFER9 GetHeightmapBuffer();
	//Set the heightmap buffer
	void SetHeightmapBuffer(LPDIRECT3DVERTEXBUFFER9 vertices);
	//Map width
	int width;
	//Map height
	int height;
	//Number of triangles
	int numTriangles;
	//Number of vertices
	int numVertices;
	//The filename for deferred loading
	std::string fileName;
private:
	//The collection of vertices
	Vertex* vertices;
	//actual heightmapbuffer
	LPDIRECT3DVERTEXBUFFER9 heightmapbuffer;
};

#endif