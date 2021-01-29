#pragma once
#include "game/GameObject.h"
#include "math/Vec3.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"
#include "graphics/ConstantBuffer.h"
#include <vector>

class Capsule : public GameObject
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, float length, float resolution, float radius);
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();

private:
	void buildVertices(float length, float resolution, float radius);
	Vec3 buildCylinderVertex(float longitude, float latitude);
	Vec3 buildSphereTopVertex(float longitude, float latitude);
	Vec3 buildSphereBottomVertex(float longitude, float latitude);

	float m_length;
	Vec3 m_color = Vec3(1.0f, 1.0f, 1.0f);
	float m_radius;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	CoordinateSystemMatrices m_matrices;
};
