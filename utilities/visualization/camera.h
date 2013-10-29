/**
 * @file  camera.h
 * @brief <b>A 3D Camera Class</b>
 * 
 * @author  Gamino/Sweet
 * @ingroup utilities - visualization
 */  



#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <fstream>
#ifndef GEOMETRY
#define GEOMETRY
#include "../../simulation/geometry.h"
#endif
using namespace std;

class camera {
	public:
	camera(int inWindow) {window = inWindow;}
	~camera() {}

	// Check for Keyboard Input
	void static KeyPress( unsigned char, int, int ); ///< receives user input

	// Check for Mouse Input
	void static MouseDrag( int, int );///< drives movement in response to mouse drag
	void static MouseClick(int button, int state, int x, int y) { clickX = x; clickY = y;}

	// Read In and Write Out Camera Coordinates From File
	void static ReadIn(bool);///< reads in parameters from a file
	void static WriteOut();///< writes parameters to a file
	void static readIn();

	// Mouse Position
	static float clickX;
	static float clickY;
	static float changeX;
	static float changeY;
	static float changeZ;

	static double QW,QX,QY,QZ;

	// In Vector
	static float InX;
	static float InY;
	static float InZ;

	// Constants
	static const float Pi = 3.14159265;

	// Varibles
	static int window;

};
