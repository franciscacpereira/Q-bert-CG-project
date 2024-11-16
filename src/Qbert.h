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

#define JUMP_TIME 600	// ms

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
	void startJump(ofVec3f);
	bool checkPyramidCollision();


	// state variables
	ofVec3f startPosition;
	ofVec3f currentPosition;
	GLfloat qbertSize;
	Orientation orientation;
	Pyramid* pyramid;
	bool isDead;
	bool isMoving;
	bool isFalling;

	// movement variables
	float jumpProgress;
	float timePerFrame;
	float previousTime;
	ofVec3f jumpStartPosition;
	ofVec3f targetPosition;
};

#endif // QBERT_H
