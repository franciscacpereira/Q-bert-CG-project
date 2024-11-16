#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	glEnable(GL_DEPTH_TEST);	// makes the objets closer to the camera appear in front of the others (even if they are drawn later)
	ofBackground(18, 18, 23);
	glLineWidth(5);

	// init debug variables
	debugRotationX = 0;
	debugRotationY = 0;
	debugRotationZ = 0;

	// init game variables
	pyramid = new Pyramid(7, 50);
	qbert = new Qbert(pyramid);

	// init camera variables
	viewType = 0;

	isometricCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel);
	orthoAdjust = 200;
	orthoRatio = pyramid->tileSize * 0.35 / 50;

	perspectiveCameraDistance = sqrt(2) * (pyramid->tileSize * pyramid->maxLevel) + (pyramid->tileSize * pyramid->maxLevel * 1.5);
	lensAngle = 75;
	alpha = 10;
	beta = 1000;
}

//--------------------------------------------------------------
void ofApp::update(){
	// update debug variables
	debugRotationX += 0.5;
	debugRotationY += 0.5;
	debugRotationZ += 1;

	// update camera variables

	// update game variables
	qbert->update();
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
		lookat(perspectiveCameraDistance / 4, perspectiveCameraDistance / 3, perspectiveCameraDistance / 2, 0, pyramid->tileSize * (pyramid->maxLevel / 4), 0, 0, 1, 0);
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
	qbert->draw();
	pyramid->draw();

	glScaled(1000, 1000, 1000);
	draw3DAxis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
