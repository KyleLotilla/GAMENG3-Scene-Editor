#include "game/GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < this->m_numID; i++)
	{
		this->m_idPool.push_back(i);
	}
}

GameObjectManager::~GameObjectManager()
{
	m_gameObjects.~vector();
	//m_idIndexMapping.~unordered_map();
	m_idPool.~vector();
}

void GameObjectManager::addGameObject(GameObject * gameObject)
{
	if (this->m_idPool.size() > 0)
	{
		int id = this->m_idPool.front();
		this->m_idPool.erase(this->m_idPool.begin());
		gameObject->setID(id);
		this->m_gameObjects.push_back(gameObject);
		this->m_idIndexMapping[id] = this->m_gameObjects.size() - 1;
	}
}

void GameObjectManager::removeGameObject(int id)
{
	if (this->m_idIndexMapping.find(id) != this->m_idIndexMapping.end())
	{
		int index = this->m_idIndexMapping[id];
		GameObject* removedObject = this->m_gameObjects[index];
		GameObject* lastObject = this->m_gameObjects.back();
		this->m_gameObjects[index] = lastObject;
		this->m_idIndexMapping[lastObject->getID()] = index;
		this->m_idIndexMapping.erase(id);
		this->m_gameObjects.erase(this->m_gameObjects.end());
		this->m_idPool.push_back(id);
	}
}

void GameObjectManager::update(float deltaTime)
{
	for (GameObject* gameObject : this->m_gameObjects)
	{
		gameObject->update(deltaTime);
	}
}

void GameObjectManager::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
{
	for (GameObject* gameObject : this->m_gameObjects)
	{
		gameObject->draw(deviceContext, viewportParams);
	}
}

void GameObjectManager::release()
{
	for (GameObject* gameObject : this->m_gameObjects)
	{
		gameObject->release();
	}
}

std::vector<GameObject*>::iterator GameObjectManager::begin()
{
	return this->m_gameObjects.begin();
}

std::vector<GameObject*>::iterator GameObjectManager::end()
{
	return this->m_gameObjects.end();
}

GameObject * GameObjectManager::getGameObject(int id)
{
	if (this->m_idIndexMapping.find(id) != this->m_idIndexMapping.end())
	{
		return this->m_gameObjects[this->m_idIndexMapping[id]];
	}
	else
	{
		return nullptr;
	}
}

