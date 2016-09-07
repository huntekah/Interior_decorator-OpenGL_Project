#pragma once

#include "control_objects.h"


ControlObjects::ControlObjects(GLFWwindow * const & window_, glm::vec3 translation_, glm::vec3 scale_, glm::vec3 rotation_):
	window(window_), translation(translation_), scale(scale_), rotation(rotation_)
{
	transformation_t = none_t;
	InitializeTime();
}

void ControlObjects::ComputeTranslations()
{
	SetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		transformation_t = translation_t;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		transformation_t = scale_t;
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		transformation_t = rotation_t;
	}
	SetTransformationValues();
}



void ControlObjects::SetTransformationValues()
{
	if (transformation_t == translation_t) {
		translation = glm::vec3();
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) translation += glm::vec3(0.1 * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) translation += glm::vec3(-0.1 * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) translation += glm::vec3(0.0, 0.1 * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) translation += glm::vec3(0.0, -0.1 * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) translation += glm::vec3( 0.0, 0.0, 0.1 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) translation += glm::vec3( 0.0, 0.0, -0.1 * deltaTime);
	}
	else if (transformation_t == scale_t) {
		scale = glm::vec3(1.0,1.0,1.0);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) scale *= glm::vec3(1.0 + (0.1 * deltaTime), 1.0, 1.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) scale *= glm::vec3(1.0 + (-0.1 * deltaTime), 1.0, 1.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) scale *= glm::vec3(1.0,1.0 + (0.1 * deltaTime), 1.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) scale *= glm::vec3(1.0,1.0 + (-0.1 * deltaTime), 1.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) scale *= glm::vec3(1.0, 1.0, 1.0 + (0.1 * deltaTime));
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) scale *= glm::vec3(1.0, 1.0, 1.0 + (-0.1 * deltaTime));
	}
	else if (transformation_t == rotation_t) {
		rotation = glm::vec3();
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotation += glm::vec3(0.2 * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotation += glm::vec3(-0.2 * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) rotation += glm::vec3(0.0, 0.2 * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotation += glm::vec3(0.0, -0.2 * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) rotation += glm::vec3(0.0, 0.0, 0.2 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) rotation += glm::vec3(0.0, 0.0, -0.2 * deltaTime);
	}

}

void ControlObjects::ClearTransformationValues()
{
}

