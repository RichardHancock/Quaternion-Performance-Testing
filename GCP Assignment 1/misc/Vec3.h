#pragma once

#include <iostream>
#include <cmath>

//Modified but a previous version was used in another assignment

/**
@brief Stores a 3D Vector or Position, as floats
*/
struct Vec3
{
	/** @brief	Default constructor. */
	Vec3() { }

	/**
	 @brief Constructor.
	
	 @param x The x coordinate.
	 @param y The y coordinate.
	 @param z The z coordinate.
	 */
	Vec3(float x, float y, float z) : x(x), y(y), z(z)
	{

	}

	/**
	@brief Create a Vec3
	@param XYZ X,Y and Z value
	*/
	Vec3(float XYZ) : x(XYZ), y(XYZ), z(XYZ)
	{

	}

	/// X positions
	float x;
	/// Y positions
	float y;
	/// Z positions
	float z;

	/**
	@brief Get the length of the vector
	@return float length of vector
	*/
	float getLength()
	{
		Vec3 temp;
		temp.x = pow(x, 2);
		temp.y = pow(y, 2);
		temp.z = pow(z, 2);
		float total = temp.x + temp.y + temp.z;

		return sqrt(total);
	}
	
	/**
	 @brief Get a normalized Vec3
	
	 @return A normalized Vec3.
	 */
	Vec3 normalize()
	{
		float length = getLength();

		if (length < 0.0001f) 
		{
			return Vec3(0.0f);
		}

		return Vec3(x / length, y / length, z / length);
	}

	Vec3* operator += (Vec3 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return this;
	}
	Vec3* operator -= (Vec3 b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return this;
	}

};

inline Vec3 operator + (Vec3 a, Vec3 b)
{
	Vec3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

inline Vec3 operator - (Vec3 a, Vec3 b)
{
	Vec3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

inline Vec3 operator * (Vec3 a, Vec3 b)
{
	Vec3 result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}

inline Vec3 operator / (Vec3 a, Vec3 b)
{
	Vec3 result;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return result;
}


inline std::ostream& operator << (std::ostream& os, const Vec3& a)
{
	os << "Vec3(" << a.x << ", " << a.y << ", " << a.z << ") ";
	return os;
}
inline bool operator == (const Vec3& a, const Vec3& b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
inline bool operator != (const Vec3& a, const Vec3& b)
{
	return (a.x != b.x || a.y != b.y || a.z != b.z);
}
