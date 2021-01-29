#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool load(void* buffer, UINT size_buffer, ID3D11Device* device);
	void update(DeviceContext* context, void* buffer);
	bool release();
	ID3D11Buffer * getBuffer();
	~ConstantBuffer();
private:
	ID3D11Buffer * m_buffer;
};