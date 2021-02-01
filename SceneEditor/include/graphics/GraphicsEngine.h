#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "SwapChain.h"
#include "DeviceContext.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	bool init();
	bool release();
	ID3D11Device* getD3DDevice();
	IDXGIFactory* getIDXGIFactory();
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size, D3D11_INPUT_ELEMENT_DESC layout[], UINT size_layout);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

private:
	DeviceContext m_imm_device_context;
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	IDXGIDevice * m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3DBlob * m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
	std::string m_defaultTexturePath = "assets/textures/default.png";
};
