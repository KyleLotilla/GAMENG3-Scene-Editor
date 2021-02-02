#pragma once
#include "PhysicsComponent.h"
#include "game/GameObjectManager.h"
#include "editor/EditorStateListener.h"

class PhysicsEngine : public EditorStateListener
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	void update(float delta_time);
	void setGameObjectManager(GameObjectManager* gameObjectManager);
	reactphysics3d::PhysicsCommon* getPhysicsCommon();
	reactphysics3d::PhysicsWorld* getPhysicsWorld();
	void stateUpdated(EditorState oldState, EditorState newState);

private:
	reactphysics3d::PhysicsCommon* m_physicsCommon;
	reactphysics3d::PhysicsWorld* m_physicsWorld;
	GameObjectManager* m_gameObjectManager;
};
