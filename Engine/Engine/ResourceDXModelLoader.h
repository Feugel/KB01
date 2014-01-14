#ifndef RESOURCEDXMODELLOADER_H
#define RESOURCEDXMODELLOADER_H

#ifndef LOGMANAGER_H
#include "LogManager.h"
#endif
#include "ResourceModelLoader.h"

#include <ostream>

class ResourceDXModelLoader :
	public ResourceModelLoader
{
public:
	ResourceDXModelLoader(void);
	ResourceDXModelLoader(LPDIRECT3DDEVICE9 d3dDevice);
	virtual ~ResourceDXModelLoader(void);
	void Cleanup();
	ResourceModel* LoadFile(LPCWSTR fileName);
	void SetD3DDevice(LPDIRECT3DDEVICE9 d3dDevice);
private:
	LPDIRECT3DDEVICE9 d3dDevice;
};

#endif