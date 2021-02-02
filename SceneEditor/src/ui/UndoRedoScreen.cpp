#include "ui/UndoRedoScreen.h"

UndoRedoScreen::UndoRedoScreen()
{
}

UndoRedoScreen::~UndoRedoScreen()
{
}

void UndoRedoScreen::setEditorCommandHistory(EditorCommandHistory* commandHistory)
{
	this->m_commandHistory = commandHistory;
}

void UndoRedoScreen::update(float deltaTime)
{
}

void UndoRedoScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		ImGui::Begin("Editor Actions", &(m_active), ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(205, 75));
		ImGui::SetWindowPos(ImVec2(0.0f, 100.0f), ImGuiCond_Once);


		if (this->m_currentState == EditorState::EDIT_MODE)
		{
			if (this->m_commandHistory->hasRemainingUndo())
			{
				if (ImGui::Button("Undo"))
				{
					this->m_commandHistory->undoCommand();
				}
			}

			if (this->m_commandHistory->hasRemainingRedo())
			{
				ImGui::SameLine();
				if (ImGui::Button("Redo"))
				{
					this->m_commandHistory->redoCommand();
				}
			}
		}
		
		ImGui::End();
	}
}

void UndoRedoScreen::stateUpdated(EditorState oldState, EditorState newState)
{
	this->m_currentState = newState;
}
