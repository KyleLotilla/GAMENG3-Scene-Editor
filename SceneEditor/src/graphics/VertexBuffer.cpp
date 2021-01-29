#include "graphics/VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

bool VertexBuffer::load(void * list_vertices, UINT size_vertex, UINT size_list, ID3D11Device* device)
{
	if (m_buffer)
		m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

UINT VertexBuffer::getSizeVertex()
{
	return this->m_size_vertex;
}

ID3D11Buffer * VertexBuffer::getBuffer()
{
	return this->m_buffer;
}

bool VertexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
