#pragma once

#include <iostream>
#include "Vec4.h"

class Mat4
{
public:

	Mat4() :
		x(1, 0, 0, 0),
		y(0, 1, 0, 0),
		z(0, 0, 1, 0),
		w(0, 0, 0, 1)
	{}

	Mat4(
		float xx, float xy, float xz, float xw,
		float yx, float yy, float yz, float yw,
		float zx, float zy, float zz, float zw,
		float wx, float wy, float wz, float ww
		) :
		x(xx, xy, xz, xw),
		y(yx, yy, yz, yw),
		z(zx, zy, zz, zw),
		w(wx, wy, wz, ww)
	{}

	Mat4(Vec4 x, Vec4 y, Vec4 z, Vec4 w) : x(x), y(y), z(z), w(w) 
	{}

	Vec4 x;
	Vec4 y;
	Vec4 z;
	Vec4 w;
};

inline Mat4 operator + (Mat4 a, Mat4 b)
{
	Mat4 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return result;
}

inline Mat4 operator - (Mat4 a, Mat4 b)
{
	Mat4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}
/*
inline Mat4 operator * (Mat4 a, Mat4 b)
{
	Mat4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}
*/

inline std::ostream& operator << (std::ostream& os, const Mat4& a)
{
	os << "Mat4{" << a.x << ",\n" << a.y << ",\n" << a.z << ",\n" << a.w << "\n}" << std::endl;
	return os;
}