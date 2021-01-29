#include "engine/GameEngine.h"
#include <iostream>

GameEngine::GameEngine() :
	m_window(&(m_graphicsEngine))
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
	if (this->initEngine())
	{
		this->m_isRun = true;
		this->gameLoop();
	}
}

void GameEngine::stop()
{
	this->m_isRun = false;
}

void GameEngine::pollInput()
{
	this->m_inputEngine.pollInput();
}

bool GameEngine::initEngine()
{
	this->m_graphicsEngine.init();
	this->m_window.init();
	this->m_uiEngine.init(this->m_window.getHandle(), this->m_graphicsEngine.getD3DDevice(), this->m_graphicsEngine.getImmediateDeviceContext()->getInternalContext());
	this->m_physicsEngine.setGameObjectManager(&(this->m_gameObjectManager));
	this->init();
	return true;
}

void GameEngine::releaseEngine()
{
	this->release();
	m_graphicsEngine.release();
}

void GameEngine::gameLoop()
{
	while (this->m_isRun && this->m_window.isRunning())
	{
		this->m_window.broadcast();
		if (this->m_window.isRunning())
		{
			this->m_engineTime.logFrameStart();
			this->pollInput();
			this->update(this->m_engineTime.getDeltaTime());
			this->render(this->m_engineTime.getDeltaTime());
			this->m_engineTime.logFrameEnd();

			this->frameCount++;
			//std::cout << "Frame: " << this->frameCount << " Time Elasped: " << this->m_engineTime.getDeltaTime() << " seconds" << std::endl;
		}

		Sleep(0);
	}
	this->releaseEngine();
}

bool GameEngine::init()
{
	return false;
}

void GameEngine::release()
{
}


