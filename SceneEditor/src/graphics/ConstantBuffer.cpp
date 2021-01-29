#include "graphics/ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::load(void * buffer, UINT size_buffer, ID3D11Device * device)
{
	if (m_buffer)
		m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

void ConstantBuffer::update(DeviceContext * context, void * buffer)
{
	context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::release()
{
	if (m_buffer)
		m_buffer->Release();
	return true;
}

ID3D11Buffer * ConstantBuffer::getBuffer()
{
	return this->m_buffer;
}

ConstantBuffer::~ConstantBuffer()
{
}
