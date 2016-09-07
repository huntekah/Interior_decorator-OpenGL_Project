#pragma once


class Time {
protected:
	double lastTime;
	double deltaTime;
	void InitializeTime();
	double SetDeltaTime();
public:
	Time();

};