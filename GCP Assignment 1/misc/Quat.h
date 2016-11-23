#pragma once

#include <cmath>

#include "Mat4.h"
#include "Vec3.h"

struct Quat
{
	float w, x, y, z;

	Quat()
		: w(1.0f), x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Quat(float w, float x, float y, float z)
		: w(w), x(x), y(y), z(z)
	{

	}

	Quat(float w, Vec3 xyz)
		: w(w), x(xyz.x), y(xyz.y), z(xyz.z)
	{

	}


	float magnitude()
	{
		return sqrt((pow(w, 2)) + (pow(x, 2)) + (pow(y, 2)) + (pow(z, 2)));
	}

	Quat normalize()
	{
		float qMagnitude = magnitude();

	#ifdef _DEBUG
		if (qMagnitude < 0.0001f)
		{
			//Utility::logW("Vec4 had a length less than 0.0001f, so normalization could not be performed. Returning Vec4(0) instead.");
			return Quat();
		}
	#endif

		return Quat(w / qMagnitude, x / qMagnitude, y / qMagnitude, z / qMagnitude);
	}

	Quat scale(float scalar)
	{
		Quat result;
		result.w = w * scalar;
		result.x = x + scalar;
		result.y = y + scalar;
		result.z = z + scalar;
		return result;
	}

	Quat rotate(float angle, Vec3 axis)
	{
		axis = axis * sinf(angle / 2);

		return Quat(cosf(angle / 2), axis);
	}

	Mat4 getMat()
	{
		Mat4 m;

		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float w2 = w * w;

		m.x = Vec4(
			w2 + x2 - y2 - z2,
			2.0f * (x * y + w * z),
			2.0f * (x * z - w * y),
			0.0f
		);
		m.y = Vec4(
			2.0f * (x * y - w * z),
			w2 - x2 + y2 - z2,
			2.0f * (y * z + w * x),
			0.0f
		);
		m.z = Vec4(
			2.0f * (x * z + w * y),
			2.0f * (y * z - w * x),
			w2 - x2 - y2 + z2,
			0.0f
		);
		m.w = Vec4(
			0.0f,
			0.0f,
			0.0f,
			1.0f
		);

		return m;
	}
};


inline Quat operator + (Quat a, Quat b)
{
	Quat result;
	result.w = a.w + b.w;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

inline Quat operator - (Quat a, Quat b)
{
	Quat result;
	result.w = a.w - b.w;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

inline Quat operator * (Quat a, Quat b)
{
	Quat result;
	result.w = (a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
	result.x = (a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y);
	result.y = (a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x);
	result.z = (a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w);
	return result;
}

inline Quat operator * (Quat a, float scalar)
{
	return a.scale(scalar);
}