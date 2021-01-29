#include "game/GameObject.h"

GameObject::GameObject()
	: m_localPosition(0.0f, 0.0f, 0.0f), m_localScale(1.0f, 1.0f, 1.0f)
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
	this->m_localRotation = rotation;
}

Vec3 GameObject::getLocalRotation()
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
