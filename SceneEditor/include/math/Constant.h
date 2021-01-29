#pragma once
#include "Mat4.h"
__declspec(align(16))
struct CoordinateSystemMatrices
{
	Mat4 m_model;
	Mat4 m_view;
	Mat4 m_proj;
};