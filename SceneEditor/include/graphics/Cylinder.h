#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"
#include <vector>

class Cylinder : public GameObject
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, int sectorCount, float height, float radius);
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();

private:
	void buildUnitCircleVertices(int sectorCount);
	void buildVertices(int sectorCount, float height, float radius);
	void buildIndices(int sectorCount);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Vec3> m_unitCircleVertices;
	int m_baseCenterIndex;
	int m_topCenterIndex;
	Vec3 m_color = Vec3(1.0f, 1.0f, 1.0f);
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	CoordinateSystemMatrices m_matrices;
};