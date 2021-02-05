#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "game/GameObjectManager.h"
#include "ImGuiFileDialog.h"

class MainMenuBar : public UIScreen
{
public:
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);
	void setCreditsScreen(UIScreen* creditsScreen);
	void setVertexShader(VertexShader* vertexShader);
	void setPixelShader(PixelShader* pixelShader);
	void setGameObjectManager(GameObjectManager* gameObjectManager);
	void setDevice(ID3D11Device* device);

private:
	UIScreen* m_creditsScreen;
	bool m_demoColorPicker;
	ImVec4 m_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	PixelShader* m_pixelShader;
	VertexShader* m_vertexShader;
	GameObjectManager* m_gameObjectManager;
	ID3D11Device* m_device;
	ImGuiFileDialog m_fileDialog;
};