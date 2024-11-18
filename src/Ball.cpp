// Ballcpp - Main file for the Ball class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Ball.h"

Ball::Ball(ofVec3f startPosition, GLfloat size, GLfloat jumpHeight, GLfloat jumpDistance) {
	this->startPosition = startPosition;
	this->ballSize = size;
	this->jumpHeight = jumpHeight;
	this->jumpDistance = jumpDistance;
	baseSetup();
	
	/*
	this->targetPosition = this->startPosition;
	this->currentPosition = this->startPosition;
	this->currentPosition.y = this->currentPosition.y + 500;
	this->jumpStartPosition = this->currentPosition;
	this->isMoving = true;
	this->isFalling = true;
	cout << "BALL POSITION: " << this->currentPosition << endl;
	cout << "BALL TARGET POSITION: " << this->targetPosition << endl;
	*/
}

void Ball::baseSetup() {
	this->currentPosition = this->startPosition;
	this->orientation = Orientation::LEFT_DOWN;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	resetPhysics();
}

void Ball::resetPhysics() {
	this->jumpProgress = 0;
	this->timePerFrame = 0;
	this->previousTime = 0;
	this->jumpStartPosition = ofVec3f(0, 0, 0);
	this->targetPosition = ofVec3f(0, 0, 0);
	this->pyramidCollision = false;
}

void Ball::draw() {
	if (!isDead) {
		glPurple();
		glPushMatrix(); {
			glTranslatef(this->currentPosition.x, this->currentPosition.y, this->currentPosition.z);
			glScalef(this->ballSize, this->ballSize, this->ballSize);
			unitSphere();
		} glPopMatrix();
	}
}

void Ball::update() {
	// check if the player is dead
	if (this->isDead) {
		baseSetup();
		return;
	}

	// calculate the time per frame
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;

	// check if the player fell into the ground
	if (this->currentPosition.y - this->ballSize <= 0) {
		this->isDead = true;
		cout << "BALL DIED" << endl;
		return;
	}

	// check if the player is moving
	if (isMoving) {

		if (this->jumpProgress >= 1 && !isFalling) {
			this->currentPosition = this->targetPosition;
			if (this->pyramidCollision) {
				this->jumpProgress = 1;
				this->isMoving = false;
				this->pyramidCollision = false;
				return;
			}
			else {
				this->jumpStartPosition = this->currentPosition;
				this->targetPosition.y = -100;
				this->isFalling = true;
				this->jumpProgress = 0;
			}
		}

		this->jumpProgress += this->timePerFrame * 1.5;

		if (!isFalling) {
			// calculate the new position of the player (jumping)
			float height = sin(this->jumpProgress * PI) * this->jumpHeight;
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			newPosition.y += height;
			this->currentPosition = newPosition;
			cout << "BALL POSITION (not falling): " << this->currentPosition << endl;
		}
		else {
			// calculate the new position of the player (falling)
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			this->currentPosition = newPosition;
			cout << "BALL POSITION: " << this->currentPosition << endl;
		}
	}
	else {
		// choose random direction
		int direction = ofRandom(0, 2);
		if (direction == 0) {
			this->orientation = Orientation::LEFT_DOWN;
			ofVec3f target = ofVec3f(this->currentPosition.x, this->currentPosition.y - this->jumpHeight, this->currentPosition.z + this->jumpDistance);
			startJump(target);
		}
		else {
			this->orientation = Orientation::RIGHT_DOWN;
			ofVec3f target = ofVec3f(this->currentPosition.x + this->jumpDistance, this->currentPosition.y - this->jumpHeight, this->currentPosition.z);
			startJump(target);
		}
	}
}

void Ball::startJump(ofVec3f target) {
	if (isMoving) return;
	this->isMoving = true;
	this->jumpStartPosition = this->currentPosition;
	this->targetPosition = target;
	this->jumpProgress = 0;
}
