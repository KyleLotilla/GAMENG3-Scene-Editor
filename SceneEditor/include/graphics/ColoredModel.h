#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"
#include "graphics/Texture.h"

class ColoredModel : public GameObject
{
public:
	ColoredModel();
	~ColoredModel();
	void init(std::string path, Vec3 color, VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device);
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();

private:
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	CoordinateSystemMatrices m_matrices;
};