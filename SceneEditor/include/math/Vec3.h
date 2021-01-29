#pragma once
#include <math.h>

class Vec3
{
public:
	Vec3();
	Vec3(float x, float y, float z);
	static Vec3 lerp(const Vec3& start, const Vec3& end, float delta);
	float getLength();
	Vec3 getPerpendicularUnitVector();
	Vec3 operator *(float num);
	Vec3 operator /(float num);
	Vec3 operator +(Vec3 vec);
	Vec3 operator -(Vec3 vec);
	~Vec3();

public:
	float m_x;
	float m_y;
	float m_z;
};