#include "ui/SceneOutlineScreen.h"

SceneOutlineScreen::SceneOutlineScreen()
{
}

SceneOutlineScreen::~SceneOutlineScreen()
{
}

void SceneOutlineScreen::setGameObjectManager(GameObjectManager * gameObjectManager)
{
	this->m_gameObjectManager = gameObjectManager;
}

GameObject * SceneOutlineScreen::getSelected()
{
	return this->m_selected;
}

void SceneOutlineScreen::update(float deltaTime)
{
}

void SceneOutlineScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		float windowWidth = viewportParams.m_right - viewportParams.m_left;
		float windowHeight = viewportParams.m_bottom - viewportParams.m_top;
		ImGui::Begin("Scene Outline", &(this->m_active), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(windowWidth - 505.0f, 20.0f));
		ImGui::SetWindowSize(ImVec2(250.0f, windowHeight));
		int i = 0;

		for (GameObject* gameObject : *(this->m_gameObjectManager))
		{
			bool selectedFlag = false;

			if (this->m_selectedIndex == i)
			{
				selectedFlag = true;
			}

			std::string indexString = std::to_string(i);

			if (ImGui::Selectable(indexString.c_str(), selectedFlag))
			{
				this->m_selectedIndex = i;
				this->m_selected = this->m_gameObjectManager->getGameObject(i);
			}

			i++;
		}

		ImGui::End();
	}
}
