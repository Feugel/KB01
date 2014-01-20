#include "ResourceTexture.h"
#include <string>

ResourceTexture::ResourceTexture(void)
{
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

std::string ResourceTexture::GetFilename()
{
	return fileName;
}

void ResourceTexture::SetFilename(std::string fileName)
{
	this->fileName = fileName;
}