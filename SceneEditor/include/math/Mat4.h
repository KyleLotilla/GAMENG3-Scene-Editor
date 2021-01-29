#pragma once
#include <memory>
#include "Vec3.h"
#include "Vec4.h"

class Mat4
{
public:
	Mat4();
	~Mat4();
	void setIdentity();
	void setTranslation(const Vec3& translation);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	void setScale(const Vec3& scale);
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	Vec3 getDirectionX();
	Vec3 getDirectionZ();
	float getDeterminant();
	Mat4 inverse();
	void operator *=(const Mat4& matrix);
	Mat4 operator *(const Mat4& matrix);
	
public:
	float m_mat[4][4] = {};
};
