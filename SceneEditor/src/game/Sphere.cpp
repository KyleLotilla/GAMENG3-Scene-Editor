#include "game/Sphere.h"

void Sphere::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device, int sectorCount, int stackCount, float radius)
{
	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	this->buildVertices(sectorCount, stackCount, radius);
	this->buildIndices(sectorCount, stackCount);

	this->m_vertexBuffer.load(&(this->m_vertices[0]), sizeof(VertexTexture), this->m_vertices.size(), device);
	this->m_indexBuffer.load(&(this->m_indices[0]), this->m_indices.size(), device);
	this->m_constantBuffer.load(&(m_shaderInput), sizeof(DefaultShaderInput), device);
}

void Sphere::buildVertices(int sectorCount, int stackCount, float radius)
{
	float x, y, z, xz, s, t;
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
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			VertexTexture vertex = { Vec3(x, y, z), Vec2(s, t) };
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
