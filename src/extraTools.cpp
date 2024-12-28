// extraTools.cpp - Main file for the file containing all extra tools

// Author: Francisca Pereira
// Student ID: 2022213550
// Version: 1.0

#include "extraTools.h"

// function to get screen width
float gw() {
	return ofGetWidth();
}

// function to get screen height
float gh() {
	return ofGetHeight();
}

// function to put Frame Rate as window title
void setFrWt() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

// function to get a random integer between min and max
int getRandomInt(int min, int max) {
	if (min > max) std::swap(min, max);

	std::random_device randomDevice;
	std::default_random_engine generator(randomDevice());
	std::uniform_real_distribution<> distribution(min, max);

	return static_cast<int>(distribution(generator));
}

// function to get a random float between min and max
float getRandomFloat(float min, float max) {
	if (min > max) std::swap(min, max);

	std::random_device randomDevice;
	std::default_random_engine generator(randomDevice());
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(generator);
}

// print ModelView Matrix
void coutModelviewMatrix() {
	GLfloat Matriz[4][4];
	cout << endl << "Modelview Matrix" << endl;
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Matriz[j][i] << " ";
		}
		cout << endl;
	}
	//return;
}

// function to get the cross of two vectors
ofVec3f cross(ofVec3f A, ofVec3f B) {
	ofVec3f aux;
	aux.x = A.y * B.z - A.z * B.y;
	aux.y = A.z * B.x - A.x * B.z;
	aux.z = A.x * B.y - A.y * B.x;

	return aux;
}

// function to draw an object filled
void drawFilled() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// function to draw an object non-filled
void drawLines() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// function to draw a point
void drawPoint() {
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
}

// function to draw the 3D axis
void draw3DAxis() {
	glBegin(GL_LINES);
	// x = red
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	// y = green
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	// z = blue
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

// function to draw a unit square
void unitSquare() {
	float p = 0.5;
	glBegin(GL_QUADS); {
		glNormal3f(0, 0, 1);
		glVertex3f(-p, -p, 0);
		glVertex3f(-p, p, 0);
		glVertex3f(p, p, 0);
		glVertex3f(p, -p, 0);
	} glEnd();
}

// function to draw a unit circle
void unitCircle() {
	GLint nbrFaces = 30;
	GLfloat radius = 0.5;
	GLfloat angle = (2 * PI) / nbrFaces;
	ofVec3f center = ofVec3f(0, 0, 0);

	glBegin(GL_POLYGON); {
		glNormal3f(0, 0, 1);
		for (int i = 0; i < nbrFaces; i++) {
			GLfloat xCircle = center[0] + radius * cos(angle * i);
			GLfloat zCircle = center[2] + radius * sin(angle * i);
			glVertex3f(xCircle, center[1], zCircle);
		}
	} glEnd();
}

// function to draw a circle in the center (0, 0, 0)
// parameters: radius and number of faces
void drawCircle(GLfloat radius, GLint nbrFaces) {
	GLfloat angle = (2 * PI) / nbrFaces;
	ofVec3f center = ofVec3f(0, 0, 0);

	glBegin(GL_POLYGON); {
		glNormal3f(0, 0, 1);
		for (int i = 0; i < nbrFaces; i++) {
			GLfloat xCircle = center[0] + radius * cos(angle * i);
			GLfloat zCircle = center[2] + radius * sin(angle * i);
			glVertex3f(xCircle, center[1], zCircle);
		}
	} glEnd();
}

// function to draw a unit cube
// cube visualization:
//         8 ------- 5
//        /|        /|
//       / |       / |
//      1 ------- 4  |
//      |  7 ------- 6
//      | /       | /
//      |/        |/
//      2 ------- 3
void unitCube() {
	float p = 0.5;
	glBegin(GL_QUADS); {

		// front (z is positive)
		glNormal3f(0, 0, 1);
		glVertex3f(-p, -p, p);	    // 1
		glVertex3f(-p, p, p);	    // 2
		glVertex3f(p, p, p);        // 3
		glVertex3f(p, -p, p);	    // 4

		// back (z is negative)
		glNormal3f(0, 0, -1);
		glVertex3f(p, -p, -p);		// 5
		glVertex3f(p, p, -p);		// 6
		glVertex3f(-p, p, -p); 	    // 7
		glVertex3f(-p, -p, -p);		// 8

		// top (y is negative)
		glNormal3f(0, 1, 0);
		glVertex3f(-p, -p, -p);		// 8
		glVertex3f(-p, -p, p);		// 1
		glVertex3f(p, -p, p);		// 4
		glVertex3f(p, -p, -p);		// 5

		// bottom (y is positive)
		glNormal3f(0, -1, 0);
		glVertex3f(-p, p, p);		// 2
		glVertex3f(-p, p, -p);		// 7
		glVertex3f(p, p, -p);		// 6
		glVertex3f(p, p, p);		// 3

		// left (x is negative)
		glNormal3f(-1, 0, 0);
		glVertex3f(-p, -p, -p);		// 8
		glVertex3f(-p, p, -p);		// 7
		glVertex3f(-p, p, p);		// 2
		glVertex3f(-p, -p, p);		// 1

		// right (x is positive)
		glNormal3f(1, 0, 0);
		glVertex3f(p, -p, p);		// 4
		glVertex3f(p, p, p);		// 3
		glVertex3f(p, p, -p);		// 6
		glVertex3f(p, -p, -p);		// 5

	} glEnd();
}


// function to draw a unit cube that allows for texture usage
// cube visualization:
//         8 ------- 5
//        /|        /|
//       / |       / |
//      1 ------- 4  |
//      |  7 ------- 6
//      | /       | /
//      |/        |/
//      2 ------- 3
void unitTextureCube(GLint tilingFactor, bool frontOnly) {
	float p = 0.5;
	glBegin(GL_QUADS); {

		// front (z is positive)
		glNormal3f(0, 0, 1);

		glTexCoord2f(0, 0);
		glVertex3f(-p, -p, p);	    // 1
		glTexCoord2f(0, 1 * tilingFactor);
		glVertex3f(-p, p, p);	    // 2
		glTexCoord2f(1 * tilingFactor, 1 * tilingFactor);
		glVertex3f(p, p, p);        // 3
		glTexCoord2f(1 * tilingFactor, 0);
		glVertex3f(p, -p, p);	    // 4

		if (frontOnly) {
			// back (z is negative)
			glNormal3f(0, 0, -1);
			glVertex3f(p, -p, -p);		// 5
			glVertex3f(p, p, -p);		// 6
			glVertex3f(-p, p, -p); 	    // 7
			glVertex3f(-p, -p, -p);		// 8

			// top (y is negative)
			glNormal3f(0, 1, 0);
			glVertex3f(-p, -p, -p);		// 8
			glVertex3f(-p, -p, p);		// 1
			glVertex3f(p, -p, p);		// 4
			glVertex3f(p, -p, -p);		// 5

			// bottom (y is positive)
			glNormal3f(0, -1, 0);
			glVertex3f(-p, p, p);		// 2
			glVertex3f(-p, p, -p);		// 7
			glVertex3f(p, p, -p);		// 6
			glVertex3f(p, p, p);		// 3

			// left (x is negative)
			glNormal3f(-1, 0, 0);
			glVertex3f(-p, -p, -p);		// 8
			glVertex3f(-p, p, -p);		// 7
			glVertex3f(-p, p, p);		// 2
			glVertex3f(-p, -p, p);		// 1

			// right (x is positive)
			glNormal3f(1, 0, 0);
			glVertex3f(p, -p, p);		// 4
			glVertex3f(p, p, p);		// 3
			glVertex3f(p, p, -p);		// 6
			glVertex3f(p, -p, -p);		// 5
		} 
		else {
			// back (z is negative)
			glNormal3f(0, 0, -1);

			glTexCoord2d(0, 0);
			glVertex3f(p, -p, -p);		// 5
			glTexCoord2d(0, 1 * tilingFactor);
			glVertex3f(p, p, -p);		// 6
			glTexCoord2d(1 * tilingFactor, 1 * tilingFactor);
			glVertex3f(-p, p, -p); 	    // 7
			glTexCoord2d(1 * tilingFactor, 0);
			glVertex3f(-p, -p, -p);		// 8

			// top (y is negative)
			glNormal3f(0, 1, 0);

			glTexCoord2d(0, 0);
			glVertex3f(-p, -p, -p);		// 8
			glTexCoord2d(0, 1 * tilingFactor);
			glVertex3f(-p, -p, p);		// 1
			glTexCoord2d(1 * tilingFactor, 1 * tilingFactor);
			glVertex3f(p, -p, p);		// 4
			glTexCoord2d(1 * tilingFactor, 0);
			glVertex3f(p, -p, -p);		// 5

			// bottom (y is positive)
			glNormal3f(0, -1, 0);

			glTexCoord2d(0, 0);
			glVertex3f(-p, p, p);		// 2
			glTexCoord2d(0, 1 * tilingFactor);
			glVertex3f(-p, p, -p);		// 7
			glTexCoord2d(1 * tilingFactor, 1 * tilingFactor);
			glVertex3f(p, p, -p);		// 6
			glTexCoord2d(1 * tilingFactor, 0);
			glVertex3f(p, p, p);		// 3

			// left (x is negative)
			glNormal3f(-1, 0, 0);

			glTexCoord2d(0, 0);
			glVertex3f(-p, -p, -p);		// 8
			glTexCoord2d(0, 1 * tilingFactor);
			glVertex3f(-p, p, -p);		// 7
			glTexCoord2d(1 * tilingFactor, 1 * tilingFactor);
			glVertex3f(-p, p, p);		// 2
			glTexCoord2d(1 * tilingFactor, 0);
			glVertex3f(-p, -p, p);		// 1

			// right (x is positive)
			glNormal3f(1, 0, 0);

			glTexCoord2d(0, 0);
			glVertex3f(p, -p, p);		// 4
			glTexCoord2d(0, 1 * tilingFactor);
			glVertex3f(p, p, p);		// 3
			glTexCoord2d(1 * tilingFactor, 1 * tilingFactor);
			glVertex3f(p, p, -p);		// 6
			glTexCoord2d(1 * tilingFactor, 0);
			glVertex3f(p, -p, -p);		// 5
		}

	} glEnd();
}


// function to draw a unit sphere
void unitSphere() {
	GLint m = 20;
	GLint n = 20;
	GLfloat radius = 0.5;
	GLfloat d_theta = 2.0f * 3.1415926 / m;  // incremental step for theta
	GLfloat d_phi = 3.1415926 / n;           // incremental step for phi

	glBegin(GL_QUADS); {
		for (int i = 0; i < n; ++i) {
			GLfloat phi0 = i * d_phi;
			GLfloat phi1 = (i + 1) * d_phi;

			for (int j = 0; j < m; ++j) {
				GLfloat theta0 = j * d_theta;
				GLfloat theta1 = (j + 1) * d_theta;

				// coordinates for the four vertices of the quad
				// vertex 0 (theta0, phi0)
				GLfloat x0 = radius * sinf(phi0) * cosf(theta0);
				GLfloat y0 = radius * cosf(phi0);
				GLfloat z0 = radius * sinf(phi0) * sinf(theta0);

				// vertex 1 (theta1, phi0)
				GLfloat x1 = radius * sinf(phi0) * cosf(theta1);
				GLfloat y1 = radius * cosf(phi0);
				GLfloat z1 = radius * sinf(phi0) * sinf(theta1);

				// vertex 2 (theta1, phi1)
				GLfloat x2 = radius * sinf(phi1) * cosf(theta1);
				GLfloat y2 = radius * cosf(phi1);
				GLfloat z2 = radius * sinf(phi1) * sinf(theta1);

				// vertex 3 (theta0, phi1)
				GLfloat x3 = radius * sinf(phi1) * cosf(theta0);
				GLfloat y3 = radius * cosf(phi1);
				GLfloat z3 = radius * sinf(phi1) * sinf(theta0);

				// specify normals and vertices for the quad
				// vertex 0
				glNormal3f(x0 / radius, y0 / radius, z0 / radius);
				glVertex3f(x0, y0, z0);

				// vertex 1
				glNormal3f(x1 / radius, y1 / radius, z1 / radius);
				glVertex3f(x1, y1, z1);

				// vertex 2
				glNormal3f(x2 / radius, y2 / radius, z2 / radius);
				glVertex3f(x2, y2, z2);

				// vertex 3
				glNormal3f(x3 / radius, y3 / radius, z3 / radius);
				glVertex3f(x3, y3, z3);
			}
		}
	} glEnd();
}


// function to draw a sphere at center (0, 0, 0)
// size: radius of the sphere
// m: number of subdivisions along the longitude (theta)
// n: number of subdivisions along the latitude (phi)
void drawSphere(GLint m, GLint n, GLfloat radius) {
	GLfloat d_theta = 2.0f * 3.1415926 / m;  // incremental step for theta
	GLfloat d_phi = 3.1415926 / n;           // incremental step for phi

	glBegin(GL_QUADS); {
		for (int i = 0; i < n; ++i) {
			GLfloat phi0 = i * d_phi;
			GLfloat phi1 = (i + 1) * d_phi;

			for (int j = 0; j < m; ++j) {
				GLfloat theta0 = j * d_theta;
				GLfloat theta1 = (j + 1) * d_theta;

				// coordinates for the four vertices of the quad
				// vertex 0 (theta0, phi0)
				GLfloat x0 = radius * sinf(phi0) * cosf(theta0);
				GLfloat y0 = radius * cosf(phi0);
				GLfloat z0 = radius * sinf(phi0) * sinf(theta0);

				// vertex 1 (theta1, phi0)
				GLfloat x1 = radius * sinf(phi0) * cosf(theta1);
				GLfloat y1 = radius * cosf(phi0);
				GLfloat z1 = radius * sinf(phi0) * sinf(theta1);

				// vertex 2 (theta1, phi1)
				GLfloat x2 = radius * sinf(phi1) * cosf(theta1);
				GLfloat y2 = radius * cosf(phi1);
				GLfloat z2 = radius * sinf(phi1) * sinf(theta1);

				// vertex 3 (theta0, phi1)
				GLfloat x3 = radius * sinf(phi1) * cosf(theta0);
				GLfloat y3 = radius * cosf(phi1);
				GLfloat z3 = radius * sinf(phi1) * sinf(theta0);

				// specify normals and vertices for the quad
				// vertex 0
				glNormal3f(x0 / radius, y0 / radius, z0 / radius);
				glVertex3f(x0, y0, z0);

				// vertex 1
				glNormal3f(x1 / radius, y1 / radius, z1 / radius);
				glVertex3f(x1, y1, z1);

				// vertex 2
				glNormal3f(x2 / radius, y2 / radius, z2 / radius);
				glVertex3f(x2, y2, z2);

				// vertex 3
				glNormal3f(x3 / radius, y3 / radius, z3 / radius);
				glVertex3f(x3, y3, z3);
			}
		}
	} glEnd();
}


void drawCylinder(float bottomRadius, float topRadius, float height, int nbrFaces) {
	// calculate the angle increment for each segment
	float angleIncrement = 2.0 * PI / nbrFaces;

	glBegin(GL_TRIANGLE_STRIP); {
		for (int i = 0; i <= nbrFaces; i++) {
			// calculate angle for this segment
			float angle = i * angleIncrement;

			// calculate x and z coordinates for the bottom and top vertices
			float xBottom = bottomRadius * cos(angle);
			float zBottom = bottomRadius * sin(angle);
			float xTop = topRadius * cos(angle);
			float zTop = topRadius * sin(angle);

			// calculate normals for bottom and top vertices
			float nx = cos(angle);
			float nz = sin(angle);

			// adjust normal's y-component based on the slope of the cylinder's side
			float slope = (bottomRadius - topRadius) / height;
			float ny = -slope / sqrt(1 + slope * slope);

			// normalize the vector (nx, ny, nz)
			float length = sqrt(nx * nx + ny * ny + nz * nz);
			nx /= length;
			ny /= length;
			nz /= length;

			// specify normals and vertices for bottom and top
			// bottom
			glNormal3f(nx, ny, nz);
			glVertex3f(xBottom, 0.0, zBottom);

			// top
			glNormal3f(nx, ny, nz);
			glVertex3f(xTop, height, zTop);
		}
	} glEnd();

	// bottom base
	glPushMatrix(); {
		glTranslated(0, 0, 0);
		drawCircle(bottomRadius, nbrFaces);
	} glPopMatrix();

	// top base
	glPushMatrix(); {
		glTranslated(0, height, 0);
		drawCircle(topRadius, nbrFaces);
	} glPopMatrix();

	/*
	// draw the bottom base
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);   // center of bottom base
	for (int i = 0; i <= segments; i++) {
		float angle = i * angleIncrement;
		float x = bottomRadius * cos(angle);
		float z = bottomRadius * sin(angle);
		glVertex3f(x, 0.0f, z);
	}
	glEnd();

	// draw the top base
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, height, 0); // center of top base
	for (int i = 0; i <= segments; i++) {
		float angle = i * angleIncrement;
		float x = topRadius * cos(angle);
		float z = topRadius * sin(angle);
		glVertex3f(x, height, z);
	}
	glEnd();
	*/
}

// draw unitary grid with m x n squares
void unitGrid(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS); {
		glNormal3f(0, 0, 1);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				glVertex2d(i * x_step + x_start, j * y_step + y_start);
				glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
				glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
				glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
			}
		}
	} glEnd();
}

// draw unitary grid in cube with unitGrid()
void unitCubeGrid(GLint m, GLint n) {

	// top
	glColor3f(0, 0, 1);				// use to have a different color in each face
	glPushMatrix(); {
		glTranslated(0., -0.5, 0.);		// move up in y axis
		glRotated(90, 1, 0, 0);
		unitGrid(m, n);
	} glPopMatrix();

	// bottom
	glColor3f(0, 1, 0);
	glPushMatrix(); {
		glTranslated(0., 0.5, 0);		// move down in y axis
		glRotated(270, 1, 0, 0);
		unitGrid(m, n);
	} glPopMatrix();

	// left
	glColor3f(1, 0, 0);
	glPushMatrix(); {
		glTranslated(-0.5, 0., 0.);		// move left in x axis
		glRotated(270, 0, 1, 0);
		unitGrid(m, n);
	} glPopMatrix();

	// right
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(0.5, 0., 0.);		// move right in x axis
	glRotated(90, 0, 1, 0);
	unitGrid(m, n);
	glPopMatrix();

	// back
	glColor3f(1, 0, 1);
	glPushMatrix(); {
		glTranslated(0., 0., -0.5);		// move back in z axis
		glRotated(180, 0, 1, 0);
		unitGrid(m, n);
	} glPopMatrix();

	// front
	glColor3f(0, 1, 1);
	glPushMatrix(); {
		glTranslated(0., 0., 0.5);		// move front in z axis
		// ...                          // no need to rotate
		unitGrid(m, n);
	} glPopMatrix();
}
