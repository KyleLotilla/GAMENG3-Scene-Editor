#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "editor/EditorStateManager.h"

class ModeScreen : public UIScreen
{
public:
	ModeScreen();
	~ModeScreen();
	void setEditorStateManager(EditorStateManager* stateManager);
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);

private:
	EditorStateManager* m_stateManager;
	float m_position[3];
	float m_rotation[3];
	float m_scale[3];
};