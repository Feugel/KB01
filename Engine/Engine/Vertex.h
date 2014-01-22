#ifndef VERTEX_H
#define VERTEX_H

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//Defines a default Vertex
struct Vertex
{ 
	//X, Y and Z position
	float x, y, z;
	//Color
	DWORD color;
	//Texture X
	float tu, tv;
};


#endif