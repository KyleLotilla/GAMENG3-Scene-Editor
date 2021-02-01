#pragma once
#include "graphics/DefaultGraphicsPrimitive.h"

class Cylinder : public DefaultGraphicsPrimitive
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, int sectorCount, float height, float radius);
	virtual void update(float deltaTime);

private:
	void buildUnitCircleVertices(int sectorCount);
	void buildVertices(int sectorCount, float height, float radius);
	void buildIndices(int sectorCount);

	std::vector<VertexTexture> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Vec3> m_unitCircleVertices;
	int m_baseCenterIndex;
	int m_topCenterIndex;
};