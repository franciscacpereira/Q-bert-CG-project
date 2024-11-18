// Ballcpp - Main file for the Ball class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Ball.h"

Ball::Ball(ofVec3f startPosition, GLfloat size, GLfloat jumpHeight, GLfloat jumpDistance, GLfloat deathHeight) {
	this->startPosition = startPosition;
	this->size = size;
	this->jumpHeight = jumpHeight;
	this->jumpDistance = jumpDistance;
	this->deathHeight = deathHeight;

	this->velocityMod = 15.;
	this->fallAngle = 13 * PI / 9; //25 * PI / 18;  // ideal: 163 * PI / 120;

	baseSetup();
}

void Ball::baseSetup() {
	this->currentPosition = this->startPosition;
	this->orientation = Orientation::LEFT_DOWN;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	resetPhysics();

	// set variables for initial fall
	this->initialFall = true;
	this->fallVelocity = ofVec3f(0, -0.5, 0);
	this->fallAcceleration = ofVec3f(0, -0.5, 0);
	this->targetPosition = this->currentPosition;
	this->currentPosition.y += -(this->deathHeight);
}

void Ball::resetPhysics() {
	this->pyramidCollision = false;
	this->jumpStartPosition = ofVec3f(0, 0, 0);
	this->targetPosition = ofVec3f(0, 0, 0);

	this->jumpProgress = 0;
	this->timePerFrame = 0;
	this->previousTime = 0;

	this->initialFall = false;
	this->fallVelocity = ofVec3f(0, 0, 0);
	this->fallAcceleration = ofVec3f(0, 0, 0);
}

void Ball::draw() {
	if (this->isDead) return;
	glPurple();
	glPushMatrix(); {
		glTranslatef(this->currentPosition.x, this->currentPosition.y, this->currentPosition.z);
		glScalef(this->size, this->size, this->size);
		unitSphere();
	} glPopMatrix();
}

void Ball::update() {
	// calculate the time per frame
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;

	// check if the ball is dead
	if (this->isDead) {
		baseSetup();
		return;
	}

	// check if the ball fell to the ground
	if (this->currentPosition.y - this->size <= this->deathHeight) {
		this->isDead = true;
		return;
	}

	// check if the ball is in the initial fall stage (falling into the start position)
	if (this->initialFall) {
		this->fallVelocity += this->fallAcceleration;
		this->currentPosition += this->fallVelocity;
		
		if ((this->currentPosition.y - this->targetPosition.y) <= 0) {
			this->initialFall = false;
			this->currentPosition = this->targetPosition;
			resetPhysics();
		}

	} else {

		// check if the ball is moving
		if (this->isMoving) {

			/* CHECK IF TARGET HAS BEEN REACHED */
			if (this->jumpProgress >= 1 && !isFalling) {
				// reached or surpassed the target position in the jump movement
				this->currentPosition = this->targetPosition;

				if (this->pyramidCollision) {
					// collided with the pyramid when jumping
					this->jumpProgress = 1;
					this->isMoving = false;
					this->pyramidCollision = false;
					return;
				}
				else {
					// did not collide with the pyramid, start free falling
					this->isFalling = true;
					this->jumpProgress = 0;

					this->fallVelocity.y = this->velocityMod * sin(this->fallAngle);

					if (this->orientation == Orientation::RIGHT_DOWN) {
						this->fallVelocity.x = -(this->velocityMod * cos(this->fallAngle));

					}
					else if (this->orientation == Orientation::LEFT_DOWN) {
						this->fallVelocity.z = -(this->velocityMod * cos(this->fallAngle));
					}

					/*
					this->jumpStartPosition = this->currentPosition;
					this->targetPosition.y = -100;
					this->isFalling = true;
					this->jumpProgress = 0;

					
					// set variables for free fall
					if (this->orientation == Orientation::LEFT_DOWN) {
						this->fallVelocity = ofVec3f(0, -0.5, 1);
						this->fallAcceleration = ofVec3f(0, -0.5, 0);
					}
					else if (this->orientation == Orientation::RIGHT_DOWN) {
						this->fallVelocity = ofVec3f(1, -0.5, 0);
						this->fallAcceleration = ofVec3f(0, -0.5, 0);
						this->targetPosition.x += jumpDistance * 2;
					}
					this->isFalling = true;
					this->jumpProgress = 0;
					*/
				}
			}

			/* UPDATE POSITION */
			if (this->isFalling) {
				// free falling (will end up crashing with the ground)
				this->fallVelocity += this->fallAcceleration;
				this->currentPosition += this->fallVelocity;

				/* this->jumpProgress += this->timePerFrame * 6;
				// calculate the new position of the player (falling)
				ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
				this->currentPosition = newPosition;

				this->fallVelocity += this->fallAcceleration;
				this->currentPosition += this->fallVelocity;

				cout << "BALL POSITION: " << this->currentPosition << endl;
				*/
			}
			else {
				// jumping
				this->jumpProgress += this->timePerFrame * 1.5;
				
				float height = sin(this->jumpProgress * PI) * this->jumpHeight;
				ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
				newPosition.y += height;

				this->currentPosition = newPosition;
			}
		}
		else {
			// choose random direction
			int direction = getRandomInt(0, 2);
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
}

void Ball::startJump(ofVec3f target) {
	if (isMoving) return;
	this->isMoving = true;
	this->jumpStartPosition = this->currentPosition;
	this->targetPosition = target;
	this->jumpProgress = 0;
}
