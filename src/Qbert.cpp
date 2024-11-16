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
	this->qbertSize = this->pyramid->tileSize * 0.6;

	GLfloat x = this->pyramid->coords[0][0].x;
	GLfloat y = this->pyramid->coords[0][0].y + tileSize - (this->qbertSize / 2);
	GLfloat z = this->pyramid->coords[0][0].z;

	this->startPosition = ofVec3f(x, y, z);
	baseSetup();
}

void Qbert::baseSetup() {
	this->currentPosition = this->startPosition;
	this->isDead = false;
	this->isMoving = false;
	this->orientation = Orientation::LEFT_DOWN;
	resetPhysics();
}

void Qbert::resetPhysics() {
	this->initialTime = 0;
	this->elapsedTime = 0;
	this->initialPosition = ofVec3f(0, 0, 0);
	this->initialVelocity = ofVec3f(0, 0, 0);
	this->velocity = ofVec3f(0, 0, 0);
	this->velocityMagnitude = 0;
	this->velocityAngle = 0;
	this->acceleration = ofVec3f(0, 0, 0);
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
		this->elapsedTime = getTime() - this->initialTime;
		
		// calculate the position
		this->currentPosition.x = calculatePosition(this->initialPosition.x, this->initialVelocity.x, 0, this->elapsedTime);
		this->currentPosition.y = calculatePosition(this->initialPosition.y, this->initialVelocity.y, this->acceleration.y, this->elapsedTime);
		this->currentPosition.z = calculatePosition(this->initialPosition.z, this->initialVelocity.z, 0, this->elapsedTime);

		// calculate the velocity
		this->velocity.x = calculateVelocity(this->initialVelocity.x, 0, this->elapsedTime);
		this->velocity.y = calculateVelocity(this->initialVelocity.y, this->acceleration.y, this->elapsedTime);
		this->velocity.z = calculateVelocity(this->initialVelocity.z, 0, this->elapsedTime);


		cout << "Current Position: " << this->currentPosition << endl;

		// check collision with any tile
		int currentMaxLevel = this->pyramid->maxLevel;
		for (int row = 0; row < this->pyramid->maxLevel; row++, currentMaxLevel--) {
			for (int column = 0; column < currentMaxLevel; column++) {
				GLfloat expectedX = this->pyramid->coords[row][column].x;
				GLfloat expectedY = this->pyramid->coords[row][column].y + (this->pyramid->tileSize / 2) + (this->qbertSize / 2);
				GLfloat expectedZ = this->pyramid->coords[row][column].z;

				ofVec3f expectedPosition = ofVec3f(expectedX, expectedY, expectedZ);
				if (this->currentPosition.x == expectedPosition.x && this->currentPosition.z == expectedPosition.z && this->currentPosition.y <= expectedPosition.y) {
					this->isMoving = false;
					resetPhysics();
					return;
				}
			}
		}
	} 
}

void Qbert::keyPressed(int key) {
	if (this->isDead || this->isMoving) return;

	if (key == OF_KEY_UP) {
		this->orientation = Orientation::RIGHT_UP;
		isMoving = true;
		this->initialTime = getTime();
		this->elapsedTime = 0;
		this->initialPosition = this->currentPosition;

	} else if (key == OF_KEY_RIGHT) {
		this->orientation = Orientation::RIGHT_DOWN;
		isMoving = true;
		this->initialTime = getTime();
		this->elapsedTime = 0;
		this->initialPosition = this->currentPosition;

	} else if (key == OF_KEY_DOWN) {
		this->orientation = Orientation::LEFT_DOWN;
		isMoving = true;
		this->initialTime = getTime();
		this->elapsedTime = 0;
		this->initialPosition = this->currentPosition;

		// x axis stays the same
		this->initialVelocity = ofVec3f(0, 0, 0);
		this->acceleration.x = 0;

		// set the initial velocity and acceleration
		this->velocityAngle = 70;
		this->acceleration.y = -0.01;

		float temp = 0.5 * -0.001 * pow(600, 2);
		this->initialVelocity.y = (temp - this->pyramid->tileSize) / 600;
		this->velocityMagnitude = this->initialVelocity.y / sin(this->velocityAngle);
		this->initialVelocity.z =  -this->velocityMagnitude * cos(this->velocityAngle);

	} else if (key == OF_KEY_LEFT) {
		this->orientation = Orientation::LEFT_UP;
		isMoving = true;
		this->initialTime = getTime();
		this->elapsedTime = 0;
		this->initialPosition = this->currentPosition;
	}
}
