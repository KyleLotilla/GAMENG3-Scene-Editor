#pragma once
#include "GameEngine.h"
#include "graphics/Cube.h"
#include "graphics/Vertex.h"
#include "math/Constant.h"
#include "game/Camera.h"
#include "ui/SceneOutlineScreen.h"
#include "ui/InspectorScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "ui/MainMenuBar.h"
#include "ui/CreditsScreen.h"
#include "graphics/Sphere.h"
#include "graphics/Cylinder.h"
#include "graphics/Capsule.h"
#include "graphics/OBJModel.h"

class RendererGameEngine : public GameEngine
{
public:
	RendererGameEngine();
	~RendererGameEngine();
	void update(double delta_time);
	void render(double interpolation);

protected:
	bool init();
	void release();

private:
	VertexShader* m_vertexColorShader;
	PixelShader* m_pixelColorShader;
	VertexShader* m_vertexTextureShader;
	PixelShader* m_pixelTextureShader;
	OBJModel* m_sphere;
	//Cube* m_cubes[20];
	//Cube* m_plane;
	Camera m_camera;
};