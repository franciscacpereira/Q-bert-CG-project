// movementTools.cpp - Main file containing all movement auxiliary methods
// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "movementTools.h"

// function to get the current time in milliseconds
long long getTime() {
	using namespace std::chrono;
	return duration<float, std::milli>(steady_clock::now().time_since_epoch()).count();
}

// function to get the current velocity of an object in a given axis
// applies the equation of motion: v = v0 + at
float calculateVelocity(float v0, float a, float t) {
	return v0 + a * t;
}

// function to get the current position of an object in a given axis
// applies the equation of motion: x = x0 + v0t + 0.5at^2
float calculatePosition(float x0, float v0, float a, float t) {
	return x0 + v0 * t + 0.5 * a * t * t;
}

// function to get the current acceleration of an object in a given axis
// applies the second Newton's law: F = ma => a = F/m
float calculateAcceleration(float F, float m) {
	return F / m;
} 