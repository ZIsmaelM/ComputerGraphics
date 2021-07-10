#include "camera.h"

Camera::Camera()
	: position_{ 0.0, 0.0, 0.0 }, viewDirection_{ 0.0, 0.0, -1.0 }, up_{ 0.0, 1.0, 0.0 }, fovy_{ 45 }
{

}

Camera::Camera(Vector3 position, Vector3 viewDirection, Vector3 up, float fovy)
	: position_{ position }, viewDirection_{ viewDirection }, up_{ up }, fovy_{ fovy }
{
}

Camera::~Camera() {}
