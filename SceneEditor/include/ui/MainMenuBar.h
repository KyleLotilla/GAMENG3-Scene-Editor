#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

class MainMenuBar : public UIScreen
{
public:
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);
	void setCreditsScreen(UIScreen* creditsScreen);

private:
	UIScreen* m_creditsScreen;
	bool m_demoColorPicker;
	ImVec4 m_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};