#include "graphics/VertexShader.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::init(const void * shader_byte_code, size_t byte_code_size, ID3D11Device * device, D3D11_INPUT_ELEMENT_DESC layout[], UINT size_layout)
{
	if (!SUCCEEDED(device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
	{
		return false;
	}
	else
	{
		/*
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
			{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
		};
		

		UINT size_layout = ARRAYSIZE(layout);
		*/

		if (FAILED(device->CreateInputLayout(layout, size_layout, shader_byte_code, byte_code_size, &m_layout)))
		{
			return false;
		}
		return true;
	}
}

ID3D11VertexShader * VertexShader::getShader()
{
	return m_vs;
}

ID3D11InputLayout * VertexShader::getInputLayout()
{
	return this->m_layout;
}

void VertexShader::release()
{
	m_vs->Release();
	m_layout->Release();
	delete this;
}
