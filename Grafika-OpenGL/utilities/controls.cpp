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
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (Controls::Time::MeasureTempo(keyRepeatTempoID)) {
			Action = save;
			Controls::Time::ResetMeasureTempo(keyRepeatTempoID);
		}
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
	keyRepeatTempoID = Controls::Time::SetMeasureTempo(0.4);
}

void Controls::ControlInput()
{
	if (Action == none) ActionNone();
	else if (Action == edit) {
		ActionEdit();
		ComputeTranslations();
	}
	else if (Action == save) Action = none;
	computeMatricesFromInputs();

	if (Action == edit) glClearColor(0.72f, 0.91f, 0.84f, 0.0f);
	else glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}
