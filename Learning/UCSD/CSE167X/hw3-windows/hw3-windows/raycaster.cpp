#include <math.h>
#include "globals.h"
#include "raycaster.h"


Matrix3 LookAt(Camera cam)
{
	Vector3 up = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 center;
	Vector3 w = Normalize(cam.position_ - center);
	Vector3 u = Normalize(Cross(up, w));
	Vector3 v = Cross(w, u);

	return Matrix3(u, v, w);
}

Vector3 GenerateRay(Camera camera, int pixelX, int pixelY)
{
	// get the eye/camera coordinates
	Matrix3 cameraCoordinates = LookAt(camera);

	// get the pixel's x and y displacement along image plane
	float alpha = tan(FOVX / 2) * ((pixelX - WIDTH / 2) / (WIDTH / 2));
	float beta = tan(FOVY / 2) * ((HEIGHT / 2 - pixelY) / (HEIGHT / 2));

	Vector3 ray = camera.position_ + Normalize(cameraCoordinates.column(0) * alpha
		+ cameraCoordinates.column(1) * beta - cameraCoordinates.column(2));

	return ray;
}
