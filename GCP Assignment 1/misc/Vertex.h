#pragma once

#include "Vec2.h"
#include "Vec3.h"

//Was used in another assignment

/** @brief A vertex. */
struct Vertex
{
	Vec3 v; //< Vertex Position
	Vec3 vn; //< Vertex Normal
	Vec2 vt; //< Vertex Texture Coordinate
};

/** @brief A Vertex with tangent attributes*/
struct AdvVertex
{
	Vec3 v; //< Vertex Position
	Vec3 vn; //< Vertex Normal
	Vec2 vt; //< Vertex Texture Coordinate
	Vec3 tan; //< Tangent
	Vec3 bitan; //< BiTangent
};