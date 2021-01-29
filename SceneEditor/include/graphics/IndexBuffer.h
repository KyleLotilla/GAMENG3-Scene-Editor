#pragma once
#include <d3d11.h>

class IndexBuffer
{
public:
	IndexBuffer();
	bool load(void* list_indices, UINT size_list, ID3D11Device* device);
	UINT getSizeIndexList();
	ID3D11Buffer * getBuffer();
	bool release();
	~IndexBuffer();
private:
	UINT m_size_list;
	ID3D11Buffer * m_buffer;
};