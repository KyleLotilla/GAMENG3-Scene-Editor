#pragma once
#include "ComponentType.h"

class Component
{
public: 
	void setOwnerID(int ownerID);
	int getOwnerID();
	void setType(ComponentType type);
	ComponentType getType();

protected:
	ComponentType m_type = NOTSET;
	int m_ownerID = -1;
};