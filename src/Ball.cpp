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

	// start deactivated so it can be activated on command
	this->isDead = true;
}

void Ball::baseSetup() {
	this->currentPosition = this->startPosition;
	this->orientation = Orientation::LEFT_DOWN;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	this->isWaiting = false;
	this->qbertCollision = false;
	resetPhysics();

	// set variables for initial fall
	this->initialFall = true;
	this->fallVelocity = ofVec3f(0, -0.05, 0);
	this->fallAcceleration = ofVec3f(0, -0.05, 0);
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
	//glPurple();
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

	// check if the ball is dead or paused
	if (this->isDead || this->isWaiting) {
		return;
	}

	// check if the ball fell to the ground
	if (this->currentPosition.y - this->size <= this->deathHeight) {
		this->isDead = true;
		return;
	}

	// check if the ball collided with the qbert
	if (this->qbertCollision) {
		this->isDead = true;
		//this->startPosition = ofVec3f(0, 0, 0);
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
				}
			}

			/* UPDATE POSITION */
			if (this->isFalling) {
				// free falling (will end up crashing with the ground)
				this->fallVelocity += this->fallAcceleration;
				this->currentPosition += this->fallVelocity;
			}
			else {
				// jumping
				this->jumpProgress += this->timePerFrame * 1.25;
				
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

void Ball::activate(ofVec3f position) {
	this->startPosition = position;
	baseSetup();
}

void Ball::pause() {
	this->isWaiting = true;
}

void Ball::resume() {
	this->isWaiting = false;
}