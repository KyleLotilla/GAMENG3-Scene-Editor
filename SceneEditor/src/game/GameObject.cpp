#include "game/GameObject.h"

GameObject::GameObject()
	: m_localPosition(0.0f, 0.0f, 0.0f), m_localScale(1.0f, 1.0f, 1.0f), m_localRotation(reactphysics3d::Quaternion::identity())
{
}

GameObject::~GameObject()
{
}

void GameObject::release()
{
}

void GameObject::setPosition(const Vec3 & position)
{
	this->m_localPosition = position;
}

Vec3 GameObject::getLocalPosition()
{
	return this->m_localPosition;
}

void GameObject::setScale(const Vec3 & scale)
{
	this->m_localScale = scale;
}

Vec3 GameObject::getLocalScale()
{
	return this->m_localScale;
}

void GameObject::setRotation(const Vec3 & rotation)
{
	float pi = atan(1) * 4.0f;
	this->m_localRotation = reactphysics3d::Quaternion::fromEulerAngles(rotation.m_x * (float)pi / 180.0f, rotation.m_y * (float)pi / 180.0f, rotation.m_z * (float)pi / 180.0f);
}

void GameObject::setRotation(reactphysics3d::Quaternion rotation)
{
	this->m_localRotation = rotation;
}

Vec3 GameObject::getLocalRotationVector()
{
	Vec3 rotation(0.0f, 0.0f, 0.0f);
	float pi = atan(1) * 4.0f;
	float sqw = m_localRotation.w * m_localRotation.w;
	float sqx = m_localRotation.x * m_localRotation.x;
	float sqy = m_localRotation.y * m_localRotation.y;
	float sqz = m_localRotation.z * m_localRotation.z;
	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	float test = m_localRotation.x * m_localRotation.w - m_localRotation.y * m_localRotation.z;

	if (test > 0.4995f * unit) { // singularity at north pole
		rotation.m_y = 2.0f * std::atan2(m_localRotation.y, m_localRotation.x) * (180.0f / pi);
		rotation.m_x = pi / 2.0f * (180.0f / pi);
		rotation.m_z = 0;
		return rotation;
	}
	if (test < -0.4995f * unit) { // singularity at south pole
		rotation.m_y = -2.0f * std::atan2(m_localRotation.y, m_localRotation.x) * (180.0f / pi);
		rotation.m_x = -pi / 2.0f * (180.0f / pi);
		rotation.m_z = 0;
		return rotation;
	}
	reactphysics3d::Quaternion q(m_localRotation.w, m_localRotation.z, m_localRotation.x, m_localRotation.y);
	rotation.m_y = (float)std::atan2(2.0f * q.x * q.w + 2.0f * q.y * q.z, 1 - 2.0f * (q.z * q.z + q.w * q.w)) * (180.0f / pi);     // Yaw
	rotation.m_x = (float)std::asin(2.0f * (q.x * q.z - q.w * q.y)) * (180.0f / pi);                             // Pitch
	rotation.m_z = (float)std::atan2(2.0f * q.x * q.y + 2.0f * q.z * q.w, 1 - 2.0f * (q.y * q.y + q.z * q.z)) * (180.0f / pi);      // Roll
	return rotation;
}

reactphysics3d::Quaternion GameObject::getLocalRotationQuaternion()
{
	return this->m_localRotation;
}

void GameObject::setID(int id)
{
	if (this->m_id < 0)
	{
		this->m_id = id;
	}
}

int GameObject::getID()
{
	return this->m_id;
}

void GameObject::addComponent(Component* component)
{
	component->setOwnerID(this->m_id);
	this->m_components.push_back(component);
}

void GameObject::removeComponent(Component* component)
{
	std::vector<Component*>::iterator it = this->m_components.begin();
	while (it != this->m_components.end())
	{
		if (*it == component)
		{
			delete *it;
			this->m_components.erase(it);
			return;
		}
		else
		{
			it++;
		}
	}
}
