#include "graphics/GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() :
	m_imm_device_context(nullptr)
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	ID3D11DeviceContext* m_imm_context;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
	}
	if (FAILED(res))
	{
		return false;
	}

	m_imm_device_context = DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	this->m_d3d_device->Release();
	this->m_imm_device_context.release();
	this->m_dxgi_device->Release();
	this->m_dxgi_adapter->Release();
	this->m_dxgi_factory->Release();
	return true;
}

ID3D11Device * GraphicsEngine::getD3DDevice()
{
	return this->m_d3d_device;
}

IDXGIFactory * GraphicsEngine::getIDXGIFactory()
{
	return this->m_dxgi_factory;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain(this->m_d3d_device, this->m_dxgi_factory);
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return &(this->m_imm_device_context);
}

VertexShader * GraphicsEngine::createVertexShader(const void * shader_byte_code, size_t byte_code_size, D3D11_INPUT_ELEMENT_DESC layout[], UINT size_layout)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size, this->m_d3d_device, layout, size_layout))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader * GraphicsEngine::createPixelShader(const void * shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size, this->m_d3d_device))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t * file_name, const char * entry_point_name, void ** shader_byte_code, size_t * byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t * file_name, const char * entry_point_name, void ** shader_byte_code, size_t * byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}
