#include "ResourceDXTextureLoader.h"

ResourceDXTextureLoader::ResourceDXTextureLoader(void)
{

}

ResourceDXTextureLoader::ResourceDXTextureLoader(LPDIRECT3DDEVICE9 d3dDevice)
{
	this->d3dDevice = d3dDevice;
}

ResourceDXTextureLoader::~ResourceDXTextureLoader(void)
{

}

void ResourceDXTextureLoader::Cleanup()
{

}

ResourceTexture* ResourceDXTextureLoader::LoadFile(LPCWSTR fileName)
{
	LPDIRECT3DTEXTURE9 texture;

	D3DXCreateTextureFromFile(this->d3dDevice, fileName, &texture);
	
	this->d3dDevice->SetTexture(0, texture);

	this->d3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	this->d3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	this->d3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	ResourceTexture* tex = new ResourceTexture();
	(*tex).SetTexture(texture);
	
	return tex;
}

void ResourceDXTextureLoader::SetDirect3DDevice(LPDIRECT3DDEVICE9 d3dDevice)
{
	this->d3dDevice = d3dDevice;
}