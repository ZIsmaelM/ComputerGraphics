#include <math.h>
#include <iostream>
#include "globals.h"
#include "raycaster.h"

Ray::Ray()
	: origin_{ Vector3() }, direction_{ Vector3() }
{}

Ray::Ray(Vector3 origin, Vector3 direction)
	: origin_{ origin }, direction_{ direction }
{}

Ray::~Ray() {}

Matrix4 LookAt(Vector3 eyePos, Vector3 point)
{
	Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f);
	//Vector3 center;
	Vector3 camForward = Normalize(eyePos - point);
	Vector3 camRight = Normalize(Cross(worldUp, camForward));
	Vector3 camUp = Cross(camForward, camRight);

	Matrix3 camToWorld = Matrix3(camRight, camUp, camForward);

	return Matrix4(camToWorld);
}

int gar = 0;
Ray GenerateRay(Vector3 eyePos, int pixelX, int pixelY)
{
	Matrix4 CameraToWorld = LookAt(Vector3(), eyePos);
	eyePos = MultVecMat(eyePos, CameraToWorld);

	// convert to NDC space
	float pixelNDCX = (pixelX + 0.5f) / (float)WIDTH;
	float pixelNDCY = (pixelY + 0.5f) / (float)HEIGHT;

	// convert to Screen space. TL: -1,1 TR: 1,1
	float pixelScreenX = (2 * pixelNDCX) - 1;
	float pixelScreenY = 1 - (2 * pixelNDCY);// -1;

	// convert to Camera space
	float pixelCameraX = pixelScreenX * tan(ToRadians(FOVY * 0.5f)) * ASPECTRATIO;
	float pixelCameraY = pixelScreenY * tan(ToRadians(FOVY * 0.5f));

	Vector3 direction = Vector3(pixelCameraX, pixelCameraY, -1.0f) - eyePos;
	CameraToWorld = LookAt(eyePos, direction);
	direction = MultVecMat(direction, CameraToWorld);
	Normalize(direction);

	return Ray(eyePos, direction);
}
