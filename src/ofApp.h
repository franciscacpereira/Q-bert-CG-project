#pragma once

#include "ofMain.h"
#include "extraTools.h"
#include "cameraTools.h"
#include "colorTools.h"
#include "Pyramid.h"
#include "Qbert.h"
#include "Ball.h"

#include <random>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void checkPyramidCollision();
		ofVec3f getBallSpawnPoint();
		int getRandomInt(int min, int max);

		/* DEBUG VARIALES */
		GLfloat debugRotationX, debugRotationY, debugRotationZ;
		
		/* CAMERA AND VIEWPORT VARIABLES */
		int viewType;

		// ortho view variables
		int isometricCameraDistance;
		int orthoAdjust;
		GLfloat orthoRatio;

		// perspective view variables
		int perspectiveCameraDistance;
		GLfloat lensAngle = 75;
		GLfloat alpha = 10;
		GLfloat beta = 1000;

		/* GAME VARIABLES */
		Pyramid* pyramid;
		Qbert* qbert;
		Ball* ball;

		GLfloat ballSize;

		/* GAME STATE VARIABLES */ 
		bool gameStarted;
};
