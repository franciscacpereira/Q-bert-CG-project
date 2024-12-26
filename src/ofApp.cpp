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
	debug = false;



	/* INIT GAME VARIABLES */
	currentGameLevel = 1;
	maxGameLevel = 3;
	maxLives = 3;
	currentLives = maxLives;

	// pyramid
	pyramidCubeSize = 50;
	currentPyramidLevel = 7;
	pyramid = new Pyramid(currentPyramidLevel, pyramidCubeSize);
	GLfloat objectDeathHeight = -(pyramid->tileSize * pyramid->maxLevel * 10 * 0.1); //-(pyramid->tileSize * pyramid->maxLevel * 2);

	// animations
	pyramidShakeAngle = 0;
	shakeAmplitude = 1.5;
	shakeFrequency = 10;
	shakeTime = 0;
	gameOverTime = 0;
	gameOverDuration = 2;

	victoryAnimationTime = 0;
	victoryAnimationDuration = gameOverDuration;

	ofVec3f initValues = ofVec3f(0, 0, 0);
	textStartPosition = textTargetPosition = textCurrentPosition = initValues;
	textScaleStart = textScaleTarget = textScaleCurrent = initValues;
	mainText = subText = "";
	textAnimationStage = TextAnimationStage::DEACTIVATED;

	dynamicMainText = new Text();
	dynamicSubText = new Text();
	gameStartText = vector<Text>(3);
	gameStartText[0].setText("Use                  to move");
	gameStartText[1].setText("Don't fall off the pyramid!");
	gameStartText[2].setText("Press                    to start the game");

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

	isometricCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (sqrt(2) * pyramid->tileSize * pyramid->maxLevel * 0.5);
	orthoAdjust = 200;
	orthoRatio = pyramid->maxLevel * (pyramid->tileSize / 1000); //1; //pyramid->tileSize * 0.35 / 50;

	perspectiveCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel * 1.5);
	lensAngle = 75;
	alpha = 10;
	beta = 1000;

	fpCameraDistance = 0;
	fpLensAngle = 85;
	fpAlpha = 45;
	fpBeta = 1000;



	/* INIT GAME STATE VARIABLES */
	enemyActivated = false;
	gameOver = false;
	gameWon = false;
	gameStart = true;
	gameEnd = false;
	luAnimation = false;

	/* PRINT START INSTRUCTION IN CONSOLE */
	printStartInstructionsConsole();
}

//--------------------------------------------------------------
void ofApp::update(){
	/* UPDATE GAME VARIABLES */
	// calculate time per frame (delta_t)
	float currentTime = getTime();
	this->timePerFrame = currentTime - this->previousTime;
	this->previousTime = currentTime;


	// update text vectors
	GLfloat pyramidSide = pyramid->tileSize * pyramid->maxLevel;
	textTranslation = ofVec3f(pyramidSide * sqrt(2) / 3, pyramidSide * 2 / 3, pyramidSide * sqrt(2) / 3);
	textScale = ofVec3f(pyramidSide * 0.03, pyramidSide * 0.03, pyramidSide * 0.03);
	textRotation = atan(textTranslation.x / textTranslation.y) * 180 / PI;


	// game won (could be any level, does not mean end of game)
	if (pyramid->nbrFlippedTiles == pyramid->nbrTotalTiles && !luAnimation && !gameEnd) {

		// start win rainbow animation
		if (!gameWon) {
			gameWon = true;
			enemyActivated = false;

			// pause all objects
			this->qbert->pause();
			for (int i = 0; i < maxBalls; i++) balls[i].pause();

			// start rainbow animation
			pyramid->rainbowAnimation = true;
			victoryAnimationTime = currentTime;
		}

		// end win rainbow animation
		if (currentTime - victoryAnimationTime >= victoryAnimationDuration) {
			
			pyramid->rainbowAnimation = false;

			// activate text animation
			textAnimationStage = TextAnimationStage::START;
			currentGameLevel++;
			
			if (currentGameLevel > maxGameLevel) {
				// end of game animation
				gameEnd = true;
				luAnimation = false;
			}
			else {
				// level up animation
				currentPyramidLevel++;
				luAnimation = true;
				gameEnd = false;
			}
		}
	}

	// game over
	if (this->qbert->lives <= 0 && !gameWon && !gameEnd) {
		gameOver = true;
		enemyActivated = false;

		// start game over animation timer and pause all objects
		if (gameOverTime == 0) {
			gameOverTime = currentTime;

			this->qbert->pause();
			for (int i = 0; i < maxBalls; i++) balls[i].pause();
		}

		// check if game over animation has ended
		if (currentTime - gameOverTime < gameOverDuration) {

			pyramidShakeAngle = shakeAmplitude * sin(2 * PI * shakeFrequency * shakeTime);
			shakeTime += timePerFrame;
		}
		else {
			// kill all objects
			//this->qbert->isDead = true;
			//for (int i = 0; i < maxBalls; i++) balls[i].isDead = true;
			viewType = 0;
			textAnimationStage = TextAnimationStage::START;
			gameEnd = true;
		}
	}


	// text animation
	if (textAnimationStage != TextAnimationStage::DEACTIVATED) {

		switch (textAnimationStage) {
		case TextAnimationStage::START:

			// define type of animation to execute
			if (gameEnd && gameOver) {
				setupTextAnimation("GAME OVER", "Press 'R' to restart game", ofVec3f(0, 0, 0), textTranslation, ofVec3f(0, 0, 0), textScale);
			}
			else if (gameEnd && gameWon) {
				setupTextAnimation("YOU WON", "Press 'R' to restart game", ofVec3f(0, 0, 0), textTranslation, ofVec3f(0, 0, 0), textScale);
			}
			else if (luAnimation) {
				char text[20];
				sprintf(text, "LEVEL %d", currentGameLevel);
				setupTextAnimation(text, "", ofVec3f(0, 0, 0), textTranslation, ofVec3f(0, 0, 0), textScale);
			}

			textAnimationStage = TextAnimationStage::SHOW;
			break;

		case TextAnimationStage::SHOW:
			if (textAnimationProgress >= 1) {
				// target position has been reached
				textCurrentPosition = textTargetPosition;
				textScaleCurrent = textScaleTarget;

				// move up to next stage
				textAnimationDuration = 1.5;
				textAnimationTime = currentTime;
				textAnimationStage = TextAnimationStage::STAY;
			}
			else {
				// update text position and scale
				textAnimationProgress += timePerFrame * 1.5;

				ofVec3f newPosition = textStartPosition.getInterpolated(textTargetPosition, textAnimationProgress);
				textCurrentPosition = newPosition;

				ofVec3f newScale = textScaleStart.getInterpolated(textScaleTarget, textAnimationProgress);
				textScaleCurrent = newScale;
			}

			break;

		case TextAnimationStage::STAY:
			if (!gameEnd) {
				if (currentTime - textAnimationTime >= textAnimationDuration) {
					// move up to next stage
					textAnimationStage = TextAnimationStage::EXIT;

					ofVec3f camera = ofVec3f(isometricCameraDistance * 0.6, isometricCameraDistance * 0.6, isometricCameraDistance * 0.6);
					setupTextAnimation(mainText, subText, textTranslation, camera, textScale, 10 * textScale);
				}
			}

			break;

		case TextAnimationStage::EXIT:
			if (textAnimationProgress >= 1) {
				// target position has been reached
				textCurrentPosition = textTargetPosition;
				textScaleCurrent = textScaleTarget;

				textAnimationStage = TextAnimationStage::DEACTIVATED;
				textAnimationProgress = 0;
				luAnimation = false;

				// alter pyramid (if necessary)
				if (!luAnimation || gameWon) {
					levelUp();
				}
			}
			else {
				// update text position and scale
				textAnimationProgress += timePerFrame * 1.5;

				ofVec3f newPosition = textStartPosition.getInterpolated(textTargetPosition, textAnimationProgress);
				textCurrentPosition = newPosition;

				ofVec3f newScale = textScaleStart.getInterpolated(textScaleTarget, textAnimationProgress);
				textScaleCurrent = newScale;

				// check if next stage will be the final one
				if (textAnimationProgress >= 0.95) {
					// fill the whole screen with the text
					dynamicMainText->setText("###");
					textScaleCurrent *= 10;
				}
			}

			break;
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
			for (int i = 0; i < maxBalls; i++) balls[i].pause();
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
	if (this->qbert->isDead && this->qbert->lives > 0 && !gameWon && !gameEnd) {
		drawQbert = true;
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
		for (int i = 0; i < maxBalls; i++) balls[i].update();

		// only check collisions if balls are active (spare resources)
		checkBallCollision();
	}

	checkPyramidCollision();


	/* UPDATE CAMERA VARIABLES */
	// ortho view
	isometricCameraDistance = (sqrt(2) * (pyramid->tileSize * pyramid->maxLevel)) * 4; //+ (sqrt(2) * pyramid->tileSize * pyramid->maxLevel * 0.5);
	orthoAdjust = 200;
	orthoRatio = pyramid->maxLevel * (pyramid->tileSize / 1000); //1; //pyramid->tileSize * 0.35 / 50;

	// 3d view
	perspectiveCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel * 1.5);
	lensAngle = 75;
	alpha = 10;
	beta = 1000;

	// first person view
	fpCamera.x = qbert->currentPosition.x;
	fpCamera.y = qbert->currentPosition.y;
	fpCamera.z = qbert->currentPosition.z;

	fpTarget.x = fpTarget.y = fpTarget.z = 0;

	switch (qbert->orientation) {
	case Orientation::LEFT_DOWN:
		fpCamera.y += qbert->size * 3;
		fpCamera.z += qbert->size * 0.5;

		fpTarget.x = fpCamera.x;
		fpTarget.y = fpCamera.y - pyramid->tileSize * pyramid->maxLevel;
		fpTarget.z = fpCamera.z + pyramid->tileSize * pyramid->maxLevel * 0.5;
		break;

	case Orientation::RIGHT_DOWN:
		fpCamera.x += qbert->size * 0.5;
		fpCamera.y += qbert->size * 3;

		fpTarget.x = fpCamera.x + pyramid->tileSize * pyramid->maxLevel * 0.5;
		fpTarget.y = fpCamera.y - pyramid->tileSize * pyramid->maxLevel;
		fpTarget.z = fpCamera.z;
		break;

	case Orientation::LEFT_UP:
		fpCamera.x += qbert->size * 0.5;
		fpCamera.y += qbert->size * 3;

		fpTarget.x = qbert->currentPosition.x - pyramid->tileSize;
		fpTarget.y = qbert->currentPosition.y + pyramid->tileSize * 0.5;
		fpTarget.z = qbert->currentPosition.z;
		break;

	case Orientation::RIGHT_UP:
		fpCamera.y += qbert->size * 3;
		fpCamera.z += qbert->size * 0.5;

		fpTarget.x = qbert->currentPosition.x;
		fpTarget.y = qbert->currentPosition.y + pyramid->tileSize * 0.5;
		fpTarget.z = qbert->currentPosition.z - pyramid->tileSize;
		break;
	}

	/* UPDATE DEBUG VARIABLES */
	debugRotationX += 0.5;
	debugRotationY += 0.5;
	debugRotationZ += 1;

	if (debug) {
		enemyActivated = false;
	}
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
		glViewport(0, 0, gw(), gh());

		perspective(fpLensAngle, fpAlpha, fpBeta);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(fpCamera.x, fpCamera.y, fpCamera.z, fpTarget.x, fpTarget.y, fpTarget.z, 0, 1, 0);
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

	if (gameStart) {
		// game start screen
		glPushMatrix(); {
			drawOpeningScreen_2();
		} glPopMatrix();
	}
	else {
		/* DRAW THE GAME */
		// draw animation text (for level up, game over or game won)
		glPushMatrix(); {
			if (gameEnd || luAnimation) {
				printText();
			}
		} glPopMatrix();


		// draw the game pieces
		glPushMatrix(); {
			glRotated(pyramidShakeAngle, 1, 0, 1);

			for (int i = 0; i < qbert->lives; i++) lives[i].draw();

			for (int i = 0; i < maxBalls; i++) balls[i].draw();

			if (drawQbert) qbert->draw();

			pyramid->draw();

			glScaled(1000, 1000, 1000);
			draw3DAxis();

		} glPopMatrix();

		// draw the game background
		//drawBackground();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// start game menu exit
	if (gameStart) {
		if (key == ' ') {
			gameStart = false;

			luAnimation = true;
			textAnimationStage = TextAnimationStage::START;
			viewType = 0;
			//setupTextAnimation("LEVEL 1", "");
		}
		return;
	}

	// basic debug and view key presses
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

	case 'd':
		debug = !debug;
		break;

	case 'w':
		cheatGame();
		return;

	default:
		break;
	}

	// deactivate key press while level up animation is running
	if (luAnimation) {
		return;
	}

	// reset game
	if (gameOver || gameWon || gameEnd) {
		if (key == 'r') {
			setup();
		}
		return;
	}

	// activate enemy when player moves
	if (key == OF_KEY_UP || key == OF_KEY_DOWN || key == OF_KEY_LEFT || key == OF_KEY_RIGHT) {
		enemyActivated = true;
	}

	// change key press command to match the first person view
	if (viewType == 2) {
		if (qbert->orientation == Orientation::LEFT_DOWN || qbert->orientation == Orientation::RIGHT_DOWN) {
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
		}
		else if (qbert->orientation == Orientation::LEFT_UP || qbert->orientation == Orientation::RIGHT_UP) {
			// do nothing
		}
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

/////////////////////// GAME DYNAMICS //////////////////////////

void ofApp::levelUp() {
	// reset game variables
	gameWon = false;
	luAnimation = false;

	// reset the pyramid for the new level
	pyramid = new Pyramid(currentPyramidLevel, pyramidCubeSize);

	// reset qbert position
	qbert->isDead = true;
	qbert->previousPosition = pyramid->coords[0][0];
	qbert->previousPosition.y += pyramid->tileSize * 0.5 + qbert->size * 0.5;
	qbert->startPosition = qbert->currentPosition = qbert->previousPosition;
	qbert->jumpStartPosition = qbert->previousPosition;
	qbert->previousOrientation = Orientation::LEFT_DOWN;

	// reset lives position
	//lives.clear();
	GLfloat startZ = pyramid->tileSize * pyramid->maxLevel * 0.5;
	GLfloat livesDistance = qbert->size;
	for (int i = 0; i < maxLives; i++) {
		ofVec3f startPos = ofVec3f(-startZ + i * livesDistance, pyramid->tileSize * pyramid->maxLevel, startZ - i * livesDistance);
		//lives.push_back(Qbert(startPos, qbert->size, 0, 0, 0, maxLives));
		lives[i].startPosition = lives[i].previousPosition = lives[i].currentPosition = lives[i].previousPosition = startPos;
	}

	// kill all objects
	for (int i = 0; i < maxBalls; i++) balls[i].isDead = true;
	//for (int i = 0; i < maxLives; i++) lives[i].isDead = true;
}

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
		}
	}
}

void ofApp::checkBallCollision() {
	// collision between ball and qbert
	for (int i = 0; i < maxBalls; i++) {
		if (balls[i].isDead == false && balls[i].isWaiting == false && qbert->currentPosition.distance(balls[i].currentPosition) <= qbert->size * 0.5 + balls[i].size * 0.5) {
			qbert->ballCollision = true;
			balls[i].qbertCollision = true;
		}
	}
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

void ofApp::cheatGame() {
	// win level imeadiately (for debug purposes)
	pyramid->nbrFlippedTiles = pyramid->nbrTotalTiles;
}

///////////////////// GAME ANIMATIONS //////////////////////////

void ofApp::printStartInstructionsConsole() {

	cout << "BASIC CONTROLS:" << endl;
	cout << "\t- 'v' to change view" << endl;
	cout << "\t- 'r' to restart the game" << endl << endl;

	cout << "GAME CONTROLS (for isometric view):" << endl;
	cout << "\t- 'UP' to move RIGHT UP" << endl;
	cout << "\t- 'LEFT' to move LEFT UP" << endl;
	cout << "\t- 'RIGHT' to move RIGHT DOWN" << endl;
	cout << "\t- 'DOWN' to move LEFT DOWN" << endl << endl;

	cout << "DEBUG KEYS:" << endl;
	cout << "\t- 'd' to enable/disable debug mode" << endl;
	cout << "\t- '1' to disable culling" << endl;
	cout << "\t- '2' to enable culling with back face" << endl;
	cout << "\t- '3' to enable culling with front face" << endl;
	cout << "\t- '4' to enable culling with front and back face" << endl;
	cout << "\t- 'g' to change polygon mode to GL_LINE" << endl;
	cout << "\t- 'f' to change polygon mode to GL_FILL" << endl;
	cout << "\t- 'l' to change first person view lens angle" << endl;
	cout << "\t- 'a' to change first person view alpha" << endl;
	cout << "\t- 'b' to change first person view beta" << endl;
	cout << "\t- 'w' to win current level imeadiatly" << endl << endl << endl;
}

void ofApp::printText() {
	glPushMatrix(); {
		glTranslated(textCurrentPosition.x, textCurrentPosition.y, textCurrentPosition.z);
		glRotated(45, 0, 1, 0);
		glRotated(-textRotation, 1, 0, 0);
		glScaled(textScaleCurrent.x, textScaleCurrent.y, textScaleCurrent.z);
		
		/////////////////////////////
		dynamicMainText->draw();

		if (!dynamicSubText->isTextNull()) {
			glPushMatrix(); {
				glTranslated(0, -((dynamicSubText->characterUnitHeight / 2) + 2), 0);
				glScalef(0.4, 0.4, 0.4);
				dynamicSubText->draw();
			} glPopMatrix();
		}
		////////////////////////////

	} glPopMatrix();
}

void ofApp::setupTextAnimation(string mainText, string subText, ofVec3f originPos, ofVec3f targetPos, ofVec3f originScale, ofVec3f targetScale) {
	// define interpolation variables
	textAnimationProgress = 0;
	this->mainText = mainText;
	this->subText = subText;
	dynamicMainText->setText(mainText);
	dynamicSubText->setText(subText);

	// define start position and scale
	textStartPosition = textCurrentPosition = originPos;
	textScaleStart = textScaleCurrent = originScale;

	// define target position and scale
	textTargetPosition = targetPos;
	textScaleTarget = targetScale;
}

// opening screen
// version that uses no glOrtho or view types
void ofApp::drawOpeningScreen() {
	float logoHeight = 200;
	float logoWidth = 600;
	float textSize = 5;

	float textHeight = textSize * this->gameStartText[0].characterUnitHeight;

	float textOffset = 0;
	float textSpacing = textHeight * 2.5;

	glPushMatrix(); {
		// set the text position right
		glTranslatef(gw() / 2, gh() / 2, 0);

		// logo
		glPushMatrix(); {
			glTranslatef(0, -logoHeight, 0);		// move the logo to sit above the middle of the screen line
			glScaled(1, -1, 1);		// flip upside down (because there is no glOrtho)
			glScalef(logoWidth, logoHeight, textSize);
			unitCube();
		} glPopMatrix();

		// text
		glPushMatrix(); {
			//glTranslatef(0, logoHeight * 0.3, 0);		// move the text to sit above the logo

			// text
			for (int i = 0; i < this->gameStartText.size(); i++) {
				glPushMatrix(); {
					glTranslated(0, textOffset, 0);
					glScalef(textSize, textSize, textSize);
					glScaled(1, -1, 1);		// flip upside down (because there is no glOrtho)

					this->gameStartText[i].draw();
				} glPopMatrix();

				if (i == 0) {
					// space key image
					glPushMatrix(); {
						glTranslated(-textHeight * 1.5, textOffset, 0);
						glScalef(textHeight * 5, textHeight * 3, textSize);
						glScaled(1, -1, 1);		// flip upside down (because there is no glOrtho)

						unitCube();
					} glPopMatrix();
				} 
				else if (i == 2) {
					// controls image
					glPushMatrix(); {
						glTranslated(-textHeight * 4.5, textOffset, 0);
						glScalef(textHeight * 5, textHeight * 2, textSize);
						glScaled(1, -1, 1);		// flip upside down (because there is no glOrtho)

						unitCube();
					} glPopMatrix();
				}

				textOffset += textSpacing + textHeight;
			}

		} glPopMatrix();

		// debug axis
		glScaled(1000, 1000, 1000);
		draw3DAxis();

	} glPopMatrix();
}

// opening screen
// version that uses glOrtho and view types to make it sit on top of the pyramid (if it was shown)
void ofApp::drawOpeningScreen_2() {
	// everything is drawn in the center of the screen
	// all letters have a height of 6 units (because they have a height of 6 cube that form each character)
	float textHeight = this->gameStartText[0].characterUnitHeight;
	float charLength = this->gameStartText[0].textUnitLength / this->gameStartText[0].textLength;
	float textOffset = 0;
	float textSpacing = textHeight * 2.5;


	float logoHeight = textHeight * 7;
	float logoWidth = charLength * 45;

	glPushMatrix(); {
		// set the text position right
		glTranslated(textTranslation.x, textTranslation.y, textTranslation.z);
		glRotated(45, 0, 1, 0);
		glRotated(-textRotation, 1, 0, 0);
		glScaled(textScale.x * 0.3, textScale.y * 0.3, textScale.z * 0.3);


		// logo
		glPushMatrix(); {
			glTranslatef(0, logoHeight, 0);		// move the logo to sit above the middle of the screen line
			glScalef(logoWidth, logoHeight, 1);
			unitCube();
		} glPopMatrix();

		// text
		glPushMatrix(); {
			//glTranslatef(0, logoHeight * 0.3, 0);		// move the text to sit above the logo

			// text
			for (int i = 0; i < this->gameStartText.size(); i++) {
				glPushMatrix(); {
					glTranslated(0, -textOffset, 0);

					this->gameStartText[i].draw();
				} glPopMatrix();

				if (i == 0) {
					// space key image
					glPushMatrix(); {
						glTranslated(-textHeight * 1.5, -textOffset, 0);
						glScalef(textHeight * 5, textHeight * 3, 1);

						unitCube();
					} glPopMatrix();
				}
				else if (i == 2) {
					// controls image
					glPushMatrix(); {
						glTranslated(-textHeight * 4.5, -textOffset, 0);
						glScalef(textHeight * 5, textHeight * 2, 1);

						unitCube();
					} glPopMatrix();
				}

				textOffset += textSpacing + textHeight;
			}

		} glPopMatrix();

	} glPopMatrix();
}

void ofApp::drawBackground() {
	float size = pyramid->tileSize * pyramid->maxLevel * 10;

	glPushMatrix(); {
		setColor(CYAN);
		glTranslated(size * 0.44, size * 0.44, size * 0.44);
		glScaled(size, size, size);
		//drawLines();
		unitCubeGrid(10, 10);
	} glPopMatrix();
}