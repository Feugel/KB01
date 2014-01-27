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
	//Constructor
	Terrain(void);
	//Destroy this Terrain.
	virtual ~Terrain(void);
	//Clean up the mess a little.
	void Cleanup();
	//Initialize the terrain. Does the actual loading.
	void Initialize(Renderer*);
	//Render the Terrain
	void Render(Renderer*);
	//Get the heightmap
	ResourceHeightmap* GetHeightmap();
	//Set the heightmap.
	void SetHeightmap(ResourceHeightmap*);
	//Set the heightmap filename. Will need to call Initialize afterwards.
	void SetHeightmap(std::string);
	//Get the Terrain texture.
	ResourceTexture* GetTexture();
	//Set the Terrain texture.
	void SetTexture(ResourceTexture*);
	//Set the texture filename. Will need to call Initialize afterwards. 
	void SetTexture(std::string);
private:
	//The heightmap
	ResourceHeightmap* heightmap;
	//The terrain texture
	ResourceTexture* texture;
	//heightmap file name
	std::string heightmapFileName;
	//texture file name
	std::string textureFileName;
};

#endif