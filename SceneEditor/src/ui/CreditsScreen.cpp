#include "ui/CreditsScreen.h"

CreditsScreen::CreditsScreen()
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::init(ID3D11Device * device)
{
	this->m_logo.init(this->m_logoPath, device);
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
