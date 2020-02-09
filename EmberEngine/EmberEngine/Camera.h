#pragma once
#include "OpenGLLibraries.h"
#include <iostream>

enum class Cam_Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float speed;
	float sensitivity;

	Camera(const Camera &c);
	Camera(Camera&& c);

	void updateVectors();

public:
	Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float speed = 2.5f, float yaw = -90.0f, float pitch = 0.0f);

	glm::mat4 View();
	glm::vec3 Position() { return glm::vec3(pos); }

	void ProcessDirection(Cam_Movement dir, float deltaTime);
	void ProcessMouse(float xOff, float yOff, bool constrainPitch = true);
};

