#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "editor/EditorStateListener.h"
#include <vector>

class GameObjectManager : public EditorStateListener
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
	void saveObjectState();
	void restoreObjectState();
	void stateUpdated(EditorState oldState, EditorState newState);

private:
	std::unordered_map<int, int> m_idIndexMapping;
	std::vector<GameObject*> m_gameObjects;
	std::vector<Transform> m_transformStates;
	std::vector<int> m_idPool;
	int m_numID = 10000;
};

