#pragma once
#include "DefaultGraphicsPrimitive.h"

class OBJModel : public DefaultGraphicsPrimitive
{
public:
	OBJModel();
	~OBJModel();
	void init(std::string path, VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device);
	virtual void update(float deltaTime);
};