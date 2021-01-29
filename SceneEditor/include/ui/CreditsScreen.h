#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "graphics/Texture.h"

class CreditsScreen : public UIScreen
{
public:
	CreditsScreen();
	~CreditsScreen();
	void init(ID3D11Device* device);
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);

private:
	Texture m_logo;
	std::string m_logoPath = "assets/textures/logo.jpg";
};