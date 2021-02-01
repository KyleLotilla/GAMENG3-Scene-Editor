#include "graphics/Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::init(std::string path, ID3D11Device * device)
{
	DirectX::ScratchImage image_data;
	std::wstring wPath = std::wstring(path.begin(), path.end());
	HRESULT res = DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(device, image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
		this->m_path = path;
	}
	else
	{
		throw std::exception("Texture not created successfully");
	}
}

ID3D11ShaderResourceView * Texture::getShaderResourceView()
{
	return this->m_shader_res_view;
}

std::string Texture::getPath()
{
	return this->m_path;
}

void Texture::release()
{
	this->m_shader_res_view->Release();
	this->m_texture->Release();
}
