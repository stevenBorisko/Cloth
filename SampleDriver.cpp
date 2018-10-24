#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "Cloth/src/DataStructures/Scene/Scene.hpp"
#include "Cloth/src/Input/Input.hpp"

#define HEIGHT 512
#define WIDTH 512

//----------------------------------------------------------------------------//
// --- Helper Function Declarations--- //
//----------------------------------------------------------------------------//

//------------------------------------//
// --- OpenGL functions --- //
//------------------------------------//

void renderScene(void);
void processNormalKeys(unsigned char key, int x, int y);
void changeSize(int w, int h);

//------------------------------------//
// --- Test Scenes --- //
//------------------------------------//

void testScene_00(Scene* scene);

//----------------------------------------------------------------------------//
// --- Main--- //
//----------------------------------------------------------------------------//

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Test Window");

	glutDisplayFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);

	glutMainLoop();

	return 0;
}

//----------------------------------------------------------------------------//
// --- Helper Function Implementation--- //
//----------------------------------------------------------------------------//

//------------------------------------//
// --- OpenGL functions --- //
//------------------------------------//

void renderScene(void) {
	static float angle = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(
		0.0f,0.0f,10.0f,
		0.0f,0.0f, 0.0f,
		0.0f,1.0f, 0.0f
	);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0,-2.0,0.0);
	glVertex3f(2.0,0.0,0.0);
	glVertex3f(0.0,2.0,0.0);
	glEnd();

	angle += 1.0f;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if(key == 27) exit(0);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

//------------------------------------//
// --- Test Scenes --- //
//------------------------------------//

void testScene_00(Scene* scene) {

	const unsigned int GRID_WIDTH = 20;
	const unsigned int GRID_SPACE = 50;
	const float BALL_RADIUS = 100;
	const float BALL_MASS = 20;

	Input::Grid(scene, GRID_WIDTH, GRID_SPACE, 1, 10);
	Particle* ball_0 = new Particle(
		1,
		Vector4(0,BALL_RADIUS*2.0,GRID_SPACE>>1,0) * (GRID_WIDTH >> 1),
		Vector4(0,0,0,0),
		BALL_MASS,
		BALL_RADIUS
	);

	scene->addParticle(ball_0);
}
