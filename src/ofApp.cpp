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
	shakeAmplitude = 1.5;
	shakeFrequency = 10;
	shakeTime = 0;
	gameOverTime = 0;
	gameOverDuration = 2;

	gameWonTime = 0;
	gameWonDuration = gameOverDuration;

	// qbert
	drawQbert = true;
	GLfloat qbertSize = pyramid->tileSize * PYRAMID_TO_QBERT_RATIO;
	ofVec3f qbertStartPosition = pyramid->coords[0][0];
	qbertStartPosition.y += pyramid->tileSize * 0.5 + qbertSize * 0.5;
	qbert = new Qbert(qbertStartPosition, qbertSize, pyramid->tileSize, pyramid->tileSize, objectDeathHeight, maxLives);

	// balls
	ballSpawnInterval = 0;
	lastBallSpawnTime = -1;
	lastActiveBallIndex = -1;

	ballCollisionDuration = 1;
	ballCollisionTime = -1;
	lastQbertFlashTime = -1;

	balls.clear();
	ballSize = pyramid->tileSize * 0.8;
	maxBalls = 10;
	for (int i = 0; i < maxBalls; i++) {
		balls.push_back(Ball(ofVec3f(0, 0, 0), ballSize, pyramid->tileSize, pyramid->tileSize, objectDeathHeight));
	}

	// lives
	lives.clear();
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

	fpCameraDistance = 0;
	fpLensAngle = 40;
	fpAlpha = 1;
	fpBeta = 1000;

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


	/* UPDATE GAME VARIABLES */
	// calculate time per frame (delta_t)
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;

	// game won
	if (pyramid->nbrFlippedTiles == pyramid->nbrTotalTiles) {

		if (!gameWon) {
			gameWon = true;
			enemyActivated = false;

			// pause all objects
			this->qbert->pause();

			for (int i = 0; i < maxBalls; i++) {
				balls[i].pause();
			}

			// start rainbow animation
			pyramid->rainbowAnimation = true;
			gameWonTime = currentTime;
		}

		if (currentTime - gameWonTime >= gameWonDuration) {
			// end rainbow animation
			pyramid->rainbowAnimation = false;

			// kill all objects
			this->qbert->isDead = true;

			for (int i = 0; i < maxBalls; i++) {
				balls[i].isDead = true;
			}

			for (int i = 0; i < maxLives; i++) {
				lives[i].isDead = true;
			}
		}
	}

	// game over
	if (this->qbert->lives <= 0 && !gameWon) {
		gameOver = true;
		enemyActivated = false;

		// start game over animation timer and pause all objects
		if (gameOverTime == 0) {
			gameOverTime = currentTime;

			this->qbert->pause();

			for (int i = 0; i < maxBalls; i++) {
				balls[i].pause();
			}
		}

		// check if game over animation has ended
		if (currentTime - gameOverTime < gameOverDuration) {

			pyramidShakeAngle = shakeAmplitude * sin(2 * PI * shakeFrequency * shakeTime);
			shakeTime += timePerFrame;
		}
		else {
			// kill all objects
			this->qbert->isDead = true;
			
			for (int i = 0; i < maxBalls; i++) {
				balls[i].isDead = true;
			}
		}

	}

	// ball collision animation
	if (qbert->ballCollision) {
		// start of collision animation
		if (ballCollisionTime == -1) {
			ballCollisionTime = currentTime;
			qbert->update();
			qbert->isDead = false;
			qbert->pause();
			lastQbertFlashTime = currentTime;
			drawQbert = true;

			// pause all balls
			for (int i = 0; i < maxBalls; i++) {
				balls[i].pause();
			}
		}

		if (currentTime - ballCollisionTime < ballCollisionDuration) {
			// collision animation
			if (currentTime - lastQbertFlashTime >= 0.08) {
				lastQbertFlashTime = currentTime;
				drawQbert = !drawQbert;
			}
		}
		else {
			// end of collision animation
			ballCollisionTime = -1;
			//qbert->ballCollision = false;
			drawQbert = true;
			qbert->isDead = true;
			qbert->ballCollision = false;
		}
	}

	// deactivate all balls when Qbert hasn´t started moving yet (usually after losing a life)
	if (qbert->isDead) {
		enemyActivated = false;
		for (int i = 0; i < maxBalls; i++) {
			balls[i].isDead = true;
		}
	}

	// reposition qbert after death and game is running (else stays dead)
	if (this->qbert->isDead && this->qbert->lives > 0 && !gameWon) {
		this->qbert->activate();
	}

	// game running
	qbert->update();

	pyramid->update();

	if (enemyActivated) {

		// no ball has been activated yet (activate the first one)
		if (lastBallSpawnTime == -1 && lastActiveBallIndex == -1) {
			ballSpawnInterval = getRandomFloat(0.5, 3);
			lastBallSpawnTime = currentTime;
			lastActiveBallIndex++;
			if (balls[lastActiveBallIndex].isDead || balls[lastActiveBallIndex].isWaiting)
				balls[lastActiveBallIndex].activate(getBallSpawnPoint());
		}

		
		// activate new ball if the time interval has passed
		if (currentTime - lastBallSpawnTime >= ballSpawnInterval) {
			ballSpawnInterval = getRandomFloat(0.5, 3);
			lastBallSpawnTime = currentTime;
			lastActiveBallIndex++;
			if (lastActiveBallIndex >= maxBalls) {
				lastActiveBallIndex = 0;
			}

			if (balls[lastActiveBallIndex].isDead || balls[lastActiveBallIndex].isWaiting) 
				balls[lastActiveBallIndex].activate(getBallSpawnPoint());
		}

		// update all balls (if they are not active nothing happens)
		for (int i = 0; i < maxBalls; i++) {
			balls[i].update();
		}

		// only check collisions if balls are active (spare resources)
		checkBallCollision();
	}

	checkPyramidCollision();

	/* UPDATE CAMERA VARIABLES */
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
		// create small viewport off whole matrix to make first person view more easy to play
		glViewport(gw() - gw() * 0.3, gh() - gh() * 0.3, gw() * 0.25, gh() * 0.25);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-gw() * orthoRatio, gw() * orthoRatio, (-gh() + orthoAdjust) * orthoRatio, (gh() + orthoAdjust) * orthoRatio, -isometricCameraDistance, isometricCameraDistance);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(isometricCameraDistance / 2, isometricCameraDistance / 2, isometricCameraDistance / 2, 0, 0, 0, 0, 1, 0);

		glPushMatrix(); {
			for (int i = 0; i < maxBalls; i++) {
				balls[i].draw();
			}

			if (drawQbert) qbert->draw();
			pyramid->draw();
		} glPopMatrix();

		// first person view
		fpCamX = qbert->currentPosition.x;
		fpCamY = qbert->currentPosition.y;
		fpCamZ = qbert->currentPosition.z;

		fpTargetX = fpTargetY = fpTargetZ = 0;

		if (qbert->orientation == Orientation::LEFT_UP) {
			fpCamX -= qbert->size * 0.5;
			//fpCamY += qbert->size * 3;
			fpTargetX = fpCamX - pyramid->tileSize * pyramid->maxLevel * 0.5;
			fpTargetY = fpCamY + pyramid->tileSize * pyramid->maxLevel;
			fpTargetZ = fpCamZ;

		}
		else if (qbert->orientation == Orientation::RIGHT_DOWN) {
			fpCamX += qbert->size * 0.5;
			fpCamY += qbert->size * 3;
			fpTargetX = fpCamX + pyramid->tileSize * pyramid->maxLevel * 0.5;
			fpTargetY = fpCamY - pyramid->tileSize * pyramid->maxLevel;
			fpTargetZ = fpCamZ;
		}
		else if (qbert->orientation == Orientation::RIGHT_UP) {
			//fpCamY += qbert->size * 3;
			fpCamZ -= qbert->size * 0.5;
			fpTargetX = fpCamX;
			fpTargetZ = fpCamZ - pyramid->tileSize * pyramid->maxLevel * 0.5;
			fpTargetY = fpCamY + pyramid->tileSize * pyramid->maxLevel;

		}
		else if (qbert->orientation == Orientation::LEFT_DOWN) {
			fpCamY += qbert->size * 3;
			fpCamZ += qbert->size * 0.5;
			fpTargetX = fpCamX;
			fpTargetY = fpCamY - pyramid->tileSize * pyramid->maxLevel;
			fpTargetZ = fpCamZ + pyramid->tileSize * pyramid->maxLevel * 0.5;
		}

		glViewport(0, 0, gw(), gh());

		perspective(fpLensAngle, fpAlpha, fpBeta);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(fpCamX, fpCamY, fpCamZ, fpTargetX, fpTargetY, fpTargetZ, 0, 1, 0);
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
	glPushMatrix(); {
		glRotated(pyramidShakeAngle, 1, 0, 1);

		for (int i = 0; i < qbert->lives; i++) {
			lives[i].draw();
		}

		for (int i = 0; i < maxBalls; i++) {
			balls[i].draw();
		}

		if (drawQbert) qbert->draw();
		pyramid->draw();

		glScaled(1000, 1000, 1000);
		draw3DAxis();

	} glPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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

	case 'l':
		fpLensAngle++;

		if (fpLensAngle > 180)
			fpLensAngle = 0;

		cout << "LENS ANGLE = " << fpLensAngle << endl;
		break;
	
	case 'a':
		fpAlpha += 0.1;

		cout << "ALPHA = " << fpAlpha << endl;
		break;

	case 'b':
		fpBeta++;
		break;
	}

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

	if (viewType == 2) {
		//if (qbert->orientation == Orientation::LEFT_DOWN || qbert->orientation == Orientation::RIGHT_DOWN) {
			if (key == OF_KEY_UP) {
				key = OF_KEY_DOWN;
			}
			else if (key == OF_KEY_DOWN) {
				key = OF_KEY_UP;
			}
			else if (key == OF_KEY_LEFT) {
				key = OF_KEY_RIGHT;
			}
			else if (key == OF_KEY_RIGHT) {
				key = OF_KEY_LEFT;
			}
		//}
		//else if (qbert->orientation == Orientation::LEFT_UP || qbert->orientation == Orientation::RIGHT_UP) {
			// do nothing
			// needs improvements...
		//}
	}

	qbert->keyPressed(key);
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
				if (balls[i].isDead == false && balls[i].isWaiting == false && ballPos.distance(tile) <= this->balls[i].size * 0.5 + this->pyramid->tileSize * 0.5) {
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
		if (balls[i].isDead == false && balls[i].isWaiting == false && qbert->currentPosition.distance(balls[i].currentPosition) <= qbert->size * 0.5 + balls[i].size * 0.5) {
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