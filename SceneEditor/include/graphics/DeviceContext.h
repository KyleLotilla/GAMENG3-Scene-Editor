#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "Texture.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, Texture* defaultTexture);
	~DeviceContext();
	bool clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	bool release();
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);
	void UpdateSubresource(ID3D11Resource  *pDstResource, UINT DstSubresource, const D3D11_BOX *pDstBox, const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
	void setVertexConstantBuffer(ID3D11Buffer* buffer);
	void setPixelConstantBuffer(ID3D11Buffer* buffer);
	void setIndexBuffer(IndexBuffer * index_buffer);
	void setTexture(Texture* texture);
	void setDefaultTexture();
	ID3D11DeviceContext* getInternalContext();

private:
	ID3D11DeviceContext * m_device_context;
	Texture* m_defualtTexture;
};