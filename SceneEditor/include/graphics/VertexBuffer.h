#pragma once
#include <d3d11.h>

class VertexBuffer
{
public:
	VertexBuffer();
	bool load(void* list_vertices, UINT size_vertex, UINT size_list, ID3D11Device* device);
	UINT getSizeVertexList();
	UINT getSizeVertex();
	ID3D11Buffer* getBuffer();
	bool release();
	~VertexBuffer();

private:
	UINT m_size_vertex;
	UINT m_size_list;
	ID3D11Buffer* m_buffer;
};