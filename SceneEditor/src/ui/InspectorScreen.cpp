#include "ui/InspectorScreen.h"
#include <iostream>

InspectorScreen::InspectorScreen()
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::setSceneOutlineScreen(SceneOutlineScreen * sceneOutlineScreen)
{
	this->m_sceneOutlineScreen = sceneOutlineScreen;
}

void InspectorScreen::setEditorCommandHistory(EditorCommandHistory* commandHistory)
{
	this->m_commandHistory = commandHistory;
}

void InspectorScreen::setGameObjectManager(GameObjectManager* gameObjectManager)
{
	this->m_gameObjectManager = gameObjectManager;
}

void InspectorScreen::update(float deltaTime)
{
}

void InspectorScreen::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		float windowWidth = viewportParams.m_right - viewportParams.m_left;
		float windowHeight = viewportParams.m_bottom - viewportParams.m_top;
		ImGui::Begin("Inspector", &(this->m_active), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(windowWidth - 255.0f, 20.0f));
		ImGui::SetWindowSize(ImVec2(250.0f, windowHeight));


		GameObject* selectedGameObject = this->m_sceneOutlineScreen->getSelected();

		if (selectedGameObject != nullptr)
		{
			Vec3 position = selectedGameObject->getLocalPosition();
			Vec3 rotation = selectedGameObject->getLocalRotationVector();
			Vec3 scale = selectedGameObject->getLocalScale();

			this->m_position[0] = position.m_x;
			this->m_position[1] = position.m_y;
			this->m_position[2] = position.m_z;

			this->m_rotation[0] = rotation.m_x;
			this->m_rotation[1] = rotation.m_y;
			this->m_rotation[2] = rotation.m_z;

			this->m_scale[0] = scale.m_x;
			this->m_scale[1] = scale.m_y;
			this->m_scale[2] = scale.m_z;

			if (ImGui::InputFloat3("Position", this->m_position, "%.3f" ,this->m_textFlags))
			{
				Vec3 newPosition = Vec3(this->m_position[0], this->m_position[1], this->m_position[2]);
				TranslateCommand* command = new TranslateCommand(selectedGameObject->getID(), position, newPosition, this->m_gameObjectManager);
				selectedGameObject->setPosition(newPosition);
				this->m_commandHistory->recordExecutedCommand(command);
			}

			if (ImGui::InputFloat3("Rotation", this->m_rotation, "%.3f", this->m_textFlags))
			{
				reactphysics3d::Quaternion oldRotation = selectedGameObject->getLocalRotationQuaternion();
				rotation.m_x = this->m_rotation[0];
				rotation.m_y = this->m_rotation[1];
				rotation.m_z = this->m_rotation[2];
				selectedGameObject->setRotation(rotation);
				reactphysics3d::Quaternion newRotation = selectedGameObject->getLocalRotationQuaternion();
				RotateCommand* command = new RotateCommand(selectedGameObject->getID(), oldRotation, newRotation, this->m_gameObjectManager);
				this->m_commandHistory->recordExecutedCommand(command);
			}

			if (ImGui::InputFloat3("Scale", this->m_scale, "%.3f", this->m_textFlags))
			{
				Vec3 newScale = Vec3(this->m_scale[0], this->m_scale[1], this->m_scale[2]);
				ScaleCommand* command = new ScaleCommand(selectedGameObject->getID(), scale, newScale, this->m_gameObjectManager);
				selectedGameObject->setScale(newScale);
				this->m_commandHistory->recordExecutedCommand(command);
			}

		}

		ImGui::End();
	}
}

void InspectorScreen::stateUpdated(EditorState oldState, EditorState newState)
{
	if (newState == EditorState::EDIT_MODE)
	{
		this->m_textFlags = ImGuiInputTextFlags_EnterReturnsTrue;
	}
	else
	{
		this->m_textFlags = ImGuiInputTextFlags_ReadOnly;
	}
}
