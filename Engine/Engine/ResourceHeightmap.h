#ifndef RESOURCEHEIGHTMAP_H
#define RESOURCEHEIGHTMAP_H

#include <d3dx9.h>

class ResourceHeightmap
{
public:
	ResourceHeightmap(void);
	virtual ~ResourceHeightmap(void);
	void Cleanup();
	void GetHeightmapData(); // To be determined: return data type (vector of struct { float x, float y, float z };?)
	void SetHeightmapData(); // Same data type as above.
private:
	
};

#endif