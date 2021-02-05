#include "editor/SceneEditor.h"

SceneEditor::SceneEditor()
{
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::update(double delta_time)
{
	this->m_camera.update(delta_time);

	if (this->m_stateManager.getCurrentState() == EditorState::PLAY_MODE || this->m_stateManager.getCurrentState() == EditorState::FRAME_STEP)
	{
		this->m_physicsEngine.update(delta_time);
		this->m_gameObjectManager.update(delta_time);

		if (this->m_stateManager.getCurrentState() == EditorState::FRAME_STEP)
		{
			this->m_stateManager.setEditorState(EditorState::PAUSED);
		}
	}
}

void SceneEditor::render(double interpolation)
{
	this->m_window.clearRenderTargetColor(0, 0, 0, 1);
	RECT rc = this->m_window.getClientWindowRect();
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	this->m_graphicsEngine.getImmediateDeviceContext()->setViewportSize(width, height);

	Mat4 projectionMatrix;
	projectionMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	Mat4 identityMatrix;
	identityMatrix.setIdentity();

	ViewportParams viewportParams;
	viewportParams.m_left = rc.left;
	viewportParams.m_right = rc.right;
	viewportParams.m_bottom = rc.bottom;
	viewportParams.m_top = rc.top;
	viewportParams.m_projection = projectionMatrix;
	viewportParams.m_view = this->m_camera.getViewMatrix();

	
	this->m_gameObjectManager.draw(this->m_graphicsEngine.getImmediateDeviceContext(), viewportParams);

	this->m_uiEngine.drawUI(viewportParams);

	this->m_window.present(true);

}

bool SceneEditor::init()
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	D3D11_INPUT_ELEMENT_DESC textureLayout[] =
	{
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(textureLayout);

	this->m_graphicsEngine.compileVertexShader(L"shaders/DefaultVertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	this->m_vertexShader = this->m_graphicsEngine.createVertexShader(shader_byte_code, size_shader, textureLayout, size_layout);
	this->m_graphicsEngine.releaseCompiledShader();

	this->m_graphicsEngine.compilePixelShader(L"shaders/DefaultPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	this->m_pixelShader = this->m_graphicsEngine.createPixelShader(shader_byte_code, size_shader);
	this->m_graphicsEngine.releaseCompiledShader();

	/*for (int i = 0; i < 20; i++)
	{
		this->m_cubes[i] = new Cube();
		this->m_cubes[i]->init(this->m_vertexShader, this->m_pixelShader, this->m_graphicsEngine.getD3DDevice());
		this->m_cubes[i]->setPosition(Vec3(0.0f, 5.0f, 0.0f));
		PhysicsComponent* cubeComponent = new PhysicsComponent();
		cubeComponent->init(this->m_physicsEngine.getPhysicsCommon(), this->m_physicsEngine.getPhysicsWorld(), this->m_cubes[i]);
		this->m_cubes[i]->addComponent(cubeComponent);
		this->m_gameObjectManager.addGameObject(this->m_cubes[i]);
	}

	this->m_plane = new Cube();
	m_plane->init(this->m_vertexShader, this->m_pixelShader, this->m_graphicsEngine.getD3DDevice());
	m_plane->setScale(Vec3(10.0f, 0.2f, 10.0f));
	PhysicsComponent* planeComponent = new PhysicsComponent();
	planeComponent->init(this->m_physicsEngine.getPhysicsCommon(), this->m_physicsEngine.getPhysicsWorld(), m_plane);
	planeComponent->setBodyType(reactphysics3d::BodyType::KINEMATIC);
	this->m_plane->addComponent(planeComponent);
	this->m_gameObjectManager.addGameObject(this->m_plane);*/

	/*
	this->m_sphere = new OBJModel();
	this->m_sphere->init("assets/meshes/teapot.obj", this->m_vertexShader, this->m_pixelShader, this->m_graphicsEngine.getD3DDevice());
	Texture* texture = new Texture();
	texture->init("assets/textures/earth.bmp", this->m_graphicsEngine.getD3DDevice());
	TextureComponent* textureComponent = new TextureComponent();
	textureComponent->setTexture(texture);
	this->m_sphere->addComponent(textureComponent);
	this->m_gameObjectManager.addGameObject(this->m_sphere);
	*/

	this->m_inputEngine.addListener(&(this->m_camera));

	SceneOutlineScreen* sceneOutline = new SceneOutlineScreen();
	sceneOutline->setGameObjectManager(&(this->m_gameObjectManager));
	this->m_uiEngine.addUIScreen(sceneOutline);
	
	InspectorScreen* inspector = new InspectorScreen();
	inspector->setSceneOutlineScreen(sceneOutline);
	inspector->setEditorCommandHistory(&(this->m_commandHistory));
	inspector->setGameObjectManager(&(this->m_gameObjectManager));
	inspector->setPhysicsEngine(&(this->m_physicsEngine));
	inspector->setDevice(this->m_graphicsEngine.getD3DDevice());
	this->m_uiEngine.addUIScreen(inspector);

	MainMenuBar* mainMenu = new MainMenuBar();
	CreditsScreen* creditsScreen = new CreditsScreen();
	creditsScreen->init(this->m_graphicsEngine.getD3DDevice());
	mainMenu->setCreditsScreen(creditsScreen);
	mainMenu->setVertexShader(this->m_vertexShader);
	mainMenu->setPixelShader(this->m_pixelShader);
	mainMenu->setGameObjectManager(&(this->m_gameObjectManager));
	mainMenu->setDevice(this->m_graphicsEngine.getD3DDevice());
	mainMenu->setPhysicsEngine(&(this->m_physicsEngine));

	ModeScreen* modeScreen = new ModeScreen();
	modeScreen->setEditorStateManager(&(this->m_stateManager));

	UndoRedoScreen* undoRedoScreen = new UndoRedoScreen();
	undoRedoScreen->setEditorCommandHistory(&(this->m_commandHistory));

	this->m_uiEngine.addUIScreen(mainMenu);
	this->m_uiEngine.addUIScreen(creditsScreen);
	this->m_uiEngine.addUIScreen(modeScreen);
	this->m_uiEngine.addUIScreen(undoRedoScreen);

	this->m_stateManager.addListener(&(this->m_gameObjectManager));
	this->m_stateManager.addListener(&(this->m_physicsEngine));
	this->m_stateManager.addListener(inspector);
	this->m_stateManager.addListener(undoRedoScreen);
	this->m_stateManager.setEditorState(EditorState::EDIT_MODE);


	return true;
}

void SceneEditor::release()
{
	this->m_vertexShader->release();
	this->m_pixelShader->release();
}
