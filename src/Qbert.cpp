// Qbert.cpp - Main file for the Qbert class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Qbert.h"

Qbert::Qbert(ofVec3f startPosition, GLfloat size) {
	this->pyramid = nullptr;
	this->startPosition = startPosition;
	this->qbertSize = size;
	baseSetup();
}

Qbert::Qbert(Pyramid* pyramid) {
	this->pyramid = pyramid;

	int tileSize = this->pyramid->tileSize;
	this->qbertSize = this->pyramid->tileSize * PYRAMID_TO_QBERT_RATIO;

	GLfloat x = this->pyramid->coords[0][0].x;
	GLfloat y = this->pyramid->coords[0][0].y + tileSize * 0.5 + this->qbertSize * 0.5;
	GLfloat z = this->pyramid->coords[0][0].z;

	this->startPosition = ofVec3f(x, y, z);
	baseSetup();
}

void Qbert::baseSetup() {
	this->currentPosition = this->startPosition;
	this->orientation = Orientation::LEFT_DOWN;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	resetPhysics();
}

void Qbert::resetPhysics() {
	this->jumpProgress = 0;
	this->timePerFrame = 0;
	this->previousTime = 0;
	this->jumpStartPosition = ofVec3f(0, 0, 0);
	this->targetPosition = ofVec3f(0, 0, 0);
}

void Qbert::draw() {
	GLfloat unit = 0.5;

	// draw the qbert player
	glPushMatrix(); {
		glOrange();

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

		glScaled(this->qbertSize, this->qbertSize, this->qbertSize);

		// nose stack
		glDarkOrange();
		glPushMatrix(); {
			glTranslatef(0, 0, unit * 1.5);
			glRotated(270, 1, 0, 0);
			drawCylinder(unit * 0.5, unit * 0.1, unit, 30);
		} glPopMatrix();

		// main sphere
		glOrange();
		unitSphere();
	} glPopMatrix();
}

void Qbert::update() {
	// calculate the time per frame
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;

	// check if the player is dead
	if (this->isDead) {
		baseSetup();
		return;
	}

	// check if the player fell into the ground
	if (this->currentPosition.y - this->qbertSize <= 0) {
		this->isDead = true;
		return;
	}

	// check if the player is moving
	if (isMoving) {

		this->jumpProgress += this->timePerFrame * 3;

		if (this->jumpProgress >= 1 && !isFalling) {
			this->currentPosition = this->targetPosition;
			if (checkPyramidCollision()) {
				this->jumpProgress = 1;
				this->isMoving = false;
				return;
			}
			else {
				this->jumpStartPosition = this->currentPosition;
				this->targetPosition.y = -100;
				this->isFalling = true;
				this->jumpProgress = 0;
			}
		}
		
		if (!isFalling) {
			// calculate the new position of the player (jumping)
			float jumpHeight = sin(this->jumpProgress * PI) * this->pyramid->tileSize;
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			newPosition.y += jumpHeight;
			this->currentPosition = newPosition;
		}
		else {
			// calculate the new position of the player (falling)
			this->jumpProgress += this->timePerFrame * 0.25;
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			this->currentPosition = newPosition;
		}
	} 
}

void Qbert::keyPressed(int key) {
	if (this->isDead || this->isMoving) return;

	if (key == OF_KEY_UP) {
		this->orientation = Orientation::RIGHT_UP;
		ofVec3f target = ofVec3f(this->currentPosition.x, this->currentPosition.y + this->pyramid->tileSize, this->currentPosition.z - this->pyramid->tileSize);
		startJump(target);

	} else if (key == OF_KEY_RIGHT) {
		this->orientation = Orientation::RIGHT_DOWN;
		ofVec3f target = ofVec3f(this->currentPosition.x + +this->pyramid->tileSize, this->currentPosition.y - this->pyramid->tileSize, this->currentPosition.z);
		startJump(target);

	} else if (key == OF_KEY_DOWN) {
		this->orientation = Orientation::LEFT_DOWN;
		ofVec3f target = ofVec3f(this->currentPosition.x, this->currentPosition.y - this->pyramid->tileSize, this->currentPosition.z + this->pyramid->tileSize);
		startJump(target);

	} else if (key == OF_KEY_LEFT) {
		this->orientation = Orientation::LEFT_UP;
		ofVec3f target = ofVec3f(this->currentPosition.x - +this->pyramid->tileSize, this->currentPosition.y + this->pyramid->tileSize, this->currentPosition.z);
		startJump(target);

	}
}

void Qbert::startJump(ofVec3f target) {
	if (isMoving) return;
	this->isMoving = true;
	this->jumpStartPosition = this->currentPosition;
	this->targetPosition = target;
	this->jumpProgress = 0;
}

bool Qbert::checkPyramidCollision() {
	int currentMaxLevel = this->pyramid->maxLevel;
	for (int row = 0; row < this->pyramid->maxLevel; row++, currentMaxLevel--) {
		for (int col = 0; col < currentMaxLevel; col++) {
			ofVec3f tile = this->pyramid->coords[row][col];
			if (this->currentPosition.distance(tile) <= this->qbertSize * 0.5 + this->pyramid->tileSize * 0.5) {
				// change the color of the tile
				this->pyramid->setTileColor(row, col, true);
				return true;
			}
		}
	}
	return false;
}