#pragma once

class Vec4
{
public:
	Vec4();
	Vec4(float x, float y, float z, float w);
	~Vec4();
	void cross(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);

public:
	float m_x, m_y, m_z, m_w;
};