#include "graphics/DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext * device_context, Texture* defaultTexture) :
	m_device_context(device_context), m_defualtTexture(defaultTexture)
{
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain * swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };
	ID3D11RenderTargetView* rtv = swap_chain->getRenderTargetView();
	ID3D11DepthStencilView* dsv = swap_chain->getDepthStencilView();
	this->m_device_context->ClearRenderTargetView(rtv, clear_color);
	this->m_device_context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	this->m_device_context->OMSetRenderTargets(1, &(rtv), dsv);
	return true;
}

bool DeviceContext::release()
{
	m_device_context->Release();
	//delete this;
	return true;
}

void DeviceContext::setVertexBuffer(VertexBuffer * vertex_buffer)
{
	UINT stride = vertex_buffer->getSizeVertex();
	UINT offset = 0;
	ID3D11Buffer* buffer = vertex_buffer->getBuffer();

	m_device_context->IASetVertexBuffers(0, 1, &(buffer), &stride, &offset);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(VertexShader * vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->getShader(), nullptr, 0);
	m_device_context->IASetInputLayout(vertex_shader->getInputLayout());
}

void DeviceContext::setPixelShader(PixelShader * pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->getShader(), nullptr, 0);
}

void DeviceContext::UpdateSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	this->m_device_context->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void DeviceContext::setVertexConstantBuffer(ID3D11Buffer * buffer)
{
	m_device_context->VSSetConstantBuffers(0, 1, &(buffer));
}

void DeviceContext::setPixelConstantBuffer(ID3D11Buffer * buffer)
{
	m_device_context->PSSetConstantBuffers(0, 1, &(buffer));
}

void DeviceContext::setIndexBuffer(IndexBuffer * index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->getBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setTexture(Texture * texture)
{
	ID3D11ShaderResourceView* shaderResourceView = texture->getShaderResourceView();
	m_device_context->PSSetShaderResources(0, 1, &(shaderResourceView));
}

void DeviceContext::setDefaultTexture()
{
	ID3D11ShaderResourceView* shaderResourceView = this->m_defualtTexture->getShaderResourceView();
	m_device_context->PSSetShaderResources(0, 1, &(shaderResourceView));
}

ID3D11DeviceContext * DeviceContext::getInternalContext()
{
	return this->m_device_context;
}
