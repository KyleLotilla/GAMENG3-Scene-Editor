#pragma once
#include "PhysicsComponent.h"
#include "game/GameObjectManager.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	void update(float delta_time);
	void setGameObjectManager(GameObjectManager* gameObjectManager);
	reactphysics3d::PhysicsCommon* getPhysicsCommon();
	reactphysics3d::PhysicsWorld* getPhysicsWorld();

private:
	reactphysics3d::PhysicsCommon* m_physicsCommon;
	reactphysics3d::PhysicsWorld* m_physicsWorld;
	GameObjectManager* m_gameObjectManager;
};
