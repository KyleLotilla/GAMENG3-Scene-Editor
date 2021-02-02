#include "ui/ModeScreen.h"

ModeScreen::ModeScreen()
{
}

ModeScreen::~ModeScreen()
{
}

void ModeScreen::setEditorStateManager(EditorStateManager* stateManager)
{
	this->m_stateManager = stateManager;
}

void ModeScreen::update(float deltaTime)
{
}

void ModeScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		ImGui::Begin("Mode Select", &(m_active), ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(205, 75));
		ImGui::SetWindowPos(ImVec2(0.0f, 20.0f), ImGuiCond_Once);

		if (this->m_stateManager->getCurrentState() == EditorState::EDIT_MODE)
		{
			if (ImGui::Button("PLAY"))
			{
				this->m_stateManager->setEditorState(EditorState::PLAY_MODE);
			}
		}
		else if (this->m_stateManager->getCurrentState() == EditorState::PLAY_MODE)
		{
			if (ImGui::Button("PAUSE"))
			{
				this->m_stateManager->setEditorState(EditorState::PAUSED);
			}
			ImGui::SameLine();
			if (ImGui::Button("STOP"))
			{
				this->m_stateManager->setEditorState(EditorState::EDIT_MODE);
			}
		}
		else if (this->m_stateManager->getCurrentState() == EditorState::PAUSED)
		{
			if (ImGui::Button("PLAY"))
			{
				this->m_stateManager->setEditorState(EditorState::PLAY_MODE);
			}
			ImGui::SameLine();
			if (ImGui::Button("STOP"))
			{
				this->m_stateManager->setEditorState(EditorState::EDIT_MODE);
			}
			ImGui::SameLine();
			if (ImGui::Button("STEP"))
			{
				this->m_stateManager->setEditorState(EditorState::FRAME_STEP);
			}
		}

		ImGui::End();
	}
}
