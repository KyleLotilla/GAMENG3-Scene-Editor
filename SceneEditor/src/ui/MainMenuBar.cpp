#include "ui/MainMenuBar.h"
#include "game/Cube.h"
#include "game/Sphere.h"
#include "game/Cylinder.h"
#include "game/Capsule.h"
#include "game/Plane3D.h"
#include "game/OBJModel.h"

void MainMenuBar::update(float deltaTime)
{
	
}

void MainMenuBar::drawUI(ViewportParams viewportParams)
{
	if (this->m_active)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Crtl+O"))
				{

				}
				if (ImGui::MenuItem("Save", "Crtl+S"))
				{

				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				if (ImGui::MenuItem("Credits"))
				{
					this->m_creditsScreen->setActive(true);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Demo"))
			{
				if (ImGui::MenuItem("Color Picker"))
				{
					this->m_demoColorPicker = true;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Game Objects")) 
			{
				if (ImGui::MenuItem("Cube")) {
					Cube* cube = new Cube();
					cube->init(m_vertexShader, m_pixelShader, m_device);
					m_gameObjectManager->addGameObject(cube);		
				}
				if (ImGui::MenuItem("Sphere")) {
					Sphere* sphere = new Sphere();
					sphere->init(m_vertexShader, m_pixelShader, m_device, 36, 18, 1);
					m_gameObjectManager->addGameObject(sphere);
				}
				if (ImGui::MenuItem("Capsule")) {
					Capsule* capsule = new Capsule();
					capsule->init(m_vertexShader, m_pixelShader, m_device, 5, 36, 1);
					m_gameObjectManager->addGameObject(capsule);
				}
				if (ImGui::MenuItem("Cylinder")) {
					Cylinder* cylinder = new Cylinder();
					cylinder->init(m_vertexShader, m_pixelShader, m_device, 36, 3.5, 1);
					m_gameObjectManager->addGameObject(cylinder);
				}
				if (ImGui::MenuItem("Plane")) {
					Plane3D* plane = new Plane3D();
					plane->init(m_vertexShader, m_pixelShader, m_device);
					m_gameObjectManager->addGameObject(plane);
				}
				if (ImGui::MenuItem("3D Object")) {
					m_fileDialog.OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", ".");	
				}
				if (ImGui::MenuItem("Spawn 100 Physics Cubes")) {
					Cube* cubes[100];

					for (int i = 0; i < 100; i++)
					{
						cubes[i] = new Cube();
						cubes[i]->init(m_vertexShader, m_pixelShader, m_device);
						cubes[i]->setPosition(Vec3(0.0f, 5.0f, 0.0f));
						PhysicsComponent* cubeComponent = new PhysicsComponent();
						cubeComponent->init(m_physicsEngine->getPhysicsCommon(), m_physicsEngine->getPhysicsWorld(), cubes[i]);
						cubes[i]->addComponent(cubeComponent);
						m_gameObjectManager->addGameObject(cubes[i]);
					}
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (this->m_demoColorPicker)
		{
			ImGui::Begin("Color Picker", &(this->m_demoColorPicker));
			ImGui::ColorPicker4("Color Picker", (float*)&(this->m_color));
			ImGui::End();
		}

		if (m_fileDialog.Display("ChooseFileDlgKey"))
		{
			if (m_fileDialog.IsOk())
			{
				std::string filePathName = m_fileDialog.GetFilePathName();
				OBJModel* objModel = new OBJModel();
				objModel->init(filePathName, m_vertexShader, m_pixelShader, m_device);
				m_gameObjectManager->addGameObject(objModel);
			}

			m_fileDialog.Close();
		}
	}
}

void MainMenuBar::setCreditsScreen(UIScreen * creditsScreen)
{
	this->m_creditsScreen = creditsScreen;
	this->m_creditsScreen->setActive(false);
}

void MainMenuBar::setVertexShader(VertexShader* vertexShader)
{
	this->m_vertexShader = vertexShader;
}

void MainMenuBar::setPixelShader(PixelShader* pixelShader)
{
	this->m_pixelShader = pixelShader;
}

void MainMenuBar::setGameObjectManager(GameObjectManager* gameObjectManager)
{
	this->m_gameObjectManager = gameObjectManager;
}

void MainMenuBar::setDevice(ID3D11Device* device)
{
	this->m_device = device;
}

void MainMenuBar::setPhysicsEngine(PhysicsEngine* physicsEngine)
{
	this->m_physicsEngine = physicsEngine;
}
