// Pyramid.h - Header file for the Pyramid class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef PYRAMID_H
#define PYRAMID_H

#include "ofMain.h"
#include "extraTools.h"
#include "colorTools.h"

class Pyramid {
public:
	Pyramid();
	Pyramid(GLint, GLfloat);
    void baseSetup();
    void draw();
    void setCoords();
	void drawTile(ofVec3f, bool);

    GLint maxLevel;
    GLfloat tileSize;
    vector<vector<ofVec3f>> coords;
};

#endif // PYRAMID_H