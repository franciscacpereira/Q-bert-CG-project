// movementTools.h - Header file containing all movement auxiliary methods
// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef MOVEMENTTOOLS_H
#define MOVEMENTTOOLS_H

#include "ofMain.h"
#include "extraTools.h"

const float GRAVITY = 9.81f;  // acceleration due to gravity (m/s^2)

long long getTime();
float calculateVelocity(float, float, float);
float calculatePosition(float, float, float, float);
float calculateAcceleration(float, float);

#endif // MOVEMENTTOOLS_H
