#include "graphics/SwapChain.h"

SwapChain::SwapChain(ID3D11Device* device, IDXGIFactory* idxgiFactory) :
	m_device(device), m_idxgiFactory(idxgiFactory)
{
}

SwapChain::~SwapChain()
{
}

ID3D11RenderTargetView * SwapChain::getRenderTargetView()
{
	return m_rtv;
}

ID3D11DepthStencilView * SwapChain::getDepthStencilView()
{
	return this->m_dsv;
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = m_idxgiFactory->CreateSwapChain(m_device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		return false;
	}


	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = m_device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	hr = this->m_device->CreateTexture2D(&(texDesc), NULL, &(buffer));
	hr = this->m_device->CreateDepthStencilView(buffer, NULL, &(this->m_dsv));
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}
