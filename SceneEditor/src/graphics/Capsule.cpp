#include "graphics/Capsule.h"
#include <iostream>

void Capsule::init(VertexShader * vertexShader, PixelShader * pixelShader, ID3D11Device * device, float length, float resolution, float radius)
{
	this->buildVertices(length, resolution, radius);

	this->m_vertexShader = vertexShader;
	this->m_pixelShader = pixelShader;

	this->m_vertexBuffer.load(&(this->m_vertices[0]), sizeof(Vertex), this->m_vertices.size(), device);
	this->m_indexBuffer.load(&(this->m_indices[0]), this->m_indices.size(), device);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();
	this->m_matrices.m_model = identityMatrix;
	this->m_matrices.m_proj = identityMatrix;
	this->m_matrices.m_view = identityMatrix;

	this->m_constantBuffer.load(&(m_matrices), sizeof(CoordinateSystemMatrices), device);
}

void Capsule::update(float deltaTime)
{
}

void Capsule::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
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

void Capsule::release()
{
	this->m_constantBuffer.release();
	this->m_indexBuffer.release();
	this->m_vertexBuffer.release();
}

void Capsule::buildVertices(float length, float resolution, float radius)
{
	this->m_length = length;
	this->m_radius = radius;

	Vec3 start = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 end = Vec3(1.0f, 1.0f, 1.0f);

	Vec3 step = (end - start) / resolution;

	for (float i = 0.0f; i < resolution; i++)
	{
		for (float j = 0.0f; j < resolution; j++)
		{
			float longitude = i * step.m_x + start.m_x;
			float latitude = j * step.m_y + start.m_y;
			float longitudeNext = 0.0f;
			float latitudeNext = 0.0f;

			if (i + 1.0f == resolution)
			{
				longitudeNext = end.m_x;
			}
			else
			{
				longitudeNext = (i + 1.0f) * step.m_x + start.m_x;
			}

			if (j + 1.0f == resolution)
			{
				latitudeNext = end.m_y;
			}
			else
			{
				latitudeNext = (j + 1.0f) * step.m_y + start.m_y;
			}


			int verticesStartIndex = this->m_vertices.size();
			Vertex vertex0 = { this->buildCylinderVertex(longitude, latitude), this->m_color };
			Vertex vertex1 = { this->buildCylinderVertex(longitude, latitudeNext),  this->m_color };
			Vertex vertex2 = { this->buildCylinderVertex(longitudeNext, latitude),  this->m_color };
			Vertex vertex3 = { this->buildCylinderVertex(longitudeNext, latitudeNext),  this->m_color };
			this->m_vertices.push_back(vertex0);
			this->m_vertices.push_back(vertex1);
			this->m_vertices.push_back(vertex2);
			this->m_vertices.push_back(vertex3);
			this->m_indices.push_back(verticesStartIndex);
			this->m_indices.push_back(verticesStartIndex + 2);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 3);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 2);



			verticesStartIndex = this->m_vertices.size();
			vertex0 = { this->buildSphereTopVertex(longitude, latitude), this->m_color };
			vertex1 = { this->buildSphereTopVertex(longitude, latitudeNext),  this->m_color };
			vertex2 = { this->buildSphereTopVertex(longitudeNext, latitude),  this->m_color };
			vertex3 = { this->buildSphereTopVertex(longitudeNext, latitudeNext),  this->m_color };
			this->m_vertices.push_back(vertex0);
			this->m_vertices.push_back(vertex1);
			this->m_vertices.push_back(vertex2);
			this->m_vertices.push_back(vertex3);
			this->m_indices.push_back(verticesStartIndex);
			this->m_indices.push_back(verticesStartIndex + 2);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 3);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 2);

			verticesStartIndex = this->m_vertices.size();
			vertex0 = { this->buildSphereBottomVertex(longitude, latitude), this->m_color };
			vertex1 = { this->buildSphereBottomVertex(longitude, latitudeNext),  this->m_color };
			vertex2 = { this->buildSphereBottomVertex(longitudeNext, latitude),  this->m_color };
			vertex3 = { this->buildSphereBottomVertex(longitudeNext, latitudeNext),  this->m_color };
			this->m_vertices.push_back(vertex0);
			this->m_vertices.push_back(vertex1);
			this->m_vertices.push_back(vertex2);
			this->m_vertices.push_back(vertex3);
			this->m_indices.push_back(verticesStartIndex);
			this->m_indices.push_back(verticesStartIndex + 2);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 3);
			this->m_indices.push_back(verticesStartIndex + 1);
			this->m_indices.push_back(verticesStartIndex + 2);
			
		}
	}
}

Vec3 Capsule::buildCylinderVertex(float longitude, float latitude)
{
	float pi = atan(1) * 4.0f;
	longitude = 2.0f * pi * longitude;
	Vec3 localX = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 localY = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 localZ = Vec3(0.0f, 0.0f, 1.0f);
	Vec3 capsuleBottom = Vec3(0.0f, 0.0f, 0.0f);

	return capsuleBottom
		+ localZ * cosf(longitude) * this->m_radius
		+ localX * sinf(longitude) * this->m_radius
		+ localY * latitude * this->m_length;
}

Vec3 Capsule::buildSphereBottomVertex(float longitude, float latitude)
{
	float pi = atan(1) * 4.0f;
	longitude = 2.0f * pi * longitude;
	latitude = (pi / 2.0f) * (latitude - 1);
	Vec3 localX = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 localY = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 localZ = Vec3(0.0f, 0.0f, 1.0f);
	Vec3 capsuleBottom = Vec3(0.0f, 0.0f, 0.0f);

	return capsuleBottom
		+ localZ * cosf(longitude) * cosf(latitude) * this->m_radius
		+ localX * sinf(longitude) * cosf(latitude) * this->m_radius
		+ localY * sinf(latitude) * this->m_radius;
}

Vec3 Capsule::buildSphereTopVertex(float longitude, float latitude)
{
	float pi = atan(1) * 4.0f;
	longitude = 2.0f * pi * longitude;
	latitude = (pi / 2.0f) * latitude;
	Vec3 localX = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 localY = Vec3(0.0f, 1.0f, 0.0f);
	Vec3 localZ = Vec3(0.0f, 0.0f, 1.0f);
	Vec3 capsuleTop = Vec3(0.0f, this->m_length, 0.0f);

	return capsuleTop
		+ localZ * cosf(longitude) * cosf(latitude) * this->m_radius
		+ localX * sinf(longitude) * cosf(latitude) * this->m_radius
		+ localY * sinf(latitude) * this->m_radius;
}
