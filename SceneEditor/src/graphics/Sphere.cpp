#include "graphics/Sphere.h"

void Sphere::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device, int sectorCount, int stackCount, float radius)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	this->buildVertices(sectorCount, stackCount, radius);
	this->buildIndices(sectorCount, stackCount);

	this->m_vertexBuffer.load(&(this->m_vertices[0]), sizeof(Vertex), this->m_vertices.size(), device);
	this->m_indexBuffer.load(&(this->m_indices[0]), this->m_indices.size(), device);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
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

void Sphere::release()
{
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
	this->m_vertexBuffer.release();
}

void Sphere::buildVertices(int sectorCount, int stackCount, float radius)
{
	float x, y, z, xz;
	float pi = atan(1) * 4.0f;
	float sectorStep = 2 * pi / (float)sectorCount;
	float stackStep = pi / (float)stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; i++)
	{
		stackAngle = pi / 2.0f - i * stackStep;
		xz = radius * cosf(stackAngle);
		y = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; j++)
		{
			sectorAngle = j * sectorStep;
			z = xz * cosf(sectorAngle);
			x = xz * sinf(sectorAngle);
			Vertex vertex = { Vec3(x, y, z), this->m_color };
			this->m_vertices.push_back(vertex);
		}
	}

}

void Sphere::buildIndices(int sectorCount, int stackCount)
{
	int k1, k2;

	for (int i = 0; i < stackCount; i++)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; j++)
		{
			if (i != 0)
			{
				this->m_indices.push_back(k1);
				this->m_indices.push_back(k1 + 1);
				this->m_indices.push_back(k2);
			}

			if (i != (stackCount - 1))
			{
				this->m_indices.push_back(k1 + 1);
				this->m_indices.push_back(k2 + 1);
				this->m_indices.push_back(k2);
			}

			k1++;
			k2++;
		}
	}
}
