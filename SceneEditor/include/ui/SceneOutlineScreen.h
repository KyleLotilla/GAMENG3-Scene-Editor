#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "game/GameObjectManager.h"
#include <string>

class SceneOutlineScreen : public UIScreen
{
public:
	SceneOutlineScreen();
	~SceneOutlineScreen();
	void setGameObjectManager(GameObjectManager* gameObjectManager);
	GameObject* getSelected();
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);

private:
	GameObjectManager* m_gameObjectManager;
	GameObject* m_selected;
	int m_selectedIndex = -1;

};