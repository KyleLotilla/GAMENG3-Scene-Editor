#pragma once
#include <d3d11.h>

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
	bool init(const void* shader_byte_code, size_t byte_code_size, ID3D11Device* device);
	ID3D11PixelShader* getShader();
	void release();

private:
	ID3D11PixelShader* m_ps;
};