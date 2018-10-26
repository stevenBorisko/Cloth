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

// Window Size
#define HEIGHT 1024
#define WIDTH 1024
#define ASPECT (double)WIDTH / (double)HEIGHT

// Field of view constants
#define EYE_XVAL 2500.0f
#define	EYE_YVAL (double)EYE_XVAL / 3.0f
#define EYE_ZVAL EYE_XVAL

#define FRUSTUM_NEAR (EYE_XVAL / 2.0f)
#define FRUSTUM_FAR (EYE_XVAL * 2.0f)

//----------------------------------------------------------------------------//
// --- Global Variables for Main--- //
//----------------------------------------------------------------------------//

Scene* scene;
Scene* swap;

//----------------------------------------------------------------------------//
// --- Helper Function Declarations--- //
//----------------------------------------------------------------------------//

//------------------------------------//
// --- OpenGL functions --- //
//------------------------------------//

void renderScene(void);
void updateScene(void);
void processNormalKeys(unsigned char key, int x, int y);

//------------------------------------//
// --- Test Scenes --- //
//------------------------------------//

void testScene_00();
void testScene_01();

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
	glutIdleFunc(updateScene);

	scene = new Scene();
	swap = new Scene();
	testScene_00();
	scene->globalGravity = -9.81;

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(
		EYE_XVAL,EYE_YVAL,EYE_ZVAL,
		0.0f,EYE_YVAL,0.0f,
		0.0f,1.0f,0.0f
	);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,ASPECT,FRUSTUM_NEAR,FRUSTUM_FAR);

	scene->draw();

	glutSwapBuffers();
}

void updateScene(void) {
	std::cout << "Frame count: " << scene->tick++ << std::endl;
	scene->update(swap);
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if((key == 27) | (key == 'q')) exit(0);
}

//------------------------------------//
// --- Test Scenes --- //
//------------------------------------//

void testScene_00() {

	// Grid dimensions
	const unsigned int GRID_WIDTH = 20;
	const unsigned int GRID_SPACE = 50;

	// Ball dimensions
	const double BALL_RADIUS = 50;
	const double BALL_MASS = 25;

	Input::Grid(scene, GRID_WIDTH, GRID_SPACE, 0.01, 1);

	Particle* ball_0 = new Particle(
		1,
		Vector4(0,(GRID_SPACE * 50 + BALL_RADIUS)/15.0,GRID_SPACE>>1,0) * (GRID_WIDTH >> 1),
		Vector4(0,0,0,0),
		BALL_MASS,
		BALL_RADIUS
	);
	scene->addParticle(ball_0);
}

void testScene_01() {
	Particle* testParticles[2] = {
		new Particle(1,Vector4(-50,0,0,0),Vector4(0,0,0,0),1,1),
		new Particle(1,Vector4(50,0,0,0),Vector4(0,0,0,0),1,1),
	};
	Binding* testBinding = new Binding(
		testParticles[0], testParticles[1],
		1,0
	);
	scene->addParticle(testParticles[0]);
	scene->addParticle(testParticles[1]);
	scene->addBinding(testBinding);
}
