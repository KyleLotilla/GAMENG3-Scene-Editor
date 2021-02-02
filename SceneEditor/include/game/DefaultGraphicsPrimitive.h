#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "graphics/DefaultShaderInput.h"
#include "graphics/Vertex.h"
#include "graphics/Texture.h"
#include "graphics/TextureComponent.h"

class DefaultGraphicsPrimitive : public GameObject
{
public:
	DefaultGraphicsPrimitive();
	~DefaultGraphicsPrimitive();
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	virtual void release();

protected:
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	DefaultShaderInput m_shaderInput;
};