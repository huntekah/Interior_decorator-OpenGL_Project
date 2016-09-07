#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include <glfw3.h>

#include "control_objects.h"
#include "control_camera.h"

class Controls: protected ControlObjects, protected ControlCamera{
public:
	Controls(GLFWwindow *const& window_);
	void ControlInput();
};