// Text.h - Header file for the Text class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include "ofMain.h"
#include "extraTools.h"
#include "colorTools.h"
#include "movementTools.h"


class Text {
public:
	Text();
	Text(string);
	void setText(string);
	void draw();
	int unitCharacter(char);
	int getCharacterMatrix(char );
	void getTextUnitLength();
	bool isTextNull();

	string text;
	vector<vector<bool>> characterMatrix;
	int textLength;
	int textUnitLength;
	int characterUnitHeight = 6;
};

#endif // TEXT_H
