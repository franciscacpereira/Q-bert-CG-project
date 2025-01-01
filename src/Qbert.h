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
#include "materialTools.h"

#define PYRAMID_TO_QBERT_RATIO 0.6

enum class Orientation { RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP };

class Qbert {
public:

	Qbert(ofVec3f, GLfloat, GLfloat, GLfloat, GLfloat, int);
	void baseSetup();
	void resetPhysics();
	void draw();
	void update();
	void keyPressed(int);
	void startJump(ofVec3f);
	void resetLives();
	void pause();
	void resume();
	void activate();

	// position variables
	ofVec3f startPosition;
	ofVec3f currentPosition;
	ofVec3f previousPosition;

	// state variables
	GLfloat size;
	Orientation orientation;
	Orientation previousOrientation;
	bool isDead;
	bool isMoving;
	bool isFalling;
	bool pyramidCollision;
	bool ballCollision;
	int lives;
	bool isWaiting;

	// movement variables
	ofVec3f jumpStartPosition;
	ofVec3f targetPosition;

	GLfloat deathHeight;
	GLfloat jumpHeight;
	GLfloat jumpDistance;
	GLfloat jumpProgress;
	float timePerFrame;
	float previousTime;

	ofVec3f fallVelocity;
	ofVec3f fallAcceleration;
	GLfloat velocityMod;
	GLfloat fallAngle;

	// sound effects variables
	ofSoundPlayer jump;
	ofSoundPlayer fall;
	ofSoundPlayer ballCollisionSound;
};

#endif // QBERT_H
