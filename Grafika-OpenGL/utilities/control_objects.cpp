#pragma once

#include "control_objects.h"


ControlObjects::ControlObjects(GLFWwindow * const & window_, glm::vec3 translation_, glm::vec3 scale_, glm::quat rotation_):
	window(window_), translation(translation_), scale(scale_), rotation(rotation_)
{
	InitializeTime();
}

void ControlObjects::ComputeTranslations()
{
	SetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
	}
}



double ControlObjects::SetDeltaTime()
{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		return deltaTime;

}

void ControlObjects::InitializeTime()
{
	lastTime = glfwGetTime();
}
