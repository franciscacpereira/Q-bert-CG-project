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

#define PYRAMID_TO_QBERT_RATIO 0.6

class Qbert {
public:
	enum class Orientation { RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };

	Qbert(ofVec3f, GLfloat, GLfloat, GLfloat);
	//Qbert(Pyramid*);
	void baseSetup();
	void resetPhysics();
	void draw();
	void update();
	void keyPressed(int);	
	void startJump(ofVec3f);
	//bool checkPyramidCollision();


	// state variables
	ofVec3f startPosition;
	ofVec3f currentPosition;
	ofVec3f previousPosition;
	ofVec3f prevPrevPosition;
	GLfloat qbertSize;
	Orientation orientation;
	//Pyramid* pyramid;
	bool isDead;
	bool isMoving;
	bool isFalling;

	// movement variables
	GLfloat jumpHeight;
	GLfloat jumpDistance;
	GLfloat jumpProgress;
	float timePerFrame;
	float previousTime;
	ofVec3f jumpStartPosition;
	ofVec3f targetPosition;
	bool pyramidCollision;

	GLfloat velocityMod;
	ofVec3f fallVelocity;
	ofVec3f fallAcceleration;
	GLfloat prevCurThreshold = 5;

	int i;
	int j;
};

#endif // QBERT_H
