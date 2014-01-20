#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#ifndef RESOURCETEXTURE_H
#include "ResourceTexture.h"
#endif

class ResourceModel
{
public:
	ResourceModel(void);
	virtual ~ResourceModel(void);
	void Cleanup();
	D3DMATERIAL9* GetMaterials();
	void SetMaterials(D3DMATERIAL9* materials);
	LPD3DXMESH GetMesh();
	void SetMesh(LPD3DXMESH mesh);
	LPDIRECT3DTEXTURE9* GetTextures();
	void SetTextures(LPDIRECT3DTEXTURE9* textures);
	std::string GetFilename();
	void SetFilename(std::string fileName);
private:
	std::string fileName;
	LPD3DXMESH mesh;
	D3DMATERIAL9* materials;
	LPDIRECT3DTEXTURE9* textures;
};

#endif