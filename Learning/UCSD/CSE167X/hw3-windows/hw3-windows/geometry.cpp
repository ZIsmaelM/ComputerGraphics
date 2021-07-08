#include <iostream>
#include <math.h>
#include "geometry.h"

Vector3::Vector3()
	: x_{ 0.0f }, y_{ 0.0f }, z_{ 0.0f }
{
}
Vector3::Vector3(float x, float y, float z)
	: x_{ x }, y_{ y }, z_{ z }
{
}
Vector3::~Vector3()
{}

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
	result.x_ = this->x_ - v.x_;
	result.y_ = this->y_ - v.y_;
	result.z_ = this->z_ - v.z_;

	return result;
}

Vector3 Vector3::operator*(float scalar)
{
	Vector3 result;
	result.x_ = this->x_ * scalar;
	result.y_ = this->y_ * scalar;
	result.z_ = this->z_ * scalar;

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
	result.x_ = this->x_ / scalar;
	result.y_ = this->y_ / scalar;
	result.z_ = this->z_ / scalar;

	return result;
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
	return m*scalar;
}

Matrix4::Matrix4()
	: mat_{1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f
	,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f}
{}

Matrix4::Matrix4(float f)
	: mat_{f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f}
{}

Matrix4::Matrix4(Vector4 column0 , Vector4 column1, Vector4 column2, Vector4 column3)
	: mat_{0.0f}
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

void Matrix4::Translate(float tx, float ty, float tz)
{
}

void Matrix4::Rotate(Vector3 axis, float angle)
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
	result = Normalize(result);

	return result;
}

void Matrix4::Scale(float, float, float)
{
}