#include "game/Component.h"

void Component::setOwnerID(int ownerID)
{
	this->m_ownerID = ownerID;
}

int Component::getOwnerID()
{
	return this->m_ownerID;
}

void Component::setType(ComponentType type)
{
	this->m_type = type;
}

ComponentType Component::getType()
{
	return this->m_type;
}
