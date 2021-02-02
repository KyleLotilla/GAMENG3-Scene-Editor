#pragma once
#include "engine/GameEngine.h"
#include "game/Cube.h"
#include "graphics/Vertex.h"
#include "game/Camera.h"
#include "ui/SceneOutlineScreen.h"
#include "ui/InspectorScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "ui/MainMenuBar.h"
#include "ui/CreditsScreen.h"
#include "game/Sphere.h"
#include "game/Cylinder.h"
#include "game/Capsule.h"
#include "game/OBJModel.h"
#include "EditorStateManager.h"
#include "ui/ModeScreen.h"
#include "ui/UndoRedoScreen.h"

class SceneEditor : public GameEngine
{
public:
	SceneEditor();
	~SceneEditor();
	void update(double delta_time);
	void render(double interpolation);

protected:
	bool init();
	void release();

private:
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	//OBJModel* m_sphere;
	Cube* m_cubes[20];
	Cube* m_plane;
	EditorStateManager m_stateManager;
	EditorCommandHistory m_commandHistory;
	Camera m_camera;
};