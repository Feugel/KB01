#ifndef RESOURCEHEIGHTMAP_H
#define RESOURCEHEIGHTMAP_H

#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

class ResourceHeightmap
{
public:
	ResourceHeightmap(void);
	virtual ~ResourceHeightmap(void);
	void Cleanup();
	std::vector<Vertex*> GetHeightmapData(); // return data type: vector of struct { float x, float y, float z, float tu, float tv };
	void SetHeightmapData(std::vector<Vertex*> vertices);
private:
	std::vector<Vertex*> vertices;
};

#endif