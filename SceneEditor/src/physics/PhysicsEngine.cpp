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
				component->setTransform(gameObject->getLocalPosition(), gameObject->getLocalRotationQuaternion(), gameObject->getLocalScale());
			}
		}
		*/

		if (delta_time > this->MAX_TIMESTEP)
		{
			this->m_physicsWorld->update(this->MAX_TIMESTEP);
		}
		else
		{
			this->m_physicsWorld->update(delta_time);
		}

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

void PhysicsEngine::stateUpdated(EditorState oldState, EditorState newState)
{
	if (oldState == EditorState::PLAY_MODE && newState == EditorState::EDIT_MODE)
	{
		for (GameObject* gameObject : *(this->m_gameObjectManager))
		{
			PhysicsComponent* component = nullptr;
			if (component = gameObject->findComponent<PhysicsComponent>(ComponentType::PHYSICS))
			{
				component->setIsActive(false);
			}
		}
	}
	else if (oldState == EditorState::EDIT_MODE && newState == EditorState::PLAY_MODE)
	{
		for (GameObject* gameObject : *(this->m_gameObjectManager))
		{
			PhysicsComponent* component = nullptr;
			if (component = gameObject->findComponent<PhysicsComponent>(ComponentType::PHYSICS))
			{
				component->setIsActive(true);
				component->setTransform(gameObject->getLocalPosition(), gameObject->getLocalRotationQuaternion(), gameObject->getLocalScale());
			}
		}
	}
}

