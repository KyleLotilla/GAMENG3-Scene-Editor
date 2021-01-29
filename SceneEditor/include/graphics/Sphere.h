#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"
#include <vector>

class Sphere : public GameObject
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, int sectorCount, int stackCount, float radius);
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();

private:
	void buildVertices(int sectorCount, int stackCount, float radius);
	void buildIndices(int sectorCount, int stackCount);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	Vec3 m_color = Vec3(1.0f, 1.0f, 1.0f);
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	CoordinateSystemMatrices m_matrices;
};