#pragma once

class Vector3
{
public:
	float x_;
	float y_;
	float z_;

	Vector3();
	Vector3(float, float, float);
	~Vector3();

	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	Vector3 operator*(float); //TODO move outside of class and make symmetric
	Vector3 operator/(float);
};

class Vector4
{
public:
	float x_;
	float y_;
	float z_;
	float w_;

	Vector4();
	Vector4(float, float, float, float);
	~Vector4();

	Vector4 operator+(Vector4);
	Vector4 operator-(Vector4);
	Vector4 operator*(float);
	Vector4 operator/(float);
};

Vector3 Normalize(Vector3);
Vector4 Normalize(Vector4);
Vector3 Cross(Vector3, Vector3);

// Note: Matrices use column major order
class Matrix3
{
public:
	float mat_[9]; // TODO: mat[3][3] instead maybe? would that be [col][row] or the opposite in memory?

	Matrix3();
	Matrix3(float);
	Matrix3(Vector3, Vector3, Vector3);
	// TODO: add additional constructors
	~Matrix3();

	Vector3 row(int);
	Vector3 column(int);
	int length() { return 9; }
};

Matrix3 operator+(Matrix3, Matrix3);
Matrix3 operator-(Matrix3, Matrix3);
Matrix3 operator*(Matrix3, float);
Matrix3 operator*(float, Matrix3);
Matrix3 operator/(Matrix3, float);

class Matrix4
{
public:
	float mat_[16]; // TODO: mat[4][4] instead maybe? would that be [col][row] or the opposite in memory?

	Matrix4();
	Matrix4(float);
	Matrix4(Vector4, Vector4, Vector4, Vector4);
	Matrix4(Matrix3);
	// TODO: add additional constructors
	~Matrix4();

	int length() { return 16; }
};

Matrix4 Translate(float, float, float);
Matrix3 Rotate(Vector3, float);
Matrix4 Scale(float, float, float);

float ToRadians(float);