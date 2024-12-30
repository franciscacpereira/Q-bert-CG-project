// Pyramid.cpp - Main file for the Pyramid class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Pyramid.h"

Pyramid::Pyramid() {
	baseSetup();
}

Pyramid::Pyramid(GLint maxLevel, GLfloat tileSize) {
	this->nbrFlippedTiles = 0;
	this->nbrTotalTiles = maxLevel * (maxLevel + 1) / 2;
	this->maxLevel = maxLevel;
	this->tileSize = tileSize;
	this->setCoords();
	this->setColors();
	this->topColor = RED;
	this->leftFaceColor = PINK;
	this->rightFaceColor = MAGENTA;

	this->shakeAnimation = false;
	this->rainbowAnimation = false;
	this->rainbowColors = { RED, ORANGE, YELLOW, GREEN, CYAN, DARK_BLUE, PURPLE };
	this->rainbowMaterials = { RUBY, BRASS, GOLD, GREEN_PLASTIC, TURQUOISE, CYAN_PLASTIC, OBSIDIAN };
	this->previousChangeTimer = 0;
	this->currentColorIndex = 0;
}

void Pyramid::baseSetup() {
	// set the coords matrix to have the coordinates of a 7 level pyramid with 10 units per tile
	this->nbrFlippedTiles = 0;
	this->nbrTotalTiles = 28;
	this->maxLevel = 7;
	this->tileSize = 10;
	this->setCoords();
	this->setColors();

	this->shakeAnimation = false;
	this->rainbowAnimation = false;
	this->rainbowColors = { RED, ORANGE, YELLOW, GREEN, CYAN, DARK_BLUE, PURPLE };
	this->rainbowMaterials = { RUBY, BRASS, GOLD, GREEN_PLASTIC, TURQUOISE, CYAN_PLASTIC, OBSIDIAN };
	this->previousChangeTimer = 0;
	this->currentColorIndex = -1;
}

void Pyramid::draw() {
	// pyramid stack
	glPushMatrix(); {
		int currentMaxLevel = this->maxLevel;
		for (int row = 0; row < this->maxLevel; row++, currentMaxLevel--) {
			for (int column = 0; column < currentMaxLevel; column++) {
				// individual tile stack
				glPushMatrix(); {
					this->drawTile(this->coords[row][column], this->colors[row][column]);
				} glPopMatrix();
			}
		}
	} glPopMatrix();
}

void Pyramid::update() {
	if (this->rainbowAnimation) {
		float currentTime = getTime();
		float elapsedTime = currentTime - this->previousChangeTimer;

		if (elapsedTime >= this->colorChangeTime) {

			this->currentColorIndex++;
			if (this->currentColorIndex >= this->rainbowMaterials.size()) {
				this->currentColorIndex = 0;
			}

			this->previousChangeTimer = currentTime;
		}
	} else {
		this->previousChangeTimer = getTime();
	}
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

// sets the colors of the pyramid
// uses a boolean value to decide if the tile is flipped or not
void Pyramid::setColors() {
	this->colors = vector<vector<bool>>(this->maxLevel);

	int currentMaxLevel = this->maxLevel;
	for (int row = 0; row < this->maxLevel; row++, currentMaxLevel--) {
		// create the new row
		this->colors[row] = vector<bool>(currentMaxLevel);

		for (int column = 0; column < currentMaxLevel; column++) {
			// add new color to the matrix
			this->colors[row][column] = false;
		}
	}
}

// sets the color of a single tile to flipped or not
void Pyramid::setTileColor(int row, int column, bool isFlipped) {
	this->colors[row][column] = isFlipped;
}

// draws a single tile from the pyramid
void Pyramid::drawTile(ofVec3f center, bool isFlipped) {
	GLfloat unit = 0.5;

	glTranslated(center.x, center.y, center.z);
	glScaled(this->tileSize, this->tileSize, this->tileSize);

	// outline
	/*
	glPushMatrix(); {
		//setColor(Color::GREEN);
		drawLines();
		unitCube();
	} glPopMatrix();*/

	// cube
	drawFilled();
	glPushMatrix(); {
		setMaterial(BLUE_TILE);

		// front face
		glPushMatrix(); {
			glTranslated(0, 0, unit);
			unitSquare();
		} glPopMatrix();

		// back face
		glPushMatrix(); {
			glTranslated(0, 0, -unit);
			glRotated(180, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// left face
		glPushMatrix(); {
			glTranslated(-unit, 0, 0);
			glRotated(270, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// right face
		glPushMatrix(); {
			glTranslated(unit, 0, 0);
			glRotated(90, 0, 1, 0);
			unitSquare();
		} glPopMatrix();

		// bottom face
		glPushMatrix(); {
			glTranslated(0, -unit, 0);
			glRotated(90, 1, 0, 0);
			unitSquare();
		} glPopMatrix();

		// top face
		if (this->rainbowAnimation) {
			//setColor(this->rainbowColors[this->currentColorIndex]);
			setMaterial(this->rainbowMaterials[this->currentColorIndex]);
		}
		else {
			if (!isFlipped) {
				setMaterial(YELLOW_RUBBER);
			}
			else {
				setMaterial(PINK_TILE);
			}
		}
		glPushMatrix(); {
			glTranslated(0, unit, 0);
			glRotated(270, 1, 0, 0);
			unitSquare();
		} glPopMatrix();

	} glPopMatrix();
}