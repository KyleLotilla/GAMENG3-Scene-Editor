#include "physics/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
	this->m_type = ComponentType::PHYSICS;
}

PhysicsComponent::~PhysicsComponent()
{
	delete m_rigidBody;
}

void PhysicsComponent::init(reactphysics3d::PhysicsCommon* physicsCommon, reactphysics3d::PhysicsWorld* physicsWorld, GameObject* owner)
{
	Vec3 position = owner->getLocalPosition();
	Vec3 scale = owner->getLocalScale();
	reactphysics3d::Transform transform;
	reactphysics3d::Transform boxTransform = reactphysics3d::Transform::identity();
	double pi = atan(1) * 4;

	transform.setPosition(reactphysics3d::Vector3(position.m_x, position.m_y, position.m_z));
	transform.setOrientation(owner->getLocalRotationQuaternion());
	this->m_boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	this->m_rigidBody = physicsWorld->createRigidBody(transform);
	this->m_rigidBody->addCollider(this->m_boxShape, boxTransform);
	this->m_rigidBody->updateMassPropertiesFromColliders();
	this->m_rigidBody->setMass(this->m_mass);
	this->m_rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
}

void PhysicsComponent::setTransform(Vec3 position, reactphysics3d::Quaternion rotation, Vec3 scale)
{
	double pi = atan(1) * 4;
	reactphysics3d::Transform transform = this->m_rigidBody->getTransform();
	transform.setPosition(reactphysics3d::Vector3(position.m_x, position.m_y, position.m_z));
	transform.setOrientation(rotation);
	this->m_rigidBody->setTransform(transform);
	this->m_boxShape->setHalfExtents(reactphysics3d::Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	//this->m_rigidBody->updateMassPropertiesFromColliders();
}

Vec3 PhysicsComponent::getPosition()
{
	reactphysics3d::Transform transform = this->m_rigidBody->getTransform();
	reactphysics3d::Vector3 position = transform.getPosition();
	return Vec3(position.x, position.y, position.z);
}

reactphysics3d::Quaternion PhysicsComponent::getRotation()
{
	reactphysics3d::Quaternion orientation = this->m_rigidBody->getTransform().getOrientation();
	return orientation;
}

void PhysicsComponent::setBodyType(reactphysics3d::BodyType bodyType)
{
	this->m_rigidBody->setType(bodyType);
}
