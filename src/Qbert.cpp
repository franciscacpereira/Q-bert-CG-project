// Qbert.cpp - Main file for the Qbert class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Qbert.h"

Qbert::Qbert(ofVec3f startPosition, GLfloat size, GLfloat jumpHeight, GLfloat jumpDistance, GLfloat deathHeight, int lives) {
	this->startPosition = this->currentPosition = this->previousPosition = startPosition;
	this->orientation = this->previousOrientation = Orientation::LEFT_DOWN;
	this->size = size;
	this->jumpHeight = jumpHeight;
	this->jumpDistance = jumpDistance;
	this->deathHeight = deathHeight;
	this->lives = lives;

	this->velocityMod = 7.;			// ideal: 15. (but for the sound to be accurate it should be 7);
	this->fallAngle = 13 * PI / 9;	//25 * PI / 18;  // ideal: 163 * PI / 120;

	baseSetup();
}

void Qbert::baseSetup() {
	this->currentPosition = this->previousPosition;
	this->orientation = this->previousOrientation;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	this->ballCollision = false;
	this->isWaiting = true;
	resetPhysics();
	this->jump.load("jump.mp3");
	this->fall.load("fall.mp3");
	this->ballCollisionSound.load("ballCollision.mp3");
}

void Qbert::resetPhysics() {
	// set variables for jump
	this->pyramidCollision = false;
	this->jumpStartPosition = ofVec3f(0, 0, 0);
	this->targetPosition = this->currentPosition; //ofVec3f(0, 0, 0);

	this->jumpProgress = 0;
	this->timePerFrame = 0;
	this->previousTime = 0;

	// set variables for fall
	this->fallVelocity = ofVec3f(0, 0, 0);
	this->fallAcceleration = ofVec3f(0, 0, 0);
}

void Qbert::draw() {
	if (this->isDead) return;
	GLfloat unit = 0.5;

	// draw the qbert player
	glPushMatrix(); {

		glTranslatef(this->currentPosition.x, this->currentPosition.y, this->currentPosition.z);
		
		if (this->orientation == Orientation::RIGHT_UP) {
			glRotated(180, 0, 1, 0);
		}
		else if (this->orientation == Orientation::RIGHT_DOWN) {
			glRotated(90, 0, 1, 0);
		}
		else if (this->orientation == Orientation::LEFT_UP) {
			glRotated(-90, 0, 1, 0);
		}
		else if (this->orientation == Orientation::LEFT_DOWN) {
			// it is alreadey drawn in the right orientation
		}

		glScaled(this->size, this->size, this->size);

		// nose stack
		setMaterial(ORANGE_RUBBER);
		glPushMatrix(); {
			glTranslatef(0, 0, unit * 1.5);
			glRotated(270, 1, 0, 0);
			drawCylinder(unit * 0.5, unit * 0.1, unit, 30);
		} glPopMatrix();

		// main sphere
		setMaterial(ORANGE_RUBBER);
		unitSphere();
	} glPopMatrix();
}

void Qbert::update() {
	// calculate the time per frame
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;

	// pause the game
	if (this->isWaiting) {
		return;
	}

	// check if the player is dead
	if (this->isDead && this->lives > 0) {
		return;
	}

	// check if the player fell into the ground
	if (this->currentPosition.y - this->size <= this->deathHeight) {
		this->isDead = true;
		this->lives--;
		this->previousPosition = this->startPosition;	// so it spawns from the start position
		this->previousOrientation = Orientation::LEFT_DOWN;
		return;
	}

	// check if the player collision with ball
	if (this->ballCollision) {
		this->isDead = true;
		this->previousOrientation = this->orientation;
		this->lives--;
		this->ballCollisionSound.play();
	}


	// check if the player is moving
	if (this->isMoving) {

		/* CHECK IF TARGET HAS BEEN REACHED */
		if (this->jumpProgress >= 1 && !isFalling) {
			// reached or surpassed the target position in the jump movement
			this->currentPosition = this->targetPosition;
			this->previousPosition = this->currentPosition;

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

				if (this->orientation == Orientation::LEFT_UP) {
					this->fallVelocity.x = this->velocityMod * cos(this->fallAngle);

				} else if (this->orientation == Orientation::RIGHT_DOWN) {
					this->fallVelocity.x = - (this->velocityMod * cos(this->fallAngle));

				} else if (this->orientation == Orientation::RIGHT_UP) {
					this->fallVelocity.z = this->velocityMod * cos(this->fallAngle);

				} else if (this->orientation == Orientation::LEFT_DOWN) {
					this->fallVelocity.z = - (this->velocityMod * cos(this->fallAngle));
				}

				this->fall.play();
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
			this->jumpProgress += this->timePerFrame * 3;

			float height = sin(this->jumpProgress * PI) * this->jumpHeight;
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			newPosition.y += height;

			this->currentPosition = newPosition;
		}
	} 
}

void Qbert::keyPressed(int key) {
	if (this->isDead || this->isMoving) return;

	if (key == OF_KEY_UP) {
		this->orientation = Orientation::RIGHT_UP;
		ofVec3f target = ofVec3f(this->currentPosition.x, this->currentPosition.y + this->jumpHeight, this->currentPosition.z - this->jumpDistance);
		startJump(target);

	} else if (key == OF_KEY_RIGHT) {
		this->orientation = Orientation::RIGHT_DOWN;
		ofVec3f target = ofVec3f(this->currentPosition.x + this->jumpDistance, this->currentPosition.y - this->jumpHeight, this->currentPosition.z);
		startJump(target);

	} else if (key == OF_KEY_DOWN) {
		this->orientation = Orientation::LEFT_DOWN;
		ofVec3f target = ofVec3f(this->currentPosition.x, this->currentPosition.y - this->jumpHeight, this->currentPosition.z + this->jumpDistance);
		startJump(target);

	} else if (key == OF_KEY_LEFT) {
		this->orientation = Orientation::LEFT_UP;
		ofVec3f target = ofVec3f(this->currentPosition.x - this->jumpDistance, this->currentPosition.y + this->jumpHeight, this->currentPosition.z);
		startJump(target);

	}
}

void Qbert::startJump(ofVec3f target) {
	if (isMoving) return;
	this->jump.play();
	this->isMoving = true;
	this->isWaiting = false;
	this->jumpStartPosition = this->currentPosition;
	this->previousPosition = this->currentPosition;
	this->targetPosition = target;
	this->jumpProgress = 0;
}

void Qbert::resetLives() {
	this->lives = 3;
}

void Qbert::pause() {
	this->isWaiting = true;
}

void Qbert::resume() {
	this->isWaiting = false;
}

void Qbert::activate() {
	baseSetup();
}