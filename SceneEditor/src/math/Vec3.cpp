#include "math/Vec3.h"

Vec3::Vec3()
	: m_x(0.0f), m_y(0.0f), m_z(0.0f)
{
}

Vec3::Vec3(float x, float y, float z)
	: m_x(x), m_y(y), m_z(z)
{
}

Vec3 Vec3::lerp(const Vec3 & start, const Vec3 & end, float delta)
{
	Vec3 v;
	v.m_x = start.m_x*(1.0f - delta) + end.m_x*(delta);
	v.m_y = start.m_y*(1.0f - delta) + end.m_y*(delta);
	v.m_z = start.m_z*(1.0f - delta) + end.m_z*(delta);
	return v;
}

float Vec3::getLength()
{
	return sqrtf(pow(this->m_x, 2.0f) + pow(this->m_y, 2.0f) + pow(this->m_z, 2.0f));
}

Vec3 Vec3::getPerpendicularUnitVector()
{
	return Vec3();
}

Vec3 Vec3::operator*(float num)
{
	return Vec3(m_x*num, m_y*num, m_z*num);
}

Vec3 Vec3::operator/(float num)
{
	return Vec3(this->m_x / num, this->m_y / num, this->m_z / num);
}

Vec3 Vec3::operator+(Vec3 vec)
{
	return Vec3(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
}

Vec3 Vec3::operator-(Vec3 vec)
{
	return Vec3(this->m_x - vec.m_x, this->m_y - vec.m_y, this->m_z - vec.m_z);
}

Vec3::~Vec3()
{
}
