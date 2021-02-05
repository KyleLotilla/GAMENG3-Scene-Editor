#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "game/GameObjectManager.h"
#include "SceneOutlineScreen.h"
#include "editor/EditorCommandHistory.h"
#include "editor/EditorStateListener.h"
#include "editor/TranslateCommand.h"
#include "editor/RotateCommand.h"
#include "editor/ScaleCommand.h"
#include "physics/PhysicsEngine.h"
#include "graphics/TextureComponent.h"
#include "ImGuiFileDialog.h"
#include <sstream>

class InspectorScreen : public UIScreen, public EditorStateListener
{
public:
	InspectorScreen();
	~InspectorScreen();
	void setSceneOutlineScreen(SceneOutlineScreen* sceneOutlineScreen);
	void setEditorCommandHistory(EditorCommandHistory* commandHistory);
	void setGameObjectManager(GameObjectManager* gameObjectManager);
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);
	void stateUpdated(EditorState oldState, EditorState newState);
	void setPhysicsEngine(PhysicsEngine* physicsEngine);
	void setDevice(ID3D11Device* device);

private:
	GameObjectManager* m_gameObjectManager;
	EditorCommandHistory* m_commandHistory;
	SceneOutlineScreen* m_sceneOutlineScreen;
	float m_position[3];
	float m_rotation[3];
	float m_scale[3];
	ImGuiInputTextFlags m_textFlags = ImGuiInputTextFlags_EnterReturnsTrue;
	PhysicsEngine* m_physicsEngine;
	ID3D11Device* m_device;
	ImGuiFileDialog m_fileDialog;
};