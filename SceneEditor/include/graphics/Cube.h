#pragma once
#include "game/GameObject.h"
#include "graphics/ConstantBuffer.h"
#include "math/Constant.h"
#include "graphics/Vertex.h"
#include "graphics/Texture.h"

class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	void init(VertexShader* vertexShader, PixelShader* pixelShader, ID3D11Device* device);
	void setTexture(Texture* texture);
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
	Texture* m_texture;

	/*
	float m_animSpeed;
	bool m_increasing;
	*/
};
