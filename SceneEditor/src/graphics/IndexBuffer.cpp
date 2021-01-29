#include "graphics/IndexBuffer.h"

IndexBuffer::IndexBuffer() : m_buffer(0)
{
}

bool IndexBuffer::load(void* list_indices, UINT size_list, ID3D11Device* device)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (device->CreateBuffer(&buff_desc, &init_data, &m_buffer))
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}

ID3D11Buffer * IndexBuffer::getBuffer()
{
	return this->m_buffer;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}


IndexBuffer::~IndexBuffer()
{
}