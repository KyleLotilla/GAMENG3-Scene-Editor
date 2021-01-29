#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "game/GameObjectManager.h"
#include "SceneOutlineScreen.h"

class InspectorScreen : public UIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();
	void setSceneOutlineScreen(SceneOutlineScreen* sceneOutlineScreen);
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);

private:
	GameObjectManager* m_gameObjectManager;
	SceneOutlineScreen* m_sceneOutlineScreen;
	float m_position[3];
	float m_rotation[3];
	float m_scale[3];
};