#include "graphics/Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::init(const wchar_t* full_path, ID3D11Device * device)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

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

void Texture::release()
{
	this->m_shader_res_view->Release();
	this->m_texture->Release();
}
