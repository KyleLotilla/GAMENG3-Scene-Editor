#include "ui/CreditsScreen.h"

CreditsScreen::CreditsScreen()
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::init(ID3D11Device * device)
{
	std::wstring wLogoPath = std::wstring(this->m_logoPath.begin(), this->m_logoPath.end());
	this->m_logo.init(wLogoPath.c_str(), device);
}

void CreditsScreen::update(float deltaTime)
{
}

void CreditsScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		ImGui::Begin("Credits", &(m_active), ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Scene Editor v0.1");
		ImGui::Text("By Kyle Lotilla");
		ImGui::TextWrapped("Made using DirectX 11 and ImGui v1.79. Made for GAMENG3");
		ImGui::Image((void *)this->m_logo.getShaderResourceView(), ImVec2(200.0f, 200.0f));
		ImGui::End();
	}
}
