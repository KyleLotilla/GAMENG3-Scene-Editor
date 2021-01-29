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
	Vec3 rotation = owner->getLocalRotation();
	Vec3 scale = owner->getLocalScale();
	reactphysics3d::Transform transform;
	reactphysics3d::Transform boxTransform = reactphysics3d::Transform::identity();
	double pi = atan(1) * 4;

	transform.setPosition(reactphysics3d::Vector3(position.m_x, position.m_y, position.m_z));
	transform.setOrientation(reactphysics3d::Quaternion::fromEulerAngles((rotation.m_x * (float)pi) / 180.0f, (rotation.m_y * (float)pi) / 180.0f, (rotation.m_z * (float)pi) / 180.0f));
	this->m_boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	this->m_rigidBody = physicsWorld->createRigidBody(transform);
	this->m_rigidBody->addCollider(this->m_boxShape, boxTransform);
	this->m_rigidBody->updateMassPropertiesFromColliders();
	this->m_rigidBody->setMass(this->m_mass);
	this->m_rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
}

void PhysicsComponent::setTransform(Vec3 position, Vec3 rotation, Vec3 scale)
{
	double pi = atan(1) * 4;
	reactphysics3d::Transform transform = this->m_rigidBody->getTransform();
	transform.setPosition(reactphysics3d::Vector3(position.m_x, position.m_y, position.m_z));
	transform.setOrientation(reactphysics3d::Quaternion::fromEulerAngles((rotation.m_x * (float)pi) / 180.0f, (rotation.m_y * (float)pi) / 180.0f, (rotation.m_z * (float)pi) / 180.0f));
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

Vec3 PhysicsComponent::getRotation()
{
	Vec3 rotation(0.0f, 0.0f, 0.0f);
	reactphysics3d::Quaternion orientation = this->m_rigidBody->getTransform().getOrientation();
	float pi = atan(1) * 4.0f;

	// roll (z-axis rotation)
	double sinr_cosp = 2 * (orientation.w * orientation.x + orientation.y * orientation.z);
	double cosr_cosp = 1 - 2 * (orientation.x * orientation.x + orientation.y * orientation.y);
	rotation.m_z = std::atan2(sinr_cosp, cosr_cosp) * (180.0f / pi);

	// pitch (x-axis rotation)
	double sinp = 2 * (orientation.w * orientation.y - orientation.z * orientation.x);
	if (std::abs(sinp) >= 1)
		rotation.m_x = std::copysign(pi / 2, sinp) * (180.0f / pi); // use 90 degrees if out of range
	else
		rotation.m_x = std::asin(sinp) * (180.0f / pi);

	// yaw (y-axis rotation)
	double siny_cosp = 2 * (orientation.w * orientation.z + orientation.x * orientation.y);
	double cosy_cosp = 1 - 2 * (orientation.y * orientation.y + orientation.z * orientation.z);
	rotation.m_y = std::atan2(siny_cosp, cosy_cosp) * (180.0f / pi);

	return rotation;
}

void PhysicsComponent::setBodyType(reactphysics3d::BodyType bodyType)
{
	this->m_rigidBody->setType(bodyType);
}
