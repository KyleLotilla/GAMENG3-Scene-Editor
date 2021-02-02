#pragma once
#include "math/Mat4.h"
__declspec(align(16))
struct DefaultShaderInput
{
	Mat4 m_model;
	Mat4 m_view;
	Mat4 m_proj;
	float m_red;
	float m_green;
	float m_blue;
	float m_alpha;
};