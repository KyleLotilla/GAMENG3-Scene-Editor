#include "ui/UIEngine.h"

void UIEngine::init(HWND hwnd, ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void UIEngine::addUIScreen(UIScreen * screen)
{
	this->m_screens.push_back(screen);
}

void UIEngine::update(float deltaTime)
{
	for (UIScreen* screen : this->m_screens)
	{
		screen->update(deltaTime);
	}
}

void UIEngine::drawUI(ViewportParams viewportParams)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (UIScreen* screen : this->m_screens)
	{
		screen->drawUI(viewportParams);
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
