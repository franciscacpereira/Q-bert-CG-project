// Qbert.cpp - Main file for the Qbert class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Qbert.h"

Qbert::Qbert(ofVec3f startPosition, GLfloat size, GLfloat jumpHeight, GLfloat jumpDistance) {
	this->startPosition = startPosition;
	this->qbertSize = size;
	this->jumpHeight = jumpHeight;
	this->jumpDistance = jumpDistance;
	i = 0;
	j = 0;
	baseSetup();
}

/*
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
*/

void Qbert::baseSetup() {
	this->currentPosition = this->startPosition;
	this->previousPosition = this->startPosition;
	this->prevPrevPosition = this->prevPrevPosition;
	this->orientation = Orientation::LEFT_DOWN;
	this->isDead = false;
	this->isMoving = false;
	this->isFalling = false;
	resetPhysics();

	// set variables for fall
	this->fallVelocity = ofVec3f(0, -0.5, 0);
	this->fallAcceleration = ofVec3f(0, -0.5, 0);
}

void Qbert::resetPhysics() {
	this->jumpProgress = 0;
	this->timePerFrame = 0;
	this->previousTime = 0;
	this->jumpStartPosition = ofVec3f(0, 0, 0);
	this->targetPosition = ofVec3f(0, 0, 0);
	this->pyramidCollision = false;
	this->velocityMod = 15;
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
		i = 0;
		cout << "DIED ######################################\n";
		baseSetup();
		return;
	}

	// check if the player fell into the ground
	if (this->currentPosition.y - this->qbertSize <= -this->startPosition.y) {
		this->isDead = true;
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
				j = 0;
				return;
			}
			else {
				/*
				if (this->currentPosition.distance(this->previousPosition) > 5) {
					this->fallVelocity = (this->currentPosition - this->previousPosition);
					cout << "fall velocity = " << this->fallVelocity << "\n" << endl;
					cout << "current position = " << this->currentPosition << "\n" << endl;
					cout << "previous position = " << this->previousPosition << "\n" << endl;
					cout << "distance = " << this->currentPosition.distance(this->previousPosition) << "\n" << endl;

				} else {
					this->fallVelocity = (this->currentPosition - this->prevPrevPosition);
					cout << "fall velocity = " << this->fallVelocity << "\n" << endl;
					cout << "current position = " << this->currentPosition << "\n" << endl;
					cout << "prePrev position = " << this->previousPosition << "\n" << endl;
					cout << "distance = " << this->currentPosition.distance(this->previousPosition) << "\n" << endl;

				}
				*/
				//this->jumpStartPosition = this->currentPosition;

				/*
				this->targetPosition.y = -100;
				if (this->orientation == Orientation::LEFT_UP || this->orientation == Orientation::RIGHT_DOWN) {
					this->targetPosition.x = this->currentPosition.x + this->jumpDistance * 0.5;
				} else if (this->orientation == Orientation::LEFT_DOWN || this->orientation == Orientation::RIGHT_UP) {
					this->targetPosition.z = this->currentPosition.z + this->jumpDistance * 0.5;
				}
				*/
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

				cout << "fall velocity = " << this->fallVelocity << "\n" << endl;


				this->isFalling = true;
				this->jumpProgress = 0;
				j = 0;
				
			}
		}

		if (!this->isFalling) {
			this->jumpProgress += this->timePerFrame * 3;
			// calculate the new position of the player (jumping)
			float height = sin(this->jumpProgress * PI) * this->jumpHeight;
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			newPosition.y += height;

			this->prevPrevPosition = this->previousPosition;
			this->previousPosition = this->currentPosition;
			this->currentPosition = newPosition;
			j++;	
			cout << "j = " << j << "\n" << endl;
		}
		else {
			/*
			GLfloat ratio = 6;
			this->jumpProgress += this->timePerFrame * ratio;
			// calculate the new position of the player (falling)
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			this->currentPosition = newPosition;
			
			*/

			
			this->fallVelocity += this->fallAcceleration;

			this->previousPosition = this->currentPosition;
			this->currentPosition += this->fallVelocity;
			i++;
			
			cout << i << "\tjump progess = " << this->jumpProgress << "\n" << endl;
		}


		/*
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
			ofVec3f newPosition = this->jumpStartPosition.getInterpolated(this->targetPosition, this->jumpProgress);
			this->currentPosition = newPosition;
		}
		*/
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
	this->isMoving = true;
	this->jumpStartPosition = this->currentPosition;
	this->targetPosition = target;
	this->jumpProgress = 0;
}

/*
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
*/