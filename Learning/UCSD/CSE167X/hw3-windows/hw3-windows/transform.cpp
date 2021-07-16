#include <iostream>
#include <math.h>
#include "transform.h"

#define PI 3.14159265359

Vector3::Vector3()
	: x_{ 0.0f }, y_{ 0.0f }, z_{ 0.0f }
{}

Vector3::Vector3(float x, float y, float z)
	: x_{ x }, y_{ y }, z_{ z }
{}

Vector3::~Vector3() {}

Vector3 Vector3::operator+(Vector3 v)
{
	Vector3 result;
	result.x_ = x_ + v.x_;
	result.y_ = y_ + v.y_;
	result.z_ = z_ + v.z_;

	return result;
}

Vector3 Vector3::operator-(Vector3 v)
{
	Vector3 result;
	result.x_ = x_ - v.x_;
	result.y_ = y_ - v.y_;
	result.z_ = z_ - v.z_;

	return result;
}

Vector3 Vector3::operator*(float scalar)
{
	Vector3 result;
	result.x_ = x_ * scalar;
	result.y_ = y_ * scalar;
	result.z_ = z_ * scalar;

	return result;
}

Vector3 Vector3::operator/(float scalar)
{
	if (scalar == 0)
	{
		std::cout << "ERROR: Can't divide by zero" << std::endl;
		// TODO: Exit program
	}
	Vector3 result;
	result.x_ = x_ / scalar;
	result.y_ = y_ / scalar;
	result.z_ = z_ / scalar;

	return result;
}

Vector4::Vector4()
	: x_{ 0.0f }, y_{ 0.0f }, z_{ 0.0f }, w_{ 0.0f }
{}

Vector4::Vector4(float x, float y, float z, float w)
	: x_{ x }, y_{ y }, z_{ z }, w_{ w }
{}

Vector4::~Vector4()
{}

Vector4 Vector4::operator+(Vector4 v)
{
	Vector4 result;
	result.x_ = x_ + v.x_;
	result.y_ = y_ + v.y_;
	result.z_ = z_ + v.z_;
	result.w_ = w_ + v.w_;

	return result;
}

Vector4 Vector4::operator-(Vector4 v)
{
	Vector4 result;
	result.x_ = x_ - v.x_;
	result.y_ = y_ - v.y_;
	result.z_ = z_ - v.z_;
	result.w_ = w_ - v.w_;

	return result;
}

Vector4 Vector4::operator*(float scalar)
{
	Vector4 result;
	result.x_ = x_ * scalar;
	result.y_ = y_ * scalar;
	result.z_ = z_ * scalar;
	result.w_ = w_ * scalar;

	return result;
}

Vector4 Vector4::operator/(float scalar)
{
	if (scalar == 0)
	{
		std::cout << "ERROR: Can't divide by zero" << std::endl;
		// TODO: Exit program
	}
	Vector4 result;
	result.x_ = x_ / scalar;
	result.y_ = y_ / scalar;
	result.z_ = z_ / scalar;
	result.w_ = w_ / scalar;

	return result;
}

Vector3 Normalize(Vector3 v)
{
	float norm = sqrt(pow(v.x_, 2) + pow(v.y_, 2) + pow(v.z_, 2));
	return v / norm;
}

Vector4 Normalize(Vector4 v)
{
	float norm = sqrt(pow(v.x_, 2) + pow(v.y_, 2) + pow(v.z_, 2) + pow(v.w_, 2));
	return v / norm;
}

Vector3 Cross(Vector3 a, Vector3 b)
{
	float i = a.y_ * b.z_ - a.z_ * b.y_;
	float j = -(a.x_ * b.z_ - a.z_ * b.x_);
	float k = a.x_ * b.y_ - a.y_ * b.x_;

	return Vector3(i, j, k);
}

Matrix3::Matrix3()
	: mat_{ 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f }
{}

Matrix3::Matrix3(float f)
	: mat_{ f,f,f,f,f,f,f,f,f }
{}

Matrix3::Matrix3(Vector3 column0, Vector3 column1, Vector3 column2)
	: mat_{ 0.0f }
{
	mat_[0] = column0.x_;
	mat_[1] = column0.y_;
	mat_[2] = column0.z_;
	mat_[3] = column1.x_;
	mat_[4] = column1.y_;
	mat_[5] = column1.z_;
	mat_[6] = column2.x_;
	mat_[7] = column2.y_;
	mat_[8] = column2.z_;
}

Matrix3::~Matrix3() {}

Vector3 Matrix3::row(int index)
{
	return Vector3(mat_[index], mat_[index + 3], mat_[index + 6]);
}

Vector3 Matrix3::column(int index)
{
	return Vector3(mat_[index*3], mat_[index*3 + 1], mat_[index*3 + 2]);
}

Matrix3 operator+(Matrix3 a, Matrix3 b)
{
	Matrix3 result(0.0f);
	for (int i = 0; i < a.length(); i++)
		result.mat_[i] = a.mat_[i] + b.mat_[i];

	return result;
}

Matrix3 operator-(Matrix3 a, Matrix3 b)
{
	Matrix3 result(0.0f);
	for (int i = 0; i < a.length(); i++)
		result.mat_[i] = a.mat_[i] - b.mat_[i];

	return result;
}

Matrix3 operator*(Matrix3 m, float scalar)
{
	Matrix3 result(0.0f);
	for (int i = 0; i < m.length(); i++)
		result.mat_[i] = m.mat_[i] * scalar;

	return result;
}
Matrix3 operator*(float scalar, Matrix3 m)
{
	return m * scalar;
}
Matrix3 operator/(Matrix3 m, float scalar)
{
	return m * float(1 / scalar);
}

Matrix4::Matrix4()
	: mat_{ 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f
	,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f }
{}

Matrix4::Matrix4(float f)
	: mat_{ f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f }
{}

Matrix4::Matrix4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3)
	: mat_{ 0.0f }
{
	mat_[0] = column0.x_;
	mat_[1] = column0.y_;
	mat_[2] = column0.z_;
	mat_[3] = column0.w_;
	mat_[4] = column1.x_;
	mat_[5] = column1.y_;
	mat_[6] = column1.z_;
	mat_[7] = column1.w_;
	mat_[8] = column2.x_;
	mat_[9] = column2.y_;
	mat_[10] = column2.z_;
	mat_[11] = column2.w_;
	mat_[12] = column3.x_;
	mat_[13] = column3.y_;
	mat_[14] = column3.z_;
	mat_[15] = column3.w_;
}

Matrix4::Matrix4(Matrix3 m)
{
	mat_[0] = m.mat_[0];
	mat_[1] = m.mat_[1];
	mat_[2] = m.mat_[2];
	mat_[3] = 0.0f;
	mat_[4] = m.mat_[3];
	mat_[5] = m.mat_[4];
	mat_[6] = m.mat_[5];
	mat_[7] = 0.0f;
	mat_[8] = m.mat_[6];
	mat_[9] = m.mat_[7];
	mat_[10] = m.mat_[8];
	mat_[11] = 0.0f;
	mat_[12] = 0.0f;
	mat_[13] = 0.0f;
	mat_[14] = 0.0f;
	mat_[15] = 1.0f;
}

Matrix4::~Matrix4() {}

Matrix4 operator+(Matrix4 a, Matrix4 b)
{
	Matrix4 result(0.0f);
	for (int i = 0; i < a.length(); i++)
		result.mat_[i] = a.mat_[i] + b.mat_[i];

	return result;
}

Matrix4 operator-(Matrix4 a, Matrix4 b)
{
	Matrix4 result(0.0f);
	for (int i = 0; i < a.length(); i++)
		result.mat_[i] = a.mat_[i] - b.mat_[i];

	return result;
}

Matrix4 operator*(Matrix4 m, float scalar)
{
	Matrix4 result(0.0f);
	for (int i = 0; i < m.length(); i++)
		result.mat_[i] = m.mat_[i] * scalar;

	return result;
}
Matrix4 operator*(float scalar, Matrix4 m)
{
	return m * scalar;
}
Matrix4 operator/(Matrix4 m, float scalar)
{
	return m * float(1 / scalar);
}

Matrix4 Translate(float tx, float ty, float tz)
{
	Matrix4 result = Matrix4(
		Vector4(1.0f, 0.0f, 0.0f, 0.0f),
		Vector4(0.0f, 1.0f, 0.0f, 0.0f),
		Vector4(0.0f, 0.0f, 1.0f, 0.0f),
		Vector4(tx, ty, tz, 1.0f));

	return result;
}

// axis angle rotation
Matrix3 Rotate(Vector3 axis, float angle)
{
	Matrix3 crossProductMatrix(0.0f);
	crossProductMatrix.mat_[0] = 0;
	crossProductMatrix.mat_[1] = axis.z_;
	crossProductMatrix.mat_[2] = -axis.y_;
	crossProductMatrix.mat_[3] = -axis.z_;
	crossProductMatrix.mat_[4] = 0;
	crossProductMatrix.mat_[5] = axis.x_;
	crossProductMatrix.mat_[6] = axis.y_;
	crossProductMatrix.mat_[7] = -axis.x_;
	crossProductMatrix.mat_[8] = 0;

	Matrix3 outerProductMatrix(0.0f);
	outerProductMatrix.mat_[0] = axis.x_ * axis.x_;
	outerProductMatrix.mat_[1] = axis.x_ * axis.y_;
	outerProductMatrix.mat_[2] = axis.x_ * axis.z_;
	outerProductMatrix.mat_[3] = axis.x_ * axis.y_;
	outerProductMatrix.mat_[4] = axis.y_ * axis.y_;
	outerProductMatrix.mat_[5] = axis.y_ * axis.z_;
	outerProductMatrix.mat_[6] = axis.x_ * axis.z_;
	outerProductMatrix.mat_[7] = axis.y_ * axis.z_;
	outerProductMatrix.mat_[8] = axis.z_ * axis.z_;

	Matrix3 identityMatrix;
	Matrix3 A = sin(ToRadians(angle)) * crossProductMatrix;
	Matrix3 B = (1 - cos(ToRadians(angle))) * outerProductMatrix;
	Matrix3 result = cos(ToRadians(angle)) * identityMatrix + B + A;

	return result;
}

Matrix4 Scale(float sx, float sy, float sz)
{
	Matrix4 result = Matrix4(
		Vector4(sx, 0.0f, 0.0f, 0.0f),
		Vector4(0.0f, sy, 0.0f, 0.0f),
		Vector4(0.0f, 0.0f, sz, 0.0f),
		Vector4(0.0f, 0.0f, 1.0f, 0.0f));

	return result;
}

float ToRadians(float degrees)
{
	return degrees * PI / 180;
}