#pragma once

#include <cmath>

#include "Mat4.h"
#include "Vec3.h"

/** @brief	A quaternion that represents a rotation. */
struct Quat
{
	/** @brief	The w component. */
	float w;
	/** @brief	The x component. */
	float x;
	/** @brief	The y component. */
	float y; 
	/** @brief	The z component. */
	float z;


	/** @brief	Default constructor. */
	Quat()
		: w(1.0f), x(0.0f), y(0.0f), z(0.0f)
	{

	}

	/**
	 @brief	Constructor.
	
	 @param	w	The w component.
	 @param	x	The x component.
	 @param	y	The y component.
	 @param	z	The z component.
	 */
	Quat(float w, float x, float y, float z)
		: w(w), x(x), y(y), z(z)
	{

	}

	/**
	 @brief	Constructor.
	
	 @param	w  	The w component.
	 @param	xyz	The xyz components.
	 */
	Quat(float w, Vec3 xyz)
		: w(w), x(xyz.x), y(xyz.y), z(xyz.z)
	{

	}


	/**
	 @brief	Gets the magnitude of the quaternion.
	
	 @return	The magnitude.
	 */
	float magnitude()
	{
		return sqrt((pow(w, 2)) + (pow(x, 2)) + (pow(y, 2)) + (pow(z, 2)));
	}

	/**
	 @brief	return a normalized quaternion.
	
	 @return	Normalized quaternion.
	 */
	Quat normalize()
	{
		float qMagnitude = magnitude();

	#ifdef _DEBUG
		if (qMagnitude < 0.0001f)
		{
			return Quat();
		}
	#endif

		return Quat(w / qMagnitude, x / qMagnitude, y / qMagnitude, z / qMagnitude);
	}

	/**
	 @brief	Scales the quaternion by a scalar value.
	
	 @param	scalar	The scalar value.
	
	 @return	Scaled Quaternion.
	 */
	Quat scale(float scalar)
	{
		Quat result;
		result.w = w * scalar;
		result.x = x + scalar;
		result.y = y + scalar;
		result.z = z + scalar;
		return result;
	}

	/**
	 @brief	Rotates the quaternion.
	
	 @param	angle	The angle in radians.
	 @param	axis 	The selected axis.
	 */
	void rotate(float angle, Vec3 axis)
	{
		axis = axis * sinf(angle / 2.0f);

		//Flip Y axis the correct way.
		axis.y = -axis.y;

		*this = Quat(cosf(angle / 2.0f), axis);
	}

	/**
	 @brief	Gets a transform matrix from the quaternion.
	
	 @return	The matrix.
	 */
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