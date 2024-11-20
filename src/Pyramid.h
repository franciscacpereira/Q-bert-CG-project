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

	// animation variables

};

#endif // PYRAMID_H