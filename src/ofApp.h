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
		void checkBallCollision();
		ofVec3f getBallSpawnPoint();

		/* DEBUG VARIALES */
		GLfloat debugRotationX, debugRotationY, debugRotationZ;
		
		/* CAMERA AND VIEWPORT VARIABLES */
		int viewType;

		// ortho view variables
		GLfloat isometricCameraDistance;
		GLfloat orthoAdjust;
		GLfloat orthoRatio;

		// perspective view variables
		GLfloat perspectiveCameraDistance;
		GLfloat lensAngle = 75;
		GLfloat alpha = 10;
		GLfloat beta = 1000;

		// first person view variables
		GLfloat fpCameraDistance;
		GLfloat fpLensAngle;
		GLfloat fpAlpha;
		GLfloat fpBeta;
		GLfloat fpCamX;
		GLfloat fpCamY;
		GLfloat fpCamZ;
		GLfloat fpTargetX;
		GLfloat fpTargetY;
		GLfloat fpTargetZ;


		/* GAME VARIABLES */
		Pyramid* pyramid;
		Qbert* qbert;
		vector<Qbert> lives;
		vector<Ball> balls;

		int maxLives;
		int currentLives;
		int maxBalls;
		GLfloat ballSize;

		// ball spawn variables
		float ballSpawnInterval;
		float lastBallSpawnTime;
		int lastActiveBallIndex;

		// delta_t variables
		float timePerFrame;
		float previousTime;

		// shake animation variables
		GLfloat shakeAmplitude; 
		GLfloat shakeFrequency;
		GLfloat pyramidShakeAngle;
		float shakeTime;
		float gameOverTime;
		float gameOverDuration;

		// rainbow animation variables
		float gameWonTime;
		float gameWonDuration;

		// ball collision animation variables
		float ballCollisionTime;
		float ballCollisionDuration;
		float lastQbertFlashTime;
		bool drawQbert;


		/* GAME STATE VARIABLES */ 
		bool enemyActivated;
		bool gameOver;
		bool gameWon;
};
