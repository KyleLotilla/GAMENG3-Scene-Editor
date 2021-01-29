#pragma once
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void addGameObject(GameObject* gameObject);
	void removeGameObject(int id);
	void update(float deltaTime);
	void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	void release();
	std::vector<GameObject*>::iterator begin();
	std::vector<GameObject*>::iterator end();
	GameObject* getGameObject(int id);

private:
	std::unordered_map<int, int> m_idIndexMapping;
	std::vector<GameObject*> m_gameObjects;
	std::vector<int> m_idPool;
	int m_numID = 10000;
};

