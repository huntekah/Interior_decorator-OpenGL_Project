#pragma once

#include <vector>

class Time {
protected:
	double lastTime;
	double deltaTime;
	std::vector<std::pair<double,double>> tempo;
	void InitializeTime();
	double SetDeltaTime();
public:
	Time();
	unsigned int SetMeasureTempo(double tempo_);
	bool MeasureTempo( unsigned int id);
	void ResetMeasureTempo(unsigned int id);
	bool Tempometer(unsigned int id);
	double getDeltaTime();
};