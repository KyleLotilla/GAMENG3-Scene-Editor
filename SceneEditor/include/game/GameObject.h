#pragma once
#define NOMINMAX
#include "graphics/DeviceContext.h"
#include "graphics/ViewportParams.h"
#include "Component.h"
#include "math/Vec3.h"
#include "reactphysics3d/reactphysics3d.h"
#include "math/Mat4.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void update(float deltaTime) = 0;
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams) = 0;
	virtual void release();
	void setPosition(const Vec3& position);
	Vec3 getLocalPosition();
	void setScale(const Vec3& scale);
	Vec3 getLocalScale();
	void setRotation(const Vec3& rotation);
	void setRotation(reactphysics3d::Quaternion rotation);
	Vec3 getLocalRotationVector();
	reactphysics3d::Quaternion getLocalRotationQuaternion();
	void setID(int id);
	int getID();
	void addComponent(Component* component);
	void removeComponent(Component* component);
	template <typename Component_t>  Component_t* findComponent(ComponentType type);
	template <typename Component_t> std::vector<Component_t> findComponents(ComponentType type);
	Mat4 getModelMatrix();
	void setParent(GameObject* parent);
	GameObject* getParent();

protected:
	int m_id = -1;
	Vec3 m_localPosition;
	Vec3 m_localScale;
	reactphysics3d::Quaternion m_localRotation;
	std::vector<Component*> m_components;
	GameObject* m_parent = nullptr;
};

template<typename Component_t>
inline Component_t* GameObject::findComponent(ComponentType type)
{
	for (Component* component : this->m_components)
	{
		if (component->getType() == type)
		{
			return static_cast<Component_t*>(component);
		}
	}
	return nullptr;
}

template<typename Component_t>
inline std::vector<Component_t> GameObject::findComponents(ComponentType type)
{
	std::vector<Component_t> componentList;
	for (Component* component : this->m_components)
	{
		if (component.getType() == type)
		{
			componentList.push_back(static_cast<Component_t>(component));
		}
	}
	return componentList;
}
