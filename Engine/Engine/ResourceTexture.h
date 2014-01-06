#ifndef RESOURCETEXTURE_H
#define RESOURCETEXTURE_H
#include <d3dx9.h>

class ResourceTexture
{
public:
	ResourceTexture(void);
	virtual ~ResourceTexture(void);
	void Cleanup();
	LPDIRECT3DTEXTURE9 GetTexture(void);
	void SetTexture(LPDIRECT3DTEXTURE9 texture);
	LPCWSTR GetFilename();
	void SetFilename(LPCWSTR fileName);
private:
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR fileName;
};

#endif