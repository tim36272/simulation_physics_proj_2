/**
 * @file  simSession.h
 * @brief <b>The Main Simulation Class</b>
 *
 * @author  Gamino/Sweet
 * @ingroup simulation
 */  

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library

#include "../utilities/visualization/camera.h" // For Camera Control Class
#include <time.h>
#include <iostream>
#include "../utilities/math/quaternion.h"
#include "rigid_body.h"
#include <vector>
#include <ctime>

using namespace std;

/* ASCII code for the escape key. */
#define ESCAPE 27
/* ASCII code for the enter key */
#define ENTER 13
const float DELTA_TIME = 0.0005;
const float GRAVITY = 9.81;

class simSession {
	public:
		simSession(int *argc, char **argv); ///<constructs a simSession
		static int window;
		static void InitGL(int Width, int Height); ///< starts GL
		static void DrawGLScene(); ///< draws a frame
		static std::vector<rigid_body> boxes;
		static Quaternion currentRotation;
		static int x_dir,y_dir,z_dir,rotY;
		static bool simulate;
		static bool generated;
		static bool moveOneFrame;
		static double timer;
		static int frameRatePrecision;
	private:
};
