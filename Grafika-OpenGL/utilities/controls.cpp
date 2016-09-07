#pragma once

#include "controls.h"

Controls::Controls(GLFWwindow * const & window_) : ControlCamera(window_), ControlObjects(window_)
{
}

void Controls::ControlInput()
{
	computeMatricesFromInputs();
	ComputeTranslations();
}
