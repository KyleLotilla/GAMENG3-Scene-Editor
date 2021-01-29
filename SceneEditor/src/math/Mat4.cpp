#include "math/Mat4.h"

Mat4::Mat4()
{
}

Mat4::~Mat4()
{
}

void Mat4::setIdentity()
{
	memset(m_mat, 0, sizeof(float) * 16);
	m_mat[0][0] = 1;
	m_mat[1][1] = 1;
	m_mat[2][2] = 1;
	m_mat[3][3] = 1;
}

void Mat4::setTranslation(const Vec3 & translation)
{
	this->setIdentity();
	m_mat[3][0] = translation.m_x;
	m_mat[3][1] = translation.m_y;
	m_mat[3][2] = translation.m_z;
}

void Mat4::setRotationX(float x)
{
	this->setIdentity();
	double pi = atan(1) * 4;
	float radian = (x * (float)pi) / 180.0f;

	m_mat[1][1] = cos(radian);
	m_mat[1][2] = sin(radian);
	m_mat[2][1] = -sin(radian);
	m_mat[2][2] = cos(radian);
}

void Mat4::setRotationY(float y)
{
	this->setIdentity();
	double pi = atan(1) * 4;
	float radian = (y * (float)pi) / 180.0f;

	m_mat[0][0] = cos(radian);
	m_mat[0][2] = -sin(radian);
	m_mat[2][0] = sin(radian);
	m_mat[2][2] = cos(radian);
}

void Mat4::setRotationZ(float z)
{
	this->setIdentity();
	double pi = atan(1) * 4;
	float radian = (z * (float)pi) / 180.0f;

	m_mat[0][0] = cos(radian);
	m_mat[0][1] = sin(radian);
	m_mat[1][0] = -sin(radian);
	m_mat[1][1] = cos(radian);
}

void Mat4::setScale(const Vec3 & scale)
{
	this->setIdentity();
	m_mat[0][0] = scale.m_x;
	m_mat[1][1] = scale.m_y;
	m_mat[2][2] = scale.m_z;
}

void Mat4::setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	memset(m_mat, 0, sizeof(float) * 16);
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	m_mat[0][0] = xscale;
	m_mat[1][1] = yscale;
	m_mat[2][2] = zfar / (zfar - znear);
	m_mat[2][3] = 1.0f;
	m_mat[3][2] = (-znear * zfar) / (zfar - znear);
}

void Mat4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	this->setIdentity();
	m_mat[0][0] = 2.0f / width;
	m_mat[1][1] = 2.0f / height;
	m_mat[2][2] = 1.0f / (far_plane - near_plane);
	m_mat[3][2] = -(near_plane / (far_plane - near_plane));
}

Vec3 Mat4::getDirectionX()
{
	return Vec3(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
}

Vec3 Mat4::getDirectionZ()
{
	return Vec3(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
}

float Mat4::getDeterminant()
{
	Vec4 minor, v1, v2, v3;
	float det;

	v1 = Vec4(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
	v2 = Vec4(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
	v3 = Vec4(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


	minor.cross(v1, v2, v3);
	det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
		this->m_mat[3][3] * minor.m_w);
	return det;
}

Mat4 Mat4::inverse()
{
	int a, i, j;
	Mat4 inverseMatrix;
	Vec4 v, vec[3];
	float det = 0.0f;

	det = this->getDeterminant();
	if (!det) return *this;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].m_x = (this->m_mat[j][0]);
				vec[a].m_y = (this->m_mat[j][1]);
				vec[a].m_z = (this->m_mat[j][2]);
				vec[a].m_w = (this->m_mat[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		inverseMatrix.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
		inverseMatrix.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
		inverseMatrix.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
		inverseMatrix.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
	}

	return inverseMatrix;
}

void Mat4::operator*=(const Mat4 & matrix)
{
	float product[4][4] = {};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			product[i][j] =
				m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
				m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
		}
	}
	memcpy(this->m_mat, product, sizeof(float) * 16);
}

Mat4 Mat4::operator*(const Mat4 & matrix)
{
	Mat4 product;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			product.m_mat[i][j] =
				m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
				m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
		}
	}
	return product;
}
