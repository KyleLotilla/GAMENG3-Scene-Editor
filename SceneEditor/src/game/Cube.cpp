#include "game/Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	Vec3 position_list[] =
	{
		{ Vec3(-0.5f,-0.5f,-0.5f)},
		{ Vec3(-0.5f,0.5f,-0.5f) },
		{ Vec3(0.5f,0.5f,-0.5f) },
		{ Vec3(0.5f,-0.5f,-0.5f)},

		{ Vec3(0.5f,-0.5f,0.5f) },
		{ Vec3(0.5f,0.5f,0.5f) },
		{ Vec3(-0.5f,0.5f,0.5f)},
		{ Vec3(-0.5f,-0.5f,0.5f) }
	};

	Vec2 texcoord_list[] =
	{
		{ Vec2(0.0f,0.0f) },
		{ Vec2(0.0f,1.0f) },
		{ Vec2(1.0f,0.0f) },
		{ Vec2(1.0f,1.0f) }
	};

	VertexTexture vertex_list[] =
	{
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};


	UINT size_list = ARRAYSIZE(vertex_list);
	this->m_vertexBuffer.load(vertex_list, sizeof(VertexTexture), size_list, device);

	unsigned int index_list[] =
	{
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4,
		8,9,10,
		10,11,8,
		12,13,14,
		14,15,12,
		16,17,18,
		18,19,16,
		20,21,22,
		22,23,20
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_indexBuffer.load(index_list, size_index_list, device);
	this->m_constantBuffer.load(&(m_shaderInput), sizeof(DefaultShaderInput), device);
}

void Cube::update(float deltaTime)
{
}