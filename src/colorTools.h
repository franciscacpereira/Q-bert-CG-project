#ifndef COLORTOOLS_H
#define COLORTOOLS_H

#include "ofMain.h"

enum Color {
	RED,
	GREEN,
	BLUE,
	DARK_BLUE,
	CYAN,
	LIGHT_BLUE,
	PURPLE,
	LIME,
	YELLOW,
	ORANGE,
	DARK_ORANGE,
	MAGENTA,
	PINK,
	BROWN,
	WHITE,
	BLACK,
	GRAY,
	LIGHT_GRAY
};

inline void setColor(Color color) {
	switch (color) {
	case RED:
		glColor3f(1, 0, 0);
		break;
	case GREEN:
		glColor3f(0, 1, 0);
		break;
	case BLUE:
		glColor3f(0, 0, 1);
		break;
	case DARK_BLUE:
		glColor3f(0, 0, 0.5);
		break;
	case CYAN:
		glColor3f(0, 1, 1);
		break;
	case LIGHT_BLUE:
		glColor3f(0, 0.5, 1);
		break;
	case PURPLE:
		glColor3f(0.5, 0, 1);
		break;
	case LIME:
		glColor3f(0.5, 1, 0);
		break;
	case YELLOW:
		glColor3f(1, 1, 0);
		break;
	case ORANGE:
		glColor3f(1, 0.6, 0);
		break;
	case DARK_ORANGE:
		glColor3f(1, 0.5, 0);
		break;
	case MAGENTA:
		glColor3f(1, 0, 1);
		break;
	case PINK:
		glColor3f(1, 0.5, 1);
		break;
	case BROWN:
		glColor3f(0.5, 0.25, 0);
		break;
	case WHITE:
		glColor3f(1, 1, 1);
		break;
	case BLACK:
		glColor3f(0, 0, 0);
		break;
	case GRAY:
		glColor3f(0.5, 0.5, 0.5);
		break;
	case LIGHT_GRAY:
		glColor3f(0.75, 0.75, 0.75);
		break;
	}
}

inline ofColor randomColor() {
	return ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

inline void glRed() {
	glColor3f(1, 0, 0);
}

inline void glGreen() {
	glColor3f(0, 1, 0);
}

inline void glBlue() {
	glColor3f(0, 0, 1);
}

inline void glDarkBlue() {
	glColor3f(0, 0, 0.5);
}

inline void glCyan() {
	glColor3f(0, 1, 1);
}

inline void glLightBlue() {
	glColor3f(0, 0.5, 1);
}

inline void glPurple() {
	glColor3f(0.5, 0, 1);
}

inline void glLime() {
	glColor3f(0.5, 1, 0);
}

inline void glYellow() {
	glColor3f(1, 1, 0);
}

inline void glOrange() {
	glColor3f(1, 0.6, 0);
}

inline void glDarkOrange() {
	glColor3f(1, 0.5, 0);
}

inline void glMagenta() {
	glColor3f(1, 0, 1);
}

inline void glPink() {
	glColor3f(1, 0.5, 1);
}

inline void glBrown() {
	glColor3f(0.5, 0.25, 0);
}

inline void glWhite() {
	glColor3f(1, 1, 1);
}

inline void glBlack() {
	glColor3f(0, 0, 0);
}

inline void glGray() {
	glColor3f(0.5, 0.5, 0.5);
}

inline void glLightGray() {
	glColor3f(0.75, 0.75, 0.75);
}

#endif // COLORTOOLS_H

