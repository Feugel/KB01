#ifndef TERRAIN_H
#define TERRAIN_H

#ifndef RENDERABLE_H
#include "Renderable.h"
#endif

#ifndef RESOURCEHEIGHTMAP_H
#include "ResourceHeightmap.h"
#endif
#ifndef RESOURCETEXTURE_H
#include "ResourceTexture.h"
#endif

class Terrain : public Renderable
{
public:
	Terrain(void);
	virtual ~Terrain(void);
	void Cleanup();
	void Render();
	ResourceHeightmap* GetHeightmap();
	void SetHeightmap(ResourceHeightmap* heightmap);
	ResourceTexture* GetTexture();
	void SetTexture(ResourceTexture* texture);
private:
	ResourceHeightmap* heightmap;
	ResourceTexture* texture;
};

#endif