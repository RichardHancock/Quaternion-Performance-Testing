#pragma once

#include <iostream>
#include "Vec4.h"

class Mat4
{
public:

	Mat4()
	{

	}

	Mat4(float id) :
		x(id, 0, 0, 0),
		y(0, id, 0, 0),
		z(0, 0, id, 0),
		w(0, 0, 0, id)
	{}

	Mat4(Vec4 x, Vec4 y, Vec4 z, Vec4 w) :
		x(x), y(y), z(z), w(w)
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


	Vec4 x;
	Vec4 y;
	Vec4 z;
	Vec4 w;

	Mat4 transpose()
	{
		Mat4 result(0.0f);
		result.x.x = x.x;
		result.x.y = y.x;
		result.x.z = z.x;
		result.x.w = w.x;

		result.y.x = x.y;
		result.y.y = y.y;
		result.y.z = z.y;
		result.y.w = w.y;

		result.z.x = x.z;
		result.z.y = y.z;
		result.z.z = z.z;
		result.z.w = w.z;

		result.w.x = x.w;
		result.w.y = y.w;
		result.w.z = z.w;
		result.w.w = w.w;
		return result;
	}

	Mat4* operator += (Mat4 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return this;
	}

	Mat4* operator -= (Mat4 b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return this;
	}
};

inline Mat4 operator + (Mat4 a, Mat4 b)
{
	Mat4 result(0.0f);
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return result;
}

inline Mat4 operator - (Mat4 a, Mat4 b)
{
	Mat4 result(0.0f);
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}

inline Mat4 operator * (Mat4 a, Vec4 b)
{
	Mat4 result(0.0f);
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w * b;
	return result;
}

inline Mat4 operator * (Mat4 a, float b)
{
	Mat4 result(0.0f);
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w * b;
	return result;
}


inline bool operator == (const Mat4& a, const Mat4& b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
inline bool operator != (const Mat4& a, const Mat4& b)
{
	return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}
inline std::ostream& operator << (std::ostream& os, const Mat4& a)
{
	os << "Mat4{" << a.x << ",\n" << a.y << ",\n" << a.z << ",\n" << a.w << "\n}" << std::endl;
	return os;
}