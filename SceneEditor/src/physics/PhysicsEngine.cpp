#include "physics/PhysicsEngine.h"


PhysicsEngine::PhysicsEngine()
{
	this->m_physicsCommon = new reactphysics3d::PhysicsCommon();
	reactphysics3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
	this->m_physicsWorld = this->m_physicsCommon->createPhysicsWorld(settings);
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::update(float delta_time)
{
	if (delta_time > 0.0f)
	{
		/*
		for (GameObject* gameObject : *(this->m_gameObjectManager))
		{
			PhysicsComponent* component = nullptr;
			if (component = gameObject->findComponent<PhysicsComponent>(ComponentType::PHYSICS))
			{
				component->setTransform(gameObject->getLocalPosition(), gameObject->getLocalRotation(), gameObject->getLocalScale());
			}
		}
		*/

		this->m_physicsWorld->update(delta_time * 0.5);

		for (GameObject* gameObject : *(this->m_gameObjectManager))
		{
			PhysicsComponent* component = nullptr;
			if (component = gameObject->findComponent<PhysicsComponent>(ComponentType::PHYSICS))
			{
				gameObject->setPosition(component->getPosition());
				gameObject->setRotation(component->getRotation());
			}
		}
	}
}

void PhysicsEngine::setGameObjectManager(GameObjectManager* gameObjectManager)
{
	this->m_gameObjectManager = gameObjectManager;
}

reactphysics3d::PhysicsCommon* PhysicsEngine::getPhysicsCommon()
{
	return this->m_physicsCommon;
}

reactphysics3d::PhysicsWorld* PhysicsEngine::getPhysicsWorld()
{
	return this->m_physicsWorld;
}

