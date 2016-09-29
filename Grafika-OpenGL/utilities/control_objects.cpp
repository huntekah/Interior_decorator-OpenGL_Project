#pragma once

#include "control_objects.h"
#include <iostream>


ControlObjects::ControlObjects(GLFWwindow * const & window_,  glm::vec3 translation_, glm::vec3 scale_, glm::vec3 rotation_):
	window(window_), translation(translation_), scale(scale_), rotation(rotation_)
{
	transformation_t = none_t;
	ObjectID = 0;
	transformationSpeed = 10.0;
	keyRepeatTempoID = SetMeasureTempo(0.3);
	increasedID = true;
}

void ControlObjects::ComputeTranslations()
{
	ControlSpeed();
	ChangeObject();
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
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) translation += glm::vec3(transformationSpeed * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) translation += glm::vec3(-transformationSpeed * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) translation += glm::vec3(0.0, transformationSpeed * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) translation += glm::vec3(0.0, -transformationSpeed * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) translation += glm::vec3( 0.0, 0.0, transformationSpeed * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) translation += glm::vec3( 0.0, 0.0, -transformationSpeed * deltaTime);
	}
	else if (transformation_t == scale_t) {
		scale = glm::vec3(1.0,1.0,1.0);
		transformationSpeed /= 40;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) scale *= glm::vec3(1.0 + (transformationSpeed * deltaTime), 1.0, 1.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) scale *= glm::vec3(1.0 + (-transformationSpeed * deltaTime), 1.0, 1.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) scale *= glm::vec3(1.0,1.0 + (transformationSpeed * deltaTime), 1.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) scale *= glm::vec3(1.0,1.0 + (-transformationSpeed * deltaTime), 1.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) scale *= glm::vec3(1.0, 1.0, 1.0 + (transformationSpeed * deltaTime));
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) scale *= glm::vec3(1.0, 1.0, 1.0 + (-transformationSpeed * deltaTime));
		transformationSpeed *= 40;
	}
	else if (transformation_t == rotation_t) {
		rotation = glm::vec3();
		transformationSpeed /= 20;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotation += glm::vec3(transformationSpeed * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotation += glm::vec3(-transformationSpeed * deltaTime, 0.0, 0.0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) rotation += glm::vec3(0.0, transformationSpeed * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotation += glm::vec3(0.0, -transformationSpeed * deltaTime, 0.0);
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) rotation += glm::vec3(0.0, 0.0, transformationSpeed * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) rotation += glm::vec3(0.0, 0.0, -transformationSpeed * deltaTime);
		transformationSpeed *= 20;
	}

}


void ControlObjects::ControlSpeed()
{
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) { //  PLUS
		transformationSpeed *= 1.005;
		std::cout << transformationSpeed << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) { //  MINUS
		transformationSpeed *= 0.995;
		if (transformationSpeed == 0) transformationSpeed = 0.000000001;
		std::cout << transformationSpeed << std::endl;
	}
}

void ControlObjects::ChangeObject()
{
	if (MeasureTempo(keyRepeatTempoID)) {
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			ObjectID = (ObjectID + 1) % ObjectAmount;
			increasedID = true; // in order to handle const's
			ResetMeasureTempo(keyRepeatTempoID);
			std::cout << ObjectID << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			ObjectID = (ObjectAmount + ObjectID - 1) % ObjectAmount;
			increasedID = false; // in order to handle const's
			ResetMeasureTempo(keyRepeatTempoID);
			std::cout << ObjectID << std::endl;
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS); // cleans the buffer
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS);
	}
}

void ControlObjects::SetObjectAmout(unsigned int ObjectAmount_)
{
	ObjectAmount = ObjectAmount_;
	if (ObjectAmount == 0) ObjectAmount++;
}

unsigned int ControlObjects::GetObjectID()
{
	return ObjectID;
}

void ControlObjects::NextObject()
{
	if (increasedID == true) {
		ObjectID = (ObjectID + 1) % ObjectAmount;
		std::cout << ObjectID << std::endl;
	}
	else {
		ObjectID = (ObjectAmount + ObjectID - 1) % ObjectAmount;
		std::cout << ObjectID << std::endl;
	}
}

