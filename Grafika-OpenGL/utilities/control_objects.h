#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <glfw3.h>

#include "time.h"

class ControlObjects: private Time {
private:
	GLFWwindow *const& window;
	void SetTransformationValues();
	void ClearTransformationValues();
public:
	enum transformation_type { none_t, translation_t, scale_t, rotation_t };
	transformation_type transformation_t;
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotation;
	ControlObjects(	GLFWwindow *const& window_, glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::vec3 scale_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::vec3 rotation_ = glm::vec3( 0.0f, 0.0f, 0.0f));
protected:
	void ComputeTranslations();
	
};