#pragma once

#include "controls.h"

void Controls::ActionNone()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (Controls::Time::MeasureTempo(keyRepeatTempoID)) {
			Action = escape;
			Controls::Time::ResetMeasureTempo(keyRepeatTempoID);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			Action = edit;
	}
}

void Controls::ActionEdit()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (Controls::Time::MeasureTempo(keyRepeatTempoID)) {
			Action = none;
			Controls::Time::ResetMeasureTempo(keyRepeatTempoID);
		}
	}
}

Controls::Controls(GLFWwindow * const & window_) : 
	window(window_), ControlCamera(window_), ControlObjects(window_)
{
	Action = none;
	keyRepeatTempoID = Controls::Time::SetMeasureTempo(3.4);
	//glfwPollEvents();
}

void Controls::ControlInput()
{
	if (Action == none) ActionNone();
	else if (Action == edit) {
		ActionEdit();
		ComputeTranslations();
	}
	computeMatricesFromInputs();
}
