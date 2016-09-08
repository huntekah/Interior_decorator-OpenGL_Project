#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <glfw3.h>

#include "time.h"

class ControlCamera: private virtual Time {
private:
	GLFWwindow *const& window;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;

	float FoV;

	float speed;
	float mouseSpeed;
	double xpos, ypos;
	int screen_width, screen_height;
public:
	ControlCamera(GLFWwindow *const& window_);
	void computeMatricesFromInputs();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};