#pragma once
#include "DefaultGraphicsPrimitive.h"

class Capsule : public DefaultGraphicsPrimitive
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, float length, float resolution, float radius);
	virtual void update(float deltaTime);

private:
	void buildVertices(float length, float resolution, float radius);
	Vec3 buildCylinderVertex(float longitude, float latitude);
	Vec3 buildSphereTopVertex(float longitude, float latitude);
	Vec3 buildSphereBottomVertex(float longitude, float latitude);

	float m_length;
	float m_radius;
	std::vector<VertexTexture> m_vertices;
	std::vector<unsigned int> m_indices;
};
