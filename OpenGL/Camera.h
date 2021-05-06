#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <iostream>
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
	const float moveSpeed = 2.5f;


public:

	Camera()
	{

	}

	void moveHorizontal(const float deltaTime)
	{
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed * deltaTime;
	}

	void moveVertical(const float deltaTime)
	{
		cameraPosition += cameraFront * moveSpeed * deltaTime;
	}

	void zoom()
	{

	}

	void resetToStartPosition()
	{
		cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = -90.0f;
		pitch = 0.0f;
		fov = 45.0f;
	}

	glm::mat4 getView()
	{
		glm::mat4 foo = glm::mat4(1.0f);
		foo = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		return foo;
	}
};
#endif