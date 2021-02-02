#pragma once
#include "game/DefaultGraphicsPrimitive.h"
#include <vector>

class Sphere : public DefaultGraphicsPrimitive
{
public:
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device, int sectorCount, int stackCount, float radius);

private:
	void buildVertices(int sectorCount, int stackCount, float radius);
	void buildIndices(int sectorCount, int stackCount);

	std::vector<VertexTexture> m_vertices;
	std::vector<unsigned int> m_indices;
};