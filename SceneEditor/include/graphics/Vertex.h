#pragma once
#include "math/Vec2.h"
#include "math/Vec3.h"

/*
struct Vertex
{
	Vec3 position;
	Vec3 position1;
	Vec3 color;
	Vec3 color1;
};
*/


struct Vertex
{
	Vec3 position;
	Vec3 color;
};

struct VertexTexture
{
	Vec3 position;
	Vec2 texcoord;
};
