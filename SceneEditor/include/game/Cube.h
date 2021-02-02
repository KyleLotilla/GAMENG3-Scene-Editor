#pragma once
#include "game/DefaultGraphicsPrimitive.h"

class Cube : public DefaultGraphicsPrimitive
{
public:
	Cube();
	~Cube();
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device);
	virtual void update(float deltaTime);
};