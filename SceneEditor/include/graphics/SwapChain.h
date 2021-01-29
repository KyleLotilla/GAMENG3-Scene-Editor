#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain(ID3D11Device* device, IDXGIFactory* idxgiFactory);
	~SwapChain();
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();
	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();

private:
	IDXGISwapChain * m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	ID3D11Device* m_device; 
	IDXGIFactory* m_idxgiFactory;
};