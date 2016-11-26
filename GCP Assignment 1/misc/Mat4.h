#pragma once

#include <iostream>

#include "Vec4.h"
#include "Vec3.h"

/** @brief	A matrix 4x4. */
struct Mat4
{
	/** @brief	Default constructor. */
	Mat4()
	{

	}

	/**
	 @brief	Constructor.
	
	 @param	id	Set to 1.0f for identity matrix.
	 */
	Mat4(float id) :
		x(id, 0, 0, 0),
		y(0, id, 0, 0),
		z(0, 0, id, 0),
		w(0, 0, 0, id)
	{}

	/**
	 @brief	Constructor.
	
	 @param	x	Vec4 representing x row.
	 @param	y	Vec4 representing y row.
	 @param	z	Vec4 representing z row.
	 @param	w	Vec4 representing w row.
	 */
	Mat4(Vec4 x, Vec4 y, Vec4 z, Vec4 w) :
		x(x), y(y), z(z), w(w)
	{}

	/**
	 @brief	Constructor.
	
	 @param	xx	The x.x
	 @param	xy	The x.y
	 @param	xz	The x.z
	 @param	xw	The x.w
	 @param	yx	The y.x
	 @param	yy	The y.y
	 @param	yz	The y.z
	 @param	yw	The y.w
	 @param	zx	The z.x
	 @param	zy	The z.y
	 @param	zz	The z.z
	 @param	zw	The z.w
	 @param	wx	The w.x
	 @param	wy	The w.y
	 @param	wz	The w.z
	 @param	ww	The w.w
	 */
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


	/** @brief	X Row. */
	Vec4 x;

	/** @brief	Y Row. */
	Vec4 y;

	/** @brief	Z Row. */
	Vec4 z;

	/** @brief	W Row. */
	Vec4 w;


	/**
	 @brief	Gets the transpose of the matrix.
	
	 @return	transposed Mat4.
	 */
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

	/**
	 @brief	Create a Perspective Matrix.
	
	 @param	fov   	The field of view.
	 @param	aspect	The aspect ratio (16/9) or (4/3) probably.
	 @param	near  	The near clipping plane.
	 @param	far   	The far clipping plane.
	
	 @return	A Mat4.
	 */
	static Mat4 perspective(float fov, float aspect, float near, float far)
	{
		float tanFov = tanf(fov / 2.0f);

		Mat4 results(0.0f);
		results.x.x = (1.0f / (aspect * tanFov));
		results.y.y = (1.0f / tanFov);
		results.z.z = -((far + near) / (far - near));
		results.z.w = -1.0f;
		results.w.z = -((2.0f * far * near) / (far - near));
		return results;
	}


	/**
	 @brief	Returns a translated matrix.
	
	 @param [in]	mat	The current matrix.
	 @param	pos  	    The new position.
	
	 @return	A Mat4.
	 */
	static Mat4 translate(Mat4& mat, Vec4 pos);

	/**
	 @brief	Rotates around an axis.
	 Only uses the first found axis. It does not support multiple rotation at the same time
	
	 @param	angle	The angle in radians.
	 @param	axis 	The axis (1.0f) if active.
	 */
	void rotate(float angle, Vec3 axis);

	/**
	 @brief	Rotate around x axis.
	
	 @param [in,out]	mat	The matrix.
	 @param	angle		   	The angle in radians.
	
	 @return	A Mat4.
	 */
	static Mat4 rotateX(Mat4& mat, float angle);

	/**
	 @brief	Rotate around y axis.
	
	 @param [in,out]	mat	The matrix.
	 @param	angle		   	The angle in radians.
	
	 @return	A Mat4.
	 */
	static Mat4 rotateY(Mat4& mat, float angle);

	/**
	 @brief	Rotate around z axis.
	
	 @param [in,out]	mat	The matrix.
	 @param	angle		   	The angle in radians.
	
	 @return	A Mat4.
	 */
	static Mat4 rotateZ(Mat4& mat, float angle);

	/**
	 @brief	Gets value pointer of first float.
	
	 @return	null if it fails, else the value pointer.
	 */
	float* getValuePtr()
	{
		return &x.x;
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

	inline const float* operator [] (unsigned int index) const
	{
		//ONLY USED FOR RENDERING, NOT THE TRANSFORMATIONS SO DOES NOT AFFECT BENCHMARK RESULTS
		//Not the best solution, in future rewrite to be an array of floats
		
		if (index >= 0 && index < 4)
		{
			return x[index];
		}
		else if (index >= 4 && index < 8)
		{
			return y[index - 4];
		}
		else if (index >= 8 && index < 12)
		{
			return z[index - 8];
		}
		else if (index >= 12 && index < 16)
		{
			return w[index - 12];
		}
		else
		{
			return nullptr;
		}
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

inline Mat4 operator * (Mat4 a, Mat4 b)
{
	Mat4 result;
	result.x = Vec4(
		a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x,
		a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y,
		a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z,
		a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w
	);
	result.y = Vec4(
		a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x,
		a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y,
		a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z,
		a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w
	);
	result.z = Vec4(
		a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x,
		a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y,
		a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z,
		a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w
	);
	result.w = Vec4(
		a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x,
		a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y,
		a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z,
		a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w
	);
	return result;
}

inline Mat4 operator * (Mat4 a, Vec4 b)
{
	Mat4 result;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w * b;
	return result;
}

inline Mat4 operator * (Mat4 a, float b)
{
	Mat4 result;
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