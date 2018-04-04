/*
FILE		:	HpTimer.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 2
DATE		:	March 23, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file controls the time and deltatime in the program.
REFERENCED	:	https://www.youtube.com/watch?v=jqT96a7fB7E
 */
#pragma once
#include <Windows.h>

class HPTimer {
private:
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequency;

public:
	HPTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;

		Reset();
	}

	void Reset() {
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}

	void Update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}

	float GetTimeTotal() {
		float d = (float)currentCallToUpdate - startTime;
		return d / frequency;
	}

	float GetDeltaTime() {
		float d = currentCallToUpdate - lastCallToUpdate;
		return d / frequency;
	}
};