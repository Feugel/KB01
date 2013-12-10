#include "ResourceDXModelLoader.h"

ResourceDXModelLoader::ResourceDXModelLoader(void)
{
}

ResourceDXModelLoader::ResourceDXModelLoader(LPDIRECT3DDEVICE9 d3dDevice)
{
	this->d3dDevice = d3dDevice;
}

ResourceDXModelLoader::~ResourceDXModelLoader(void)
{
	Cleanup();
	delete d3dDevice;
}

void ResourceDXModelLoader::Cleanup(void)
{
	d3dDevice->Release();
}

ResourceModel* ResourceDXModelLoader::LoadFile(LPCWSTR fileName)
{
	return new ResourceModel();
}

void ResourceDXModelLoader::SetD3DDevice(LPDIRECT3DDEVICE9 d3dDevice)
{
	this->d3dDevice = d3dDevice;
}
