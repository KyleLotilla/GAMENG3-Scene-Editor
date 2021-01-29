#include "graphics/PixelShader.h"

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::init(const void * shader_byte_code, size_t byte_code_size, ID3D11Device* device)
{
	if (!SUCCEEDED(device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		return false;

	return true;
}

ID3D11PixelShader * PixelShader::getShader()
{
	return this->m_ps;
}

void PixelShader::release()
{
	m_ps->Release();
	delete this;
}
