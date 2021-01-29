#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"

class Plane3D : public GameObject
{
public:
	Plane3D();
	~Plane3D();
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device);
	void update(float deltaTime);
	void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();

private:
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	VertexBuffer m_vertexBuffer;
	ConstantBuffer m_constantBuffer;
	IndexBuffer m_indexBuffer;
	CoordinateSystemMatrices m_matrices;
};