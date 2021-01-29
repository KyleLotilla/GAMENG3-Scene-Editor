#include "graphics/Cylinder.h"

void Cylinder::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device, int sectorCount, float height, float radius)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	this->buildVertices(sectorCount, height, radius);
	this->buildIndices(sectorCount);

	this->m_vertexBuffer.load(&(this->m_vertices[0]), sizeof(Vertex), this->m_vertices.size(), device);
	this->m_indexBuffer.load(&(this->m_indices[0]), this->m_indices.size(), device);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);
}

void Cylinder::update(float deltaTime)
{
}

void Cylinder::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
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
	modelMatrix = rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix * translateMatrix;

	this->m_matrices.m_model = modelMatrix;
	this->m_matrices.m_proj = viewportParams.m_projection;
	this->m_matrices.m_view = viewportParams.m_view;

	this->m_constantBuffer.update(deviceContext, &m_matrices);

	deviceContext->setVertexShader(this->m_vertexShader);
	deviceContext->setVertexConstantBuffer(this->m_constantBuffer.getBuffer());
	deviceContext->setPixelShader(this->m_pixelShader);
	deviceContext->setVertexBuffer(&(m_vertexBuffer));
	deviceContext->setIndexBuffer(&(m_indexBuffer));
	deviceContext->drawIndexedTriangleList(this->m_indexBuffer.getSizeIndexList(), 0, 0);
}

void Cylinder::release()
{
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
	this->m_vertexBuffer.release();
}

void Cylinder::buildUnitCircleVertices(int sectorCount)
{
	float pi = atan(1) * 4.0f;
	float sectorStep = 2.0f * pi / (float)sectorCount;
	float sectorAngle;

	for (int i = 0; i <= sectorCount; i++)
	{
		sectorAngle = i * sectorStep;
		Vec3 vertex = Vec3(sinf(sectorAngle), 0.0f, cosf(sectorAngle));
		this->m_unitCircleVertices.push_back(vertex);
	}
}

void Cylinder::buildVertices(int sectorCount, float height, float radius)
{
	this->buildUnitCircleVertices(sectorCount);

	for (int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		float t = 1.0f - i;
		int k = 0;

		for (int j = 0; j <= sectorCount; j++)
		{
			Vec3 unitVertex = this->m_unitCircleVertices[k];

			Vertex vertex = {
				Vec3(unitVertex.m_x * radius, h, unitVertex.m_z * radius),
				this->m_color
			};

			this->m_vertices.push_back(vertex);
			k++;
		}
	}

	this->m_baseCenterIndex = this->m_vertices.size();
	this->m_topCenterIndex = this->m_baseCenterIndex + sectorCount + 1;

	for (int i = 0; i < 2; i++)
	{
		float h = -height / 2.0f + i * height;
		Vertex vertex = { Vec3(0.0f, h, 0.0f), this->m_color };
		this->m_vertices.push_back(vertex);
		int k = 0;

		for (int j = 0; j < sectorCount; j++)
		{
			Vec3 unitVertex = this->m_unitCircleVertices[k];

			vertex = {
				Vec3(unitVertex.m_x * radius, h, unitVertex.m_z * radius),
				this->m_color };

			this->m_vertices.push_back(vertex);
			k++;
		}
	}
}

void Cylinder::buildIndices(int sectorCount)
{
	int k1 = 0;
	int k2 = sectorCount + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		this->m_indices.push_back(k1);
		this->m_indices.push_back(k1 + 1);
		this->m_indices.push_back(k2);

		this->m_indices.push_back(k2);
		this->m_indices.push_back(k1 + 1);
		this->m_indices.push_back(k2 + 1);

		k1++;
		k2++;
	}

	int k = this->m_baseCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->m_indices.push_back(this->m_baseCenterIndex);
			this->m_indices.push_back(k + 1);
			this->m_indices.push_back(k);
		}
		else
		{
			this->m_indices.push_back(this->m_baseCenterIndex);
			this->m_indices.push_back(this->m_baseCenterIndex + 1);
			this->m_indices.push_back(k);
		}
		k++;
	}

	k = this->m_topCenterIndex + 1;

	for (int i = 0; i < sectorCount; i++)
	{
		if (i < sectorCount - 1)
		{
			this->m_indices.push_back(this->m_topCenterIndex);
			this->m_indices.push_back(k);
			this->m_indices.push_back(k + 1);
		}
		else
		{
			this->m_indices.push_back(this->m_topCenterIndex);
			this->m_indices.push_back(k);
			this->m_indices.push_back(this->m_topCenterIndex + 1);
		}
		k++;
	}
}
