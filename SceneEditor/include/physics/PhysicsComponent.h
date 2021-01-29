#pragma once
#define NOMINMAX
#include "game/Component.h"
#include "game/GameObject.h"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	void init(reactphysics3d::PhysicsCommon* physicsCommon, reactphysics3d::PhysicsWorld* physicsWorld, GameObject* owner);
	void setTransform(Vec3 position, Vec3 rotation, Vec3 scale);
	Vec3 getPosition();
	Vec3 getRotation();
	void setBodyType(reactphysics3d::BodyType bodyType);

private:
	reactphysics3d::RigidBody* m_rigidBody;
	reactphysics3d::BoxShape* m_boxShape;
	float m_mass = 1000.0f;
};