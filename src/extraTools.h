// extraTools.h - Header file for the file containing all extra tools

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#ifndef EXTRATOOLS_H
#define EXTRATOOLS_H

#include "ofMain.h"

#define PI 3.14159265358979323846

// miscellaneous functions
float gw();
float gh();
void setFrWt();
void coutModelviewMatrix();
ofVec3f cross(ofVec3f, ofVec3f);

// drawing functions
void drawFilled();
void drawLines();
void drawPoint();
void draw3DAxis();
void unitSquare();
void unitCube();
void unitSphere();
void drawSphere(GLint, GLint, GLfloat);
void drawCylinder(GLfloat, GLfloat, GLfloat, GLint);

#endif // EXTRATOOLS_H
