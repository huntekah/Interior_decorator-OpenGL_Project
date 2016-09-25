#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <glfw3.h>

#include "time.h"

class ControlObjects: private virtual Time {
private:
	bool increasedID;
	GLFWwindow *const& window;
	void SetTransformationValues();
	unsigned int ObjectID;
	unsigned int ObjectAmount;
	double transformationSpeed;
	void ControlSpeed();
	void ChangeObject();
	unsigned int keyRepeatTempoID;
public:
	void SetObjectAmout(unsigned int ObjectAmount_);
	unsigned int GetObjectID();
	void NextObject();
	enum transformation_type { none_t, translation_t, scale_t, rotation_t };
	transformation_type transformation_t;
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotation;
	ControlObjects(	GLFWwindow *const& window_,  glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::vec3 scale_ = glm::vec3(0.0f, 0.0f, 0.0f), 
					glm::vec3 rotation_ = glm::vec3( 0.0f, 0.0f, 0.0f));
protected:
	void ComputeTranslations();
	
};