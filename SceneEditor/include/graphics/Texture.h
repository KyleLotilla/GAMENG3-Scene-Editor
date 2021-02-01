#pragma once
#include <d3d11.h>
#include "DirectXTex.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	void init(std::string path, ID3D11Device* device);
	ID3D11ShaderResourceView* getShaderResourceView();
	std::string getPath();
	void release();

private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
	std::string m_path = "";
};