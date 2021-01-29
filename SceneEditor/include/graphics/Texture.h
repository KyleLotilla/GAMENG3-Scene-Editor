#pragma once
#include <d3d11.h>
#include "DirectXTex.h"

class Texture
{
public:
	Texture();
	~Texture();
	void init(const wchar_t* full_path, ID3D11Device* device);
	ID3D11ShaderResourceView* getShaderResourceView();
	void release();

private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
};