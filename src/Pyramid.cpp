// Pyramid.cpp - Main file for the Pyramid class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Pyramid.h"

Pyramid::Pyramid() {
	baseSetup();
}

Pyramid::Pyramid(GLint maxLevel, GLfloat tileSize) {
	this->maxLevel = maxLevel;
	this->tileSize = tileSize;
	this->setCoords();
}

void Pyramid::baseSetup() {
	// set the coords matrix to have the coordinates of a 7 level pyramid with 10 units per tile
	this->maxLevel = 7;
	this->tileSize = 10;
	this->setCoords();
}

void Pyramid::draw() {
	// pyramid stack
	glPushMatrix(); {
		int currentMaxLevel = this->maxLevel;
		for (int row = 0; row < this->maxLevel; row++, currentMaxLevel--) {
			for (int column = 0; column < currentMaxLevel; column++) {
				// individual tile stack
				glPushMatrix(); {
					this->drawTile(this->coords[row][column], true);
				} glPopMatrix();
			}
		}
	} glPopMatrix();
}

// sets the coordinates of the pyramid
// creates a 2D matrix with the cube center coordinates in the pyramid
// output: 7 6 5 4 3 2 1
//         6 5 4 3 2 1
//         5 4 3 2 1
//         4 3 2 1
//         3 2 1
//         2 1
//         1
void Pyramid::setCoords() {
	this->coords = vector<vector<ofVec3f>>(this->maxLevel);

	int currentMaxLevel = this->maxLevel;
	for (int row = 0; row < this->maxLevel; row++, currentMaxLevel--) {
		// create the new row
		this->coords[row] = vector<ofVec3f>(currentMaxLevel);

		for (int column = 0; column < currentMaxLevel; column++) {
			GLfloat width = column * this->tileSize + (this->tileSize / 2);
			GLfloat length = row * this->tileSize + (this->tileSize / 2);
			GLfloat height = (currentMaxLevel - column) * this->tileSize - (this->tileSize / 2);

			// add new coordenate to the matrix
			this->coords[row][column] = ofVec3f(width, height, length);
		}
	}
}

// draws a single tile from the pyramid
void Pyramid::drawTile(ofVec3f center, bool isFlipped) {
	GLfloat unit = 0.5;

	glTranslated(center.x, center.y, center.z);
	glScaled(this->tileSize, this->tileSize, this->tileSize);
	glPushMatrix(); {
		// front face
		glPink();
		glPushMatrix(); {
			glTranslated(0, 0, unit);
			unitSquare();
		} glPopMatrix();

		// back face
		glMagenta();
		glPushMatrix(); {
			glTranslated(0, 0, -unit);
			glRotated(180, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// left face
		glPink();
		glPushMatrix(); {
			glTranslated(-unit, 0, 0);
			glRotated(270, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// right face
		glMagenta();
		glPushMatrix(); {
			glTranslated(unit, 0, 0);
			glRotated(90, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// bottom face
		glWhite();
		glPushMatrix(); {
			glTranslated(0, -unit, 0);
			glRotated(90, 1, 0, 0);
			unitSquare();
		} glPopMatrix();

		// top face
		if (isFlipped) {
			glRed();
		}
		else {
			glLime();
		}
		glPushMatrix(); {
			glTranslated(0, unit, 0);
			glRotated(270, 1, 0, 0);
			unitSquare();
		} glPopMatrix();

	} glPopMatrix();
}