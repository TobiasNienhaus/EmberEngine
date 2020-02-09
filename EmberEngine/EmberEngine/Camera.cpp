#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float speed, float yaw, float pitch) :
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	pos(pos), worldUp(up), speed(speed), yaw(yaw), pitch(pitch), sensitivity(0.05f)
{
	updateVectors();
}

glm::mat4 Camera::View()
{
	return glm::lookAt(pos, pos + front, up);
}

void Camera::ProcessDirection(Cam_Movement dir, float deltaTime)
{
	float v = speed * deltaTime;
	switch (dir)
	{
	case Cam_Movement::FORWARD:
		pos += front * v;
		break;
	case Cam_Movement::BACKWARD:
		pos -= front * v;
		break;
	case Cam_Movement::LEFT:
		pos -= right * v;
		break;
	case Cam_Movement::RIGHT:
		pos += right * v;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouse(float xOff, float yOff, bool constrainPitch)
{
	xOff *= sensitivity;
	yOff *= sensitivity;

	yaw += xOff;
	pitch += yOff;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateVectors();
}

void Camera::updateVectors()
{
	glm::vec3 frontNew;
	frontNew.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontNew.y = sin(glm::radians(pitch));
	frontNew.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontNew);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}
