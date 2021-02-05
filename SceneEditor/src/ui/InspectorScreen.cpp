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
			std::vector<std::string> ids;
			ids.push_back("None");
			int parentID = -1;
			int parentIndex = 0;
			GameObject* parent = selectedGameObject->getParent();
			if (parent != nullptr)
			{
				parentID = parent->getID();
			}

			for (GameObject* gameObject : *(this->m_gameObjectManager))
			{
				if (gameObject->getID() != selectedGameObject->getID())
				{
					std::string idString = std::to_string(gameObject->getID());
					ids.push_back(idString);
					if (gameObject->getID() == parentID)
					{
						parentIndex = ids.size() - 1;
					}
				}
			}

			if (ImGui::BeginCombo("Parent", ids[parentIndex].c_str()))
			{
				for (int i = 0; i < ids.size(); i++)
				{
					bool selectedFlag = false;
					if (i == parentIndex)
					{
						selectedFlag = true;
					}

					if (ImGui::Selectable(ids[i].c_str(), selectedFlag))
					{
						parentIndex = i;
						if (parentIndex == 0)
						{
							selectedGameObject->setParent(nullptr);
						}
						else
						{
							std::stringstream stream;
							stream << ids[parentIndex];
							stream >> parentID;
							parent = this->m_gameObjectManager->getGameObject(parentID);
							selectedGameObject->setParent(parent);
						}
					}
					
				}
				ImGui::EndCombo();
			}

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

			TextureComponent* textureComponent = selectedGameObject->findComponent<TextureComponent>(ComponentType::TEXTURE);
			if (textureComponent == NULL) {
				if (ImGui::Button("Add Texture Component")) {
					m_fileDialog.OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg,.jpeg,.bmp", ".");
				}
				// display
				if (m_fileDialog.Display("ChooseFileDlgKey"))
				{
					if (m_fileDialog.IsOk())
					{
						std::string filePathName = m_fileDialog.GetFilePathName();
						Texture* texture = new Texture();
						texture->init(filePathName, m_device);
						textureComponent = new TextureComponent();
						textureComponent->setTexture(texture);
						selectedGameObject->addComponent(textureComponent);
					}

					m_fileDialog.Close();
				}
			}
			else {
				ImGui::Text("Texture Component");

				ImGui::Image((void*)(textureComponent->getTexture()->getShaderResourceView()), ImVec2(100.0f, 100.0f));

				if (ImGui::Button("Change Texture")) {
					m_fileDialog.OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg,.jpeg,.bmp", ".");
				}
				if (m_fileDialog.Display("ChooseFileDlgKey"))
				{
					if (m_fileDialog.IsOk())
					{
						std::string filePathName = m_fileDialog.GetFilePathName();
						Texture* texture = new Texture();
						texture->init(filePathName, m_device);
						textureComponent->setTexture(texture);
						selectedGameObject->addComponent(textureComponent);
					}

					m_fileDialog.Close();
				}

				float color[4];
				Vec4 colorComponent = textureComponent->getColor();

				color[0] = colorComponent.m_x;
				color[1] = colorComponent.m_y;
				color[2] = colorComponent.m_z;
				color[3] = colorComponent.m_w;

				if (ImGui::ColorPicker4("Color Picker", color)) {
					colorComponent.m_x = color[0];
					colorComponent.m_y = color[1];
					colorComponent.m_z = color[2];
					colorComponent.m_w = color[3];

					textureComponent->setColor(colorComponent);
				}
			}

			PhysicsComponent* physicsComponent = selectedGameObject->findComponent<PhysicsComponent>(ComponentType::PHYSICS);
			if (physicsComponent == NULL) {
				if (ImGui::Button("Add Physics Component")) {
					physicsComponent = new PhysicsComponent();
					physicsComponent->init(m_physicsEngine->getPhysicsCommon(), m_physicsEngine->getPhysicsWorld(), selectedGameObject);
					selectedGameObject->addComponent(physicsComponent);
				}
			}
			else {
				ImGui::Text("Physics Component");
				int bodyType;
				const char* typeNames[] = { "DYNAMIC", "STATIC", "KINEMATIC" };
				reactphysics3d::BodyType component;
				component = physicsComponent->getBodyType();
				if (component == reactphysics3d::BodyType::DYNAMIC) {
					bodyType = 0;
				}
				else if (component == reactphysics3d::BodyType::STATIC) {
					bodyType = 1;
				}
				else if (component == reactphysics3d::BodyType::KINEMATIC) {
					bodyType = 2;
				}

				if (ImGui::Combo("Body Type", &bodyType, typeNames, IM_ARRAYSIZE(typeNames))) {
					if (bodyType == 0) {
						physicsComponent->setBodyType(reactphysics3d::BodyType::DYNAMIC);
					}
					else if (bodyType == 1) {
						physicsComponent->setBodyType(reactphysics3d::BodyType::STATIC);
					}
					else if (bodyType == 2) {
						physicsComponent->setBodyType(reactphysics3d::BodyType::KINEMATIC);
					}
				}
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

void InspectorScreen::setPhysicsEngine(PhysicsEngine* physicsEngine)
{
	this->m_physicsEngine = physicsEngine;
}

void InspectorScreen::setDevice(ID3D11Device* device)
{
	this->m_device = device;
}
