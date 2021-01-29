#pragma once
#include "math/Mat4.h"

struct ViewportParams
{
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
	Mat4 m_projection;
	Mat4 m_view;
};