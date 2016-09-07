
#pragma once

#include <glfw3.h>

#include "time.h"

void Time::InitializeTime()
{
	lastTime = glfwGetTime();
}

double Time::SetDeltaTime()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	return deltaTime;
}

Time::Time()
{
	InitializeTime();
}
