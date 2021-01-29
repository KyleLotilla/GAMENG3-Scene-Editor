#pragma once
#include "graphics/RenderWindow.h"
#include "time/EngineTime.h"
#include "input/InputEngine.h"
#include "ui/UIEngine.h"
#include "physics/PhysicsEngine.h"
#include "game/GameObjectManager.h"


class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void run();
	void stop();
	virtual void pollInput();
	virtual void update(double delta_time) = 0;
	virtual void render(double interpolation) = 0;

private:
	bool initEngine();
	void releaseEngine();
	void gameLoop();


protected:
	virtual bool init();
	virtual void release();

	RenderWindow m_window;
	GraphicsEngine m_graphicsEngine;
	InputEngine m_inputEngine;
	UIEngine m_uiEngine;
	EngineTime m_engineTime;
	GameObjectManager m_gameObjectManager;
	PhysicsEngine m_physicsEngine;
	bool m_isRun = false;
	int frameCount = 0;
};