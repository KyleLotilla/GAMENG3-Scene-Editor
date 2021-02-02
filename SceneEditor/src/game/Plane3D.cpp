#include "game/Plane3D.h"

Plane3D::Plane3D()
{
	this->m_localScale = Vec3(1.0f, 0.2f, 1.0f);
}

Plane3D::~Plane3D()
{
}
/*
void Plane3D::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	Vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vec3(-0.5f,-0.01f,-0.5f),    Vec3(1,1,1)},
		{Vec3(-0.5f,0.01f,-0.5f),    Vec3(1,1,1)},
		{ Vec3(0.5f,0.01f,-0.5f),   Vec3(1,1,1)},
		{ Vec3(0.5f,-0.01f,-0.5f),     Vec3(1,1,1)},

		//BACK FACE
		{ Vec3(0.5f,-0.01f,0.5f),    Vec3(1,1,1)},
		{ Vec3(0.5f,0.01f,0.5f),    Vec3(1,1,1)},
		{ Vec3(-0.5f,0.01f,0.5f),   Vec3(1,1,1)},
		{ Vec3(-0.5f,-0.01f,0.5f),     Vec3(1,1,1)}

	};

	UINT size_list = ARRAYSIZE(vertex_list);
	this->m_vertexBuffer.load(vertex_list, sizeof(Vertex), size_list, device);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_indexBuffer.load(index_list, size_index_list, device);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);
}
*/