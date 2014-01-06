#include "ResourceTexture.h"


ResourceTexture::ResourceTexture(void)
{
	ZeroMemory(texture, sizeof(texture));
}


ResourceTexture::~ResourceTexture(void)
{
	if(NULL != this->texture)
		this->texture->Release();
}

void ResourceTexture::Cleanup()
{
	if(NULL != this->texture)
		this->texture->Release();
}
LPDIRECT3DTEXTURE9 ResourceTexture::GetTexture(void)
{
	return this->texture;
}
void ResourceTexture::SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;
}

LPCWSTR ResourceTexture::GetFilename()
{
	return fileName;
}

void ResourceTexture::SetFilename(LPCWSTR fileName)
{
	this->fileName = fileName;
}