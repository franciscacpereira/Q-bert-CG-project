// Tile.cpp - Main file for the Tile class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Tile.h"

Tile::Tile(ofVec3f center) {
	this->center = center;
	this->ifFlipped = false;
}

void Tile::draw() {
	glPushMatrix(); {
		glTranslatef(this->center.x, this->center.y, this->center.z);
		glScalef(this->tileSize, this->tileSize, this->tileSize);

		if (this->ifFlipped) {
			glColor3f(0, 1, 0);
		}
		else {
			glColor3f(1, 0, 0);
		}

		float p = 0.5;
		glBegin(GL_QUADS);

	} glPopMatrix();
}