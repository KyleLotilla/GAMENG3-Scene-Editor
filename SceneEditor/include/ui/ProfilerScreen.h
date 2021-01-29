#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

class ProfilerScreen : public UIScreen
{
public:
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);
};