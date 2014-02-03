#ifndef RESOURCEDXTEXTURELOADER_H
#define RESOURCEDXTEXTURELOADER_H

#include "ResourceTextureLoader.h"
#include <d3dx9.h>

class ResourceDXTextureLoader :
	public ResourceTextureLoader
{
public:
	ResourceDXTextureLoader(void);
	ResourceDXTextureLoader(LPDIRECT3DDEVICE9 d3dDevice);
	virtual ~ResourceDXTextureLoader(void);
	void Cleanup(void);
	ResourceTexture* LoadFile(LPCWSTR fileName, void* device);
	void SetDirect3DDevice(LPDIRECT3DDEVICE9 d3dDevice);
private:
	LPDIRECT3DDEVICE9 d3dDevice;
};

#endif