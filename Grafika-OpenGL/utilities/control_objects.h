#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <glfw3.h>



class ControlObjects {
private:
	double lastTime;
	double deltaTime;
	void InitializeTime();
	double SetDeltaTime();
	GLFWwindow *const& window;
public:
	glm::vec3 translation;
	glm::vec3 scale;
	glm::quat rotation;
	ControlObjects(	GLFWwindow *const& window_, glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::vec3 scale_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
protected:
	void ComputeTranslations();
	
};