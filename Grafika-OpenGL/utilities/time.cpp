
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

unsigned int Time::SetMeasureTempo(double tempo_)
{
	tempo.emplace_back(tempo_,glfwGetTime());
	return tempo.size() - 1;
}

bool Time::MeasureTempo(unsigned int id)
{
	if ((glfwGetTime() - tempo[id].second) > tempo[id].first)	return true;
	return false;
}

void Time::ResetMeasureTempo(unsigned int id)
{
	tempo[id].second = glfwGetTime();
}

bool Time::Tempometer(unsigned int id)
{
	if ((glfwGetTime() - tempo[id].second) > tempo[id].first) {
		tempo[id].second = glfwGetTime();
		return true;
	}
	return false;
}
