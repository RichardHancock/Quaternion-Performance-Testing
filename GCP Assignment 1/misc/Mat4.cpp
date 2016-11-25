#include "Mat4.h"

Mat4 Mat4::translate(Mat4 & mat, Vec4 pos)
{
	Mat4 result(mat);

	result.x.w = pos.x;
	result.y.w = pos.y;
	result.z.w = pos.z;
	result.w.w = pos.w;

	return result;
}

void Mat4::rotate(float angle, Vec3 axis)
{
	if (axis.x != 0.0f)
	{
		*this = rotateX(*this, angle);
		return;
	}
	if (axis.y != 0.0f)
	{
		*this = rotateY(*this, angle);
		return;
	}
	if (axis.z != 0.0f)
	{

		*this = rotateZ(*this, angle);
		return;
	}
}

Mat4 Mat4::rotateX(Mat4 & mat, float angle)
{
	float angleSin = sinf(angle);
	float angleCos = cosf(angle);

	Mat4 rotationMat(
		Vec4(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4(0.0f, angleCos, angleSin, 0.0f),
		Vec4(0.0f, -angleSin, angleCos, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	return (mat * rotationMat);
}

Mat4 Mat4::rotateY(Mat4 & mat, float angle)
{
	float angleSin = sinf(angle);
	float angleCos = cosf(angle);

	Mat4 rotationMat(
		Vec4(angleCos, 0.0f, angleSin, 0.0f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4(-angleSin, 0.0f, angleCos, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	return (mat * rotationMat);
}

Mat4 Mat4::rotateZ(Mat4 & mat, float angle)
{
	float angleSin = sinf(angle);
	float angleCos = cosf(angle);

	Mat4 rotationMat(
		Vec4(angleCos, angleSin, 0.0f, 0.0f),
		Vec4(-angleSin, angleCos, 0.0f, 0.0f),
		Vec4(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	return (mat * rotationMat);
}
