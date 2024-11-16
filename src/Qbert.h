// Qbert.h - Header file for the Qbert class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef QBERT_H
#define QBERT_H

#include <iostream>
#include "ofMain.h"
#include "extraTools.h"
#include "colorTools.h"
#include "movementTools.h"
#include "Pyramid.h"

class Qbert {
public:
	enum class Orientation { RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };

	Qbert(ofVec3f, GLfloat);
	Qbert(Pyramid*);
	void baseSetup();
	void resetPhysics();
	void draw();
	void update();
	void keyPressed(int);	


	// state variables
	ofVec3f startPosition;
	ofVec3f currentPosition;
	GLfloat qbertSize;
	bool isDead;
	bool isMoving;
	Orientation orientation;
	Pyramid* pyramid;

	// movement variables
	float mass;
	long long initialTime;
	long long elapsedTime;
	ofVec3f initialPosition;
	ofVec3f initialVelocity;
	ofVec3f velocity;
	float velocityMagnitude;
	float velocityAngle;
	ofVec3f acceleration;
};

#endif // QBERT_H
