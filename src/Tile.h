// Tile.h - Header file for the Tile class

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef TILE_H
#define TILE_H

#include "ofMain.h"
#include "extraTools.h"

class Tile {
public:
	Tile(ofVec3f);
	void draw();

	GLint tileSize;
	ofVec3f center;
	bool ifFlipped;
};

#endif // TILE_H
