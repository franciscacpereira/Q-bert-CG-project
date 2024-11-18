// Ball.h - Header file for the Ball class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef BALL_H
#define BALL_H

#include "ofMain.h"
#include "extraTools.h"
#include "colorTools.h"
#include "movementTools.h"

class Ball {
public:
	enum class Orientation { RIGHT_DOWN, LEFT_DOWN };

	Ball(ofVec3f startPosition, GLfloat size, GLfloat jumpHeight, GLfloat jumpDistance);
	void baseSetup();
	void resetPhysics();
	void draw();
	void update();
	void startJump(ofVec3f);

	// state variables
	ofVec3f startPosition;
	ofVec3f currentPosition;
	GLfloat ballSize;
	Orientation orientation;
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
};

#endif // BALL_H

