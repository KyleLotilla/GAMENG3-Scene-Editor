#include "graphics/Cube.h"

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

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);

	/*
	this->m_animSpeed = (float)(rand() % 11 + 10);
	int randomDir = rand() % 101;
	if (randomDir > 50)
	{
		this->m_increasing = true;
	}
	else
	{
		this->m_increasing = false;
	}
	*/
}

void Cube::setTexture(Texture * texture)
{
	this->m_texture = texture;
}

void Cube::update(float deltaTime)
{
	/*
	if (m_increasing)
	{
		this->m_localRotation.m_x += deltaTime * this->m_animSpeed;
		this->m_localRotation.m_y += deltaTime * this->m_animSpeed;
		this->m_localRotation.m_z += deltaTime * this->m_animSpeed;
	}
	else
	{
		this->m_localRotation.m_x -= deltaTime * this->m_animSpeed;
		this->m_localRotation.m_y -= deltaTime * this->m_animSpeed;
		this->m_localRotation.m_z -= deltaTime * this->m_animSpeed;
	}

	int randomize = rand() % 100 + 1;
	if (randomize > 95)
	{
		this->m_animSpeed = (float)(rand() % 11 + 10);
		int randomDir = rand() % 101;
		if (randomDir > 95)
		{
			this->m_increasing = !this->m_increasing;
		}
	}
	*/
}

void Cube::draw(DeviceContext* deviceContext, ViewportParams viewportParams)
{
	Mat4 modelMatrix;
	Mat4 translateMatrix;
	Mat4 scaleMatrix;
	Mat4 rotationXMatrix;
	Mat4 rotationYMatrix;
	Mat4 rotationZMatrix;

	scaleMatrix.setScale(this->m_localScale);
	rotationZMatrix.setRotationZ(this->m_localRotation.m_z);
	rotationYMatrix.setRotationY(this->m_localRotation.m_y);
	rotationXMatrix.setRotationX(this->m_localRotation.m_x);
	translateMatrix.setTranslation(this->m_localPosition);
	modelMatrix =  rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix * translateMatrix;

	this->m_matrices.m_model = modelMatrix;
	this->m_matrices.m_proj = viewportParams.m_projection;
	this->m_matrices.m_view = viewportParams.m_view;

	this->m_constantBuffer.update(deviceContext, &m_matrices);

	deviceContext->setVertexShader(this->m_vertexShader);
	deviceContext->setVertexConstantBuffer(this->m_constantBuffer.getBuffer());
	deviceContext->setPixelShader(this->m_pixelShader);
	deviceContext->setVertexBuffer(&(m_vertexBuffer));
	deviceContext->setIndexBuffer(&(m_indexBuffer));
	deviceContext->setTexture(this->m_texture);
	deviceContext->drawIndexedTriangleList(this->m_indexBuffer.getSizeIndexList(), 0, 0);
}

void Cube::release()
{
	this->m_vertexBuffer.release();
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
	this->m_texture->release();
	delete m_texture;
}
