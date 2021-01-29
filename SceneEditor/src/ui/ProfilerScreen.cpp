#include "ui/ProfilerScreen.h"

void ProfilerScreen::update(float deltaTime)
{

}

void ProfilerScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		ImGui::Begin("Profiler", &(this->m_active));
		ImGui::End();
	}
}
