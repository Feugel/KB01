#include "ResourceDXModelLoader.h"

ResourceDXModelLoader::ResourceDXModelLoader(void)
{
}

ResourceDXModelLoader::~ResourceDXModelLoader(void)
{
	Cleanup();

}

void ResourceDXModelLoader::Cleanup(void)
{

}

ResourceModel* ResourceDXModelLoader::LoadFile(LPCWSTR fileName, VOID* device)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;
	LPD3DXMESH mesh;
	D3DMATERIAL9* materials;
	LPDIRECT3DTEXTURE9* textures;
	DWORD numMaterials = 0L;
	if( FAILED( D3DXLoadMeshFromX( fileName, D3DXMESH_SYSTEMMEM,
									(LPDIRECT3DDEVICE9)device, NULL,
									&pD3DXMtrlBuffer, NULL, &numMaterials,
									&mesh)))
    {
		LogManager::Instance()->Log(LogLevel::WARNING, "%s %s", "Could not find texture map for filename ", fileName);
	}
	D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();
    materials = new D3DMATERIAL9[numMaterials];
	textures = new LPDIRECT3DTEXTURE9[numMaterials];

	for( DWORD i = 0; i < numMaterials; i++ )
    {
        // Copy the material
        materials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
		materials[i].Ambient = materials[i].Diffuse;

        textures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( (LPDIRECT3DDEVICE9)device,
                                                    d3dxMaterials[i].pTextureFilename,
                                                    &textures[i] ) ) )
            {
				LogManager::Instance()->Log(LogLevel::WARNING, "%s %s", "Could not find texture map for filename ", fileName);
            }
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

	ResourceModel* model = new ResourceModel();
	model->SetMaterials(materials);
	model->SetTextures(textures);
	model->SetMesh(mesh);

	return model;
}
