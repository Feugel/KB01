#ifndef RESOURCETEXTURE_H
#define RESOURCETEXTURE_H
#include <d3dx9.h>
#include <string>

class ResourceTexture
{
public:
	ResourceTexture(void);
	virtual ~ResourceTexture(void);
	void Cleanup();
	LPDIRECT3DTEXTURE9 GetTexture(void);
	void SetTexture(LPDIRECT3DTEXTURE9 texture);
	std::string GetFilename();
	void SetFilename(std::string fileName);
private:
	LPDIRECT3DTEXTURE9 texture;
	std::string fileName;
};

#endif