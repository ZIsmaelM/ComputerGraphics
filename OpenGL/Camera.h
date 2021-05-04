#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
class Camera
{
private:
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;
	float fov = 45.0f;

public:

	Camera()
	{

	}

	void moveHorizontal()
	{

	}

	void moveVertical()
	{

	}

	void zoom()
	{

	}

	void resetToStartPosition()
	{

	}
};
#endif