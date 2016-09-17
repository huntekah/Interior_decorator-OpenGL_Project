#pragma once

#include "control_camera.h"
#include <glm/gtc/matrix_transform.hpp>

ControlCamera::ControlCamera(GLFWwindow * const & window_):window(window_)
{
	// Initial position : on +Z
	position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// Initial vertical angle : none
	verticalAngle = 0.0f;
	// Initial Field of View
	FoV = 45.0f;

	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.005f;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwGetWindowSize(window, &screen_width, &screen_height);
}

void ControlCamera::computeMatricesFromInputs()
{

	glfwGetCursorPos(window, &xpos, &ypos);
	///glfwGetWindowSize(window, &screen_width, &screen_height); /// ?TO MAINTAIN SPEED OF CODE;
	
	// Reset mouse position for next frame
	glfwSetCursorPos(window, screen_width / 2, screen_height / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(screen_width / 2 - xpos);
	verticalAngle += mouseSpeed * float(screen_height / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * (float)deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * (float)deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * (float)deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * (float)deltaTime * speed;
	}

	///change FoV with a mouse HERE (or with a keys)
	/// float FoV = initialFoV;// -5 * glfwGetMouseWheel();

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

glm::mat4 ControlCamera::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 ControlCamera::getProjectionMatrix()
{
	return ProjectionMatrix;
}