// Pyramid.h - Header file for the Pyramid class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef PYRAMID_H
#define PYRAMID_H

#include "ofMain.h"
#include "extraTools.h"
#include "colorTools.h"
#include "movementTools.h"
#include "materialTools.h"

#define COLOR_CHANGE_TIME 0.1	// ms

class Pyramid {
public:
	Pyramid();
	Pyramid(GLint, GLfloat);
    void baseSetup();
    void draw();
	void update();
    void setCoords();
	void setColors();
	void setTileColor(int, int, bool);
	void drawTile(ofVec3f, bool);

	int nbrFlippedTiles;
	int nbrTotalTiles;
    GLint maxLevel;
    GLfloat tileSize;
    vector<vector<ofVec3f>> coords;
	vector<vector<bool>> colors;
	Color topColor;
	Color leftFaceColor;
	Color rightFaceColor;

	// animation variables
	bool shakeAnimation;

	bool rainbowAnimation;
	vector<Color> rainbowColors;
	vector<Material> rainbowMaterials;
	float colorChangeTime = COLOR_CHANGE_TIME;
	float previousChangeTimer;
	int currentColorIndex;
};

#endif // PYRAMID_H