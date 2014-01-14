#include "ResourceModel.h"


ResourceModel::ResourceModel(void)
{
}


ResourceModel::~ResourceModel(void)
{
	Cleanup();
	delete mesh;
}

void ResourceModel::Cleanup()
{
	if(materials)
		materials = NULL;
	if(textures)
		textures = NULL;
	if(mesh)
		mesh->Release();
}

D3DMATERIAL9* ResourceModel::GetMaterials()
{
	return materials;
}

void ResourceModel::SetMaterials(D3DMATERIAL9* materials)
{
	this->materials = materials;
}

LPDIRECT3DTEXTURE9* ResourceModel::GetTextures()
{
	return textures;
}

void ResourceModel::SetTextures(LPDIRECT3DTEXTURE9* textures)
{
	this->textures = textures;
}

LPD3DXMESH ResourceModel::GetMesh()
{
	return mesh;
}

void ResourceModel::SetMesh(LPD3DXMESH mesh)
{
	this->mesh = mesh;
}