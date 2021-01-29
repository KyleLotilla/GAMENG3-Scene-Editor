#pragma once
#include <Windows.h>
#include <vector>
#include "imgui.h"
#include "UIScreen.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

class UIEngine
{
public:
	void init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void addUIScreen(UIScreen* screen);
	void update(float deltaTime);
	void drawUI(ViewportParams viewportParams);

private:
	std::vector<UIScreen*> m_screens;
};