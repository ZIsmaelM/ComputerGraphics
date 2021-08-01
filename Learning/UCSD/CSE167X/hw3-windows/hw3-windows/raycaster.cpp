#include <math.h>
#include "globals.h"
#include "raycaster.h"

Ray::Ray()
	: origin_{ Vector3() }, direction_{ Vector3() }
{}

Ray::Ray(Vector3 origin, Vector3 direction)
	: origin_{ origin }, direction_{ direction }
{}

Ray::~Ray() {}

Matrix3 LookAt(Camera cam, Vector3 point)
{
	Vector3 up = Vector3(0.0f, 0.0f, 1.0f);
	//Vector3 center;
	Vector3 w = Normalize(cam.position_ - point);
	Vector3 u = Normalize(Cross(up, w));
	Vector3 v = Cross(w, u);

	return Matrix3(u, v, w);
}

Ray GenerateRay(Camera camera, int pixelX, int pixelY)
{
	// get the eye/camera coordinates
	Vector3 point = Vector3(pixelX + 0.5f, pixelY + 0.5f, -1.0f);
	Matrix3 cameraCoordinates = LookAt(camera, point);

	// get the pixel's x and y displacement along image plane
	float alpha = tan(FOVX / 2) * ((pixelX - WIDTH / 2) / (WIDTH / 2));
	float beta = tan(FOVY / 2) * ((HEIGHT / 2 - pixelY) / (HEIGHT / 2));

	Vector3 rayDirection = camera.position_ + Normalize(cameraCoordinates.column(0) * alpha
		+ cameraCoordinates.column(1) * beta - cameraCoordinates.column(2));
	
	return Ray(camera.position_, Normalize(rayDirection));
}
