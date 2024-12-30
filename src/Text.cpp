// Text.cpp - Main file for the Text class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "Text.h"

Text::Text() {
	this->text = "";
	this->textLength = 0;
	this->characterMatrix = {};
	this->textUnitLength = 0;
	this->textUnitHeight = 0;
}

Text::Text(string text) {
	this->text = text;
	this->textLength = text.length();
	this->characterMatrix = {};
	getTextUnitLength();
	this->textUnitHeight = this->characterUnitHeight;
}

void Text::setText(string text) {
	this->text = text;
	this->textLength = text.length();
	this->characterMatrix = {};
	getTextUnitLength();
	this->textUnitHeight = this->characterUnitHeight;
}

void Text::draw() {
	float unit = 1;			// used for the size of each character and blank space
	int nbrCharUnits = 0;	// used to calculate the total length of the text
	int xOffset = 0;		// used to translate the characters to the right of the text
	char character;

	setMaterial(BLUE_TILE);
	glPushMatrix(); {
		// center text in the origin
		glTranslatef(-this->textUnitLength / 2, (this->textUnitHeight / 2) * unit, 0);

		// flip the whole text vertically with the y-axis
		glScalef(1, -1, 1);

		// iterate through the text and print each character individually
		for (int i = 0; i < this->textLength; i++) {

			character = text[i];
			if (character >= 'a' && character <= 'z') {
				// convert to uppercase
				character = character - ('a' - 'A');
			}

			glPushMatrix(); {
				if (character == ' ') {
					// draw a blank space
					glTranslatef(xOffset, 0, 0);
					xOffset += unit;
				}
				else {
					// draw the character
					glTranslatef(xOffset, 0, 0);
					nbrCharUnits = unitCharacter(character);
					xOffset += nbrCharUnits;
				}

				xOffset += unit;		// add an extra blank space after each character
			} glPopMatrix();
		}

		xOffset -= unit;				// remove the last extra blank space (every character has an extra blank space)
		this->textUnitLength = xOffset;

	} glPopMatrix();

}

// draws a single unit character next to the origin
// 0,0 ---------------------------- x (columns)
//  |    X X X
//  |  X       X
//  |  X       X
//  |  X X X X X
//  |  X       X
//  |  X       X
//  |
//  y (rows)
int Text::unitCharacter(char character) {
	getCharacterMatrix(character);

	int rows = this->characterMatrix.size();
	int columns = this->characterMatrix[0].size();
	float offset = 0.5;	// offset to make the corner be at the origin

	glPushMatrix(); {
		// draw the character
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < columns; col++) {
				if (this->characterMatrix[row][col]) {
					
					// draw a "pixel" of the character
					glPushMatrix(); {
						glTranslatef(col + offset, row + offset, 0);
						unitCube();
					} glPopMatrix();
				}
			}
		}
	} glPopMatrix();

	// return the unit length of the character
	return columns;
}

int Text::getCharacterMatrix(char character) {
	switch (character) {
	case 'A':
		characterMatrix = { 
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'B':
		characterMatrix = {
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 0}
		};
		break;

	case 'C':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'D':
		characterMatrix = {
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 0}
		};
		break;

	case 'E':
		characterMatrix = {
			{1, 1, 1, 1},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 1}
		};
		break;

	case 'F':
		characterMatrix = {
			{1, 1, 1, 1},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0}
		};
		break;

	case 'G':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 0},
			{1, 0, 1, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'H':
		characterMatrix = {
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'I':
		characterMatrix = {
			{1, 1, 1},
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},
			{1, 1, 1}
		};
		break;

	case 'J':
		characterMatrix = {
			{0, 0, 0, 1},
			{0, 0, 0, 1},
			{0, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'K':
		characterMatrix = {
			{1, 0, 0, 1},
			{1, 0, 1, 0},
			{1, 1, 0, 0},
			{1, 0, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'L':
		characterMatrix = {
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 1}
		};
		break;

	case 'M':
		characterMatrix = {
			{1, 0, 0, 0, 1},
			{1, 1, 0, 1, 1},
			{1, 0, 1, 0, 1},
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1}
		};
		break;

	case 'N':
		characterMatrix = {
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 0, 1},
			{1, 0, 1, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'O':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'P':
		characterMatrix = {
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 0},
			{1, 0, 0, 0},
			{1, 0, 0, 0}
		};
		break;

	case 'Q':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 1, 0},
			{0, 1, 0, 1}
		};
		break;

	case 'R':
		characterMatrix = {
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'S':
		characterMatrix = {
			{0, 1, 1, 1},
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'T':
		characterMatrix = {
			{1, 1, 1, 1, 1},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0}
		};
		break;

	case 'U':
		characterMatrix = {
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case 'V':
		characterMatrix = {
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{0, 1, 0, 1, 0},
			{0, 1, 0, 1, 0},
			{0, 0, 1, 0, 0}
		};
		break;

	case 'W':
		characterMatrix = {
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{1, 0, 1, 0, 1},
			{0, 1, 0, 1, 0},
			{0, 1, 0, 1, 0}
		};
		break;

	case 'X':
		characterMatrix = {
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{1, 0, 0, 1}
		};
		break;

	case 'Y':
		characterMatrix = {
			{1, 0, 0, 0, 1},
			{1, 0, 0, 0, 1},
			{0, 1, 0, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0}
		};
		break;

	case 'Z':
		characterMatrix = {
			{1, 1, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 1, 0},
			{0, 1, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 1}
		};
		break;

	case '0':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 1, 1},
			{1, 1, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '1':
		characterMatrix = {
			{0, 0, 1},
			{0, 1, 1},
			{1, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1}
		};
		break;

	case '2':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{0, 0, 0, 1},
			{0, 1, 1, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 1}
		};
		break;

	case '3':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '4':
		characterMatrix = {
			{1, 0, 0, 0},
			{1, 0, 1, 0},
			{1, 0, 1, 0},
			{1, 1, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		};
		break;

	case '5':
		characterMatrix = {
			{1, 1, 1, 1},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '6':
		characterMatrix = {
			{0, 1, 1, 1},
			{1, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '7':
		characterMatrix = {
			{1, 1, 1, 1},
			{0, 0, 0, 1},
			{0, 0, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		};
		break;

	case '8':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '9':
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 1},
			{1, 0, 0, 1},
			{0, 1, 1, 0}
		};
		break;

	case '!':
		characterMatrix = {
			{1},
			{1},
			{1},
			{1},
			{0},
			{1}
		};
		break;

	case '"':
		characterMatrix = {
			{1, 0, 1},
			{1, 0, 1},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		};
		break;

	case '\'':
		characterMatrix = {
			{1},
			{1},
			{0},
			{0},
			{0},
			{0}
		};
		break;

	case '*':
		characterMatrix = {
			{0, 1, 0},
			{1, 1, 1},
			{0, 1, 0},
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		};
		break;

	case '#':
		characterMatrix = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
		break;

	default:
		// question mark '?'
		characterMatrix = {
			{0, 1, 1, 0},
			{1, 0, 0, 1},
			{0, 0, 0, 1},
			{0, 1, 1, 0},
			{0, 0, 0, 0},
			{0, 1, 0, 0}
		};
		break;
	}

	return characterMatrix.size();
}

void Text::getTextUnitLength() {
	float unit = 1;			// used for the size of each character and blank space
	char character;

	for (int i = 0; i < this->textLength; i++) {
		character = text[i];

		if (character >= 'a' && character <= 'z') {
			// convert to uppercase
			character = character - ('a' - 'A');
		}

		(character == ' ') ? this->textUnitLength += unit + unit : this->textUnitLength += unit + unitCharacter(character);
	}
}

bool Text::isTextNull() {
	if (this->text == "" || this->textLength == 0) {
		return true;
	}
	return false;
}
