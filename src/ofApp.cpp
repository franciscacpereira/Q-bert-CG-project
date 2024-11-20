#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	glEnable(GL_DEPTH_TEST);	// makes the objets closer to the camera appear in front of the others (even if they are drawn later)
	ofBackground(18, 18, 23);
	glLineWidth(5);

	/* INIT DEBUG VARIABLES */
	debugRotationX = 0;
	debugRotationY = 0;
	debugRotationZ = 0;

	/* INIT GAME VARIABLES */
	maxLives = 3;
	currentLives = maxLives;

	// pyramid
	pyramid = new Pyramid(7, 50);
	GLfloat objectDeathHeight = -(pyramid->tileSize * pyramid->maxLevel * 2);

	pyramidShakeAngle = 0;
	shakeAmplitude = 2;
	shakeFrequency = 1;
	shakeTime = 0;

	// qbert
	GLfloat qbertSize = pyramid->tileSize * PYRAMID_TO_QBERT_RATIO;
	ofVec3f qbertStartPosition = pyramid->coords[0][0];
	qbertStartPosition.y += pyramid->tileSize * 0.5 + qbertSize * 0.5;
	qbert = new Qbert(qbertStartPosition, qbertSize, pyramid->tileSize, pyramid->tileSize, objectDeathHeight, maxLives);

	// balls
	ballSize = pyramid->tileSize * 0.8;
	maxBalls = 10;
	for (int i = 0; i < maxBalls; i++) {
		balls.push_back(Ball(ofVec3f(0, 0, 0), ballSize, pyramid->tileSize, pyramid->tileSize, objectDeathHeight));
	}

	// lives
	GLfloat startZ = pyramid->tileSize * pyramid->maxLevel * 0.5;
	GLfloat livesDistance = qbertSize;
	for (int i = 0; i < maxLives; i++) {
		ofVec3f startPos = ofVec3f(-startZ + i * livesDistance, pyramid->tileSize * pyramid->maxLevel, startZ - i * livesDistance);
		lives.push_back(Qbert(startPos, qbertSize, 0, 0, 0, maxLives));
	}

	/* INIT CAMERA VARIABLES */
	viewType = 0;

	isometricCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel);
	orthoAdjust = 200;
	orthoRatio = pyramid->tileSize * 0.35 / 50;

	perspectiveCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel * 1.5);
	lensAngle = 75;
	alpha = 10;
	beta = 1000;

	/* INIT GAME STATE VARIABLES */
	enemyActivated = false;
	gameOver = false;
	gameWon = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	/* UPDATE DEBUG VARIABLES */
	debugRotationX += 0.5;
	debugRotationY += 0.5;
	debugRotationZ += 1;

	/* UPDATE CAMERA VARIABLES */

	/* UPDATE GAME VARIABLES */

	// if game has been won pause all moving objects in screen
	if (pyramid->nbrFlippedTiles == pyramid->nbrTotalTiles) {
		gameWon = true;
		this->qbert->pause();

		for (int i = 0; i < maxBalls; i++) {
			balls[i].pause();
		}
	}

	// game over
	if (this->qbert->lives <= 0) {
		gameOver = true;
		pyramidShakeAngle = shakeAmplitude * sin(2 * PI * shakeFrequency * shakeTime);
		shakeTime += 0.1;

		this->qbert->pause();
		
		for (int i = 0; i < maxBalls; i++) {
			balls[i].pause();
		}
	}

	// game running
	qbert->update();
	pyramid->update();

	if (enemyActivated) {
		for (int i = 0; i < maxBalls; i++) {
			balls[i].update();
		}
		checkBallCollision();
	}

	checkPyramidCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){
	/* DRAW THE SCENE */
	switch (viewType) {
	case 0:
		// 2D isometric front view
		glViewport(0, 0, gw(), gh());

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-gw() * orthoRatio, gw() * orthoRatio, (-gh() + orthoAdjust) * orthoRatio, (gh() + orthoAdjust) * orthoRatio, -isometricCameraDistance, isometricCameraDistance);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(isometricCameraDistance / 2, isometricCameraDistance / 2, isometricCameraDistance / 2, 0, 0, 0, 0, 1, 0);
		break;
	case 1:
		// 3D side view
		glViewport(0, 0, gw(), gh());

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		perspective(lensAngle, alpha, beta);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(perspectiveCameraDistance / 4, perspectiveCameraDistance / 3, perspectiveCameraDistance / 2, 0, pyramid->tileSize * (pyramid->maxLevel / 3), 0, 0, 1, 0);
		break;
	case 2:
		// first person view
		// to be implemented ...
		break;
	case 3:
		// random tests
		//glViewport(0, 0, gw(), gh());

		glTranslated(gw() / 2, gh() / 2, 0);
		glRotated(debugRotationX, 1, 0, 0);
		glRotated(debugRotationY, 0, 1, 0);
		glRotated(debugRotationZ, 0, 0, 1);
		break;
	}

	/* DRAW THE GAME */

	for (int i = 0; i < qbert->lives; i++) {
		lives[i].draw();
	}

	for (int i = 0; i < maxBalls; i++) {
		balls[i].draw();
	}

	glRotated(pyramidShakeAngle, 1, 0, 1);

	qbert->draw();
	pyramid->draw();

	glScaled(1000, 1000, 1000);
	draw3DAxis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (gameOver || gameWon) {
		if (key == 'r') {
			int curentView = viewType;
			setup();
			viewType = curentView;
		}
		return;
	}

	if (key == OF_KEY_UP || key == OF_KEY_DOWN || key == OF_KEY_LEFT || key == OF_KEY_RIGHT) {
		enemyActivated = true;
	}
	qbert->keyPressed(key);

	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;

	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;

	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;

	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;

	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case 'v':
		viewType++;
		
		if (viewType > 3) {
			viewType = 0;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

////////////////////////////////////////////////////////////////

void ofApp::checkPyramidCollision() {
	bool qbertCollision = false;
	bool ballCollision = false;

	int currentMaxLevel = this->pyramid->maxLevel;
	for (int row = 0; row < this->pyramid->maxLevel; row++, currentMaxLevel--) {
		for (int col = 0; col < currentMaxLevel; col++) {
			ofVec3f tile = this->pyramid->coords[row][col];

			// qbert vs pyramid collision
			if (qbert->currentPosition.distance(tile) < qbert->size * 0.5 + this->pyramid->tileSize * 0.5) {	// changed from <= to < so it wouldn´t paint the first tile when it died
				// change the color of the tile
				if (this->qbert->isMoving) {
					if (!this->pyramid->colors[row][col])
						this->pyramid->nbrFlippedTiles++;
					this->pyramid->setTileColor(row, col, true);
				}
				this->qbert->pyramidCollision = true;
				qbertCollision = true;
			}

			// ball vs pyramid collision
			for (int i = 0; i < this->maxBalls; i++) {
				ofVec3f ballPos = this->balls[i].currentPosition;
				if (ballPos.distance(tile) < this->balls[i].size * 0.5 + this->pyramid->tileSize * 0.5) {
					this->balls[i].pyramidCollision = true;
					ballCollision = true;
				}
			}
			/*
			if (ball->currentPosition.distance(tile) < ball->size * 0.5 + this->pyramid->tileSize * 0.5) {
				this->ball->pyramidCollision = true;
				ballCollision = true;
			}
			*/
		}
	}
	

	//this->qbert->pyramidCollision = qbertCollision;
	//this->ball->pyramidCollision = ballCollision;
}

void ofApp::checkBallCollision() {
	// collision between ball and qbert
	for (int i = 0; i < maxBalls; i++) {
		if (qbert->currentPosition.distance(balls[i].currentPosition) <= qbert->size * 0.5 + balls[i].size * 0.5) {
			qbert->ballCollision = true;
			balls[i].qbertCollision = true;
		}
	}



	/*
	if (this->qbert->currentPosition.distance(this->ball->currentPosition) <= this->qbert->size * 0.5 + this->ball->size * 0.5) {
		this->qbert->ballCollision = true;
		this->ball->qbertCollision = true;
	}
	*/
}

ofVec3f ofApp::getBallSpawnPoint() {
	ofVec3f spawnPoint = ofVec3f(0., 0., 0.);
	GLfloat buffer = pyramid->tileSize;
	GLfloat qbertDistance = ballSize * 0.5 + qbert->size * 0.5 + buffer;
	GLfloat surfaceDistance = pyramid->tileSize * 0.5 + ballSize * 0.5;

	bool validSpawnPoint = false;

	while (!validSpawnPoint) {
		// get a random tile center point
		int row = getRandomInt(0, pyramid->maxLevel - pyramid->maxLevel * 0.5);
		int column = getRandomInt(0, pyramid->coords[row].size() - pyramid->coords[row].size() * 0.5);

		// adjust height to surface level
		spawnPoint = pyramid->coords[row][column];
		spawnPoint.y += surfaceDistance;

		// check if there is collision with Qbert position
		if (spawnPoint.distance(qbert->currentPosition) > qbertDistance) {
			validSpawnPoint = true;
		}
	}
	
	return spawnPoint;
}