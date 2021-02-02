#pragma once
#include "reactphysics3d/reactphysics3d.h"
#include "math/Vec3.h"

struct Transform
{
	Vec3 m_position;
	reactphysics3d::Quaternion m_rotation;
	Vec3 m_scale;
};