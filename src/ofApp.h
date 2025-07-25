#pragma once

#include "ofMain.h"
#include "extraTools.h"
#include "cameraTools.h"
#include "colorTools.h"
#include "Pyramid.h"
#include "Qbert.h"
#include "Ball.h"
#include "Text.h"

#include <random>
#include <iostream>
#include <string>

enum class TextAnimationStage { DEACTIVATED, START, SHOW, STAY, EXIT};

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

		// update functions
		void updateLights();
		void updateCamera();
		
		// game dynamics functions
		void levelUp();
		void checkPyramidCollision();
		void checkBallCollision();
		ofVec3f getBallSpawnPoint();
		void cheatGame();

		// game animation functions
		void printStartInstructionsConsole();
		void printText();
		void setupTextAnimation(string mainText, string subText, ofVec3f originPos, ofVec3f targetPos, ofVec3f originScale, ofVec3f targetScale);
		void drawOpeningScreen();
		void drawOpeningScreen_2();
		void drawBackground();
		void drawLights();

		/* DEBUG VARIALES */
		GLfloat debugRotationX, debugRotationY, debugRotationZ;
		bool debug;


		/* GAME VARIABLES */
		Pyramid* pyramid;
		Qbert* qbert;
		vector<Qbert> lives;
		vector<Ball> balls;

		// pyramid variables
		int currentPyramidLevel;
		int currentGameLevel;
		int maxGameLevel;
		int maxLives;
		int currentLives;
		int maxBalls;
		GLfloat ballSize;
		GLfloat pyramidCubeSize;

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
		float victoryAnimationTime;
		float victoryAnimationDuration;

		// ball collision animation variables
		float ballCollisionTime;
		float ballCollisionDuration;
		float lastQbertFlashTime;
		bool drawQbert;

		// text animation variables
		ofVec3f textStartPosition;
		ofVec3f textTargetPosition;
		ofVec3f textCurrentPosition;
		ofVec3f textScaleStart;
		ofVec3f textScaleTarget;
		ofVec3f textScaleCurrent;
		float textAnimationProgress;
		float textAnimationTime;
		float textAnimationDuration;
		string mainText;
		string subText;
		TextAnimationStage textAnimationStage;

		// text variables 
		ofVec3f textTranslation;
		ofVec3f textScale;
		float textRotation;

		Text* dynamicMainText;
		Text* dynamicSubText;
		vector<Text> gameStartText;

		/* GAME TEXTURE VARIABLES */
		ofImage background;
		ofImage logo;
		ofImage spaceKey;
		ofImage arrowKeys;


		/* GAME SOUND VARIABLES */
		ofSoundPlayer victorySound;
		ofSoundPlayer levelUpSound;
		ofSoundPlayer gameOverSound;
		ofSoundPlayer gameStartSound;


		/* GAME LIGHT VARIABLES */
		// directional light
		ofVec4f dirLightPosition;
		ofVec4f dirLightAmbient;
		ofVec4f dirLightDiffuse;
		ofVec4f dirLightSpecular;

		bool dirLightOn;
		bool dirLightAmbientOn;
		bool dirLightDiffuseOn;
		bool dirLightSpecularOn;

		// point light
		ofVec4f pointLightPosition;
		ofVec4f pointLightAmbient;
		ofVec4f pointLightDiffuse;
		ofVec4f pointLightSpecular;

		bool pointLightOn;
		bool pointLightAmbientOn;
		bool pointLightDiffuseOn;
		bool pointLightSpecularOn;

		// spotlight
		ofVec4f spotLightPosition;
		ofVec4f spotLightAmbient;
		ofVec4f spotLightDiffuse;
		ofVec4f spotLightSpecular;
		ofVec3f spotLightDirectionVector;
		GLfloat spotLightCutOff;
		GLfloat spotLightExponent;

		bool spotLightOn;
		bool spotLightAmbientOn;
		bool spotLightDiffuseOn;
		bool spotLightSpecularOn;


		/* GAME STATE VARIABLES */ 
		bool enemyActivated;
		bool gameOver;
		bool gameWon;
		bool gameStart;
		bool gameEnd;
		bool luAnimation;


		/* CAMERA AND VIEWPORT VARIABLES */
		int viewType;
		int maxViewType;

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

		ofVec3f fpCamera;
		ofVec3f fpTarget;
};
