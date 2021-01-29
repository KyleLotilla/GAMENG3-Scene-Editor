#include "ui/MainMenuBar.h"

void MainMenuBar::update(float deltaTime)
{
	
}

void MainMenuBar::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Crtl+O"))
				{

				}
				if (ImGui::MenuItem("Save", "Crtl+S"))
				{

				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				if (ImGui::MenuItem("Credits"))
				{
					this->m_creditsScreen->setActive(true);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Demo"))
			{
				if (ImGui::MenuItem("Color Picker"))
				{
					this->m_demoColorPicker = true;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (this->m_demoColorPicker)
		{
			ImGui::Begin("Color Picker", &(this->m_demoColorPicker));
			ImGui::ColorPicker4("Color Picker", (float*)&(this->m_color));
			ImGui::End();
		}
	}
}

void MainMenuBar::setCreditsScreen(UIScreen * creditsScreen)
{
	this->m_creditsScreen = creditsScreen;
	this->m_creditsScreen->setActive(false);
}
