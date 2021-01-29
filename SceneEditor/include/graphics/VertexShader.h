#pragma once
#include <d3d11.h>

class VertexShader
{
public:
	VertexShader();
	~VertexShader();
	bool init(const void* shader_byte_code, size_t byte_code_size, ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC layout[], UINT size_layout);
	ID3D11VertexShader* getShader();
	ID3D11InputLayout* getInputLayout();
	void release();

protected:
	ID3D11VertexShader * m_vs;
	ID3D11InputLayout* m_layout;
};