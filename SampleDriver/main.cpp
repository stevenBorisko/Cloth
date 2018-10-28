#include <stdlib.h>
#include <stdio.h>
#include <argp.h>

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
#include "Cloth/src/Physics/Physics.hpp"

#define FRAMES_PER_SECOND 60

// Window Size
#define HEIGHT 512
#define WIDTH 512
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
FILE* ffmpeg;
int* buffer;
bool recording;

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

//------------------------------------//
// --- Helper Functons --- //
//------------------------------------//

void exitProgram();

//----------------------------------------------------------------------------//
// --- Main--- //
//----------------------------------------------------------------------------//

static int parse_opt(int key, char* arg, struct argp_state* state) {
	switch(key) {
	case 'r':
		recording = true;
		break;
	default:
		break;
	}
	return 0;
}

int main(int argc, char** argv) {

	// Initialize global variables
	scene = nullptr;
	swap = nullptr;
	ffmpeg = nullptr;
	buffer = {0};
	recording = false;

	// Parse arguments
	struct argp_option options[] = {
		{ 0, 'r', 0, 0, "record screen capture" },
		{ 0 }
	};
	struct argp argp = { options, parse_opt };
	argp_parse(&argp, argc, argv, 0, 0, 0);

	// Initialize OpenGL stuff
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Test Window");

	glutDisplayFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(updateScene);

	// Create scene
	scene = new Scene();
	swap = new Scene();
	testScene_00();
	scene->globalGravity = -9.81;

	// Open pipe to ffmpeg
	if(recording) {
		const char* _cmd = "ffmpeg -r %d -f rawvideo -pix_fmt rgba -s %dx%d -i - "
			"-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip output.mp4";
		char cmd[256];
		sprintf(cmd, _cmd, FRAMES_PER_SECOND, WIDTH, HEIGHT);
		ffmpeg = popen(cmd, "w");
		buffer = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
	}

	// Get er goin
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

	// Capture frame, but not all of them
	if(
		recording
		&& !(scene->tick % ((TICKS_PER_SECOND / FRAMES_PER_SECOND) << 3))
	) {
		glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		fwrite(buffer, sizeof(int)*WIDTH*HEIGHT, 1, ffmpeg);
	}

}

void updateScene(void) {
	//std::cout << "Frame count: " << scene->tick++ << std::endl;
	++scene->tick;
	scene->update(swap);
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if((key == 27) | (key == 'q')) exitProgram();
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

	Input::Grid(scene, GRID_WIDTH, GRID_SPACE, 0.01, 0.5);

/*
	Particle* ball_0 = new Particle(
		1,
		Vector4(0,(GRID_SPACE * 50 + BALL_RADIUS)/15.0,GRID_SPACE>>1,0) * (GRID_WIDTH >> 1),
		Vector4(0,0,0,0),
		BALL_MASS,
		BALL_RADIUS
	);
	scene->addParticle(ball_0);
*/
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

//------------------------------------//
// --- Helper Functons --- //
//------------------------------------//

void exitProgram() {
	if(recording) pclose(ffmpeg);
	exit(0);
}
