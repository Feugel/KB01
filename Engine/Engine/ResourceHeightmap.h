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
	std::vector<Vertex*> GetHeightmapData(); // To be determined: return data type (vector of struct { float x, float y, float z };?)
	void SetHeightmapData(std::vector<Vertex*> vertices); // Same data type as above.
private:
	std::vector<Vertex*> vertices;
};

#endif