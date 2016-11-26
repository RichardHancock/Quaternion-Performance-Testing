#pragma once

#include <iostream>
#include <cmath>

//Modified but a previous version was used in another assignment

/**
@brief Stores a 4D Vector or Position, as floats
*/
struct Vec4
{
	/** @brief	Default constructor. */
	Vec4() { }

	/**
	@brief Constructor.

	@param x The x coordinate.
	@param y The y coordinate.
	@param z The z coordinate.
	@param w The w coordiante.
	*/
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{

	}

	/**
	@brief Create a Vec4
	@param XYZW X,Y,Z,W value
	*/
	Vec4(float XYZW) : x(XYZW), y(XYZW), z(XYZW), w(XYZW)
	{

	}

	/// X, Y, Z, W positions
	float x, y, z, w;

	/**
	@brief Get the length of the vector
	@return float length of vector
	*/
	float getLength()
	{
		Vec4 temp;
		temp.x = pow(x, 2);
		temp.y = pow(y, 2);
		temp.z = pow(z, 2);

		float total = temp.x + temp.y + temp.z;

		return sqrt(total);
	}

	/**
	@brief Get a normalized Vec4

	@return A normalized Vec4.
	*/
	Vec4 normalize()
	{
		float length = getLength();

	#ifdef _DEBUG
		if (length < 0.0001f)
		{
			//Utility::logW("Vec4 had a length less than 0.0001f, so normalization could not be performed. Returning Vec4(0) instead.");
			return Vec4(0.0f);
		}
	#endif
		return Vec4(x / length, y / length, z / length, w / length);
	}

	/**
	 @brief	Compute Dot product of 2 Vec4s.
	
	 @param	a	Vec4 A.
	 @param	b	Vec4 B.
	
	 @return	The Dot Product.
	 */
	static float dotProduct(Vec4 a, Vec4 b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	/**
	 @brief	Compute Cross product of 2 Vec4s.
	
	 @param	a	Vec4 A.
	 @param	b	Vec4 B.
	
	 @return	The Cross Product.
	 */
	static Vec4 crossProduct(Vec4 a, Vec4 b)
	{
		Vec4 result;

		result.x = (a.y * b.z) - (a.z * b.y);
		result.y = (a.z * b.x) - (a.x * b.z);
		result.z = (a.x * b.y) - (a.y * b.x);

		result.w = 1.0f;
		return result;
	}


	Vec4* operator += (Vec4 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return this;
	}
	Vec4* operator -= (Vec4 b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return this;
	}

	inline const float* operator [] (unsigned int index) const
	{
		//ONLY USED FOR RENDERING, NOT THE TRANSFORMATIONS SO DOES NOT AFFECT BENCHMARK RESULTS
		//Not the best solution, in future rewrite to be an array of floats
		switch (index)
		{
		case 0:
			return &x;
			break;
		case 1:
			return &y;
			break;
		case 2:
			return &z;
			break;
		case 3:
			return &w;
			break;
		default:
			return nullptr;
			break;
		}
	}
	

};



inline Vec4 operator + (Vec4 a, Vec4 b)
{
	Vec4 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return result;
}

inline Vec4 operator - (Vec4 a, Vec4 b)
{
	Vec4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}

inline Vec4 operator * (Vec4 a, Vec4 b)
{
	return Vec4::crossProduct(a, b);
}

inline Vec4 operator * (Vec4 a, float b)
{
	Vec4 result;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w;
	return result;
}

/*
inline Vec4 operator / (Vec4 a, Vec4 b)
{
	Vec4 result;
	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	result.w = a.w / b.w;
	return result;
}
*/

inline std::ostream& operator << (std::ostream& os, const Vec4& a)
{
	os << "Vec4(" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << ")";
	return os;
}
inline bool operator == (const Vec4& a, const Vec4& b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
inline bool operator != (const Vec4& a, const Vec4& b)
{
	return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}
