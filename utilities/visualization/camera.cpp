/**
 * @file  camera.cpp
 * @brief <b>Inmplementation of camera.h </b>
 *
 * @author  Gamino/Sweet
 * @ingroup utilities - visualization
 */  

#include "camera.h"
#include <iostream>
#include <fstream>
using namespace std;
// Initialization

double camera::QW;
double camera::QX;
double camera::QY;
double camera::QZ;

int camera::window;

float camera::InX; // Define In Vector
float camera::InY;
float camera::InZ;

float camera::clickX; // Mouse x/y Position
float camera::clickY;
float camera::changeX;
float camera::changeY;
float camera::changeZ;

// Class Functions

/**
*Camera keypress catcher
*
* @brief catches user input to act on
*/
void camera::KeyPress( unsigned char key, int x, int y )
	{
	switch ( key ) { // Control Camera Movment Via Keyboard
		//arrow keys
		case 'w':
			changeY--;
		break;
		case 's':
			changeY++;
		break;
		case 'a':
			changeX--;
		break;
		case 'd':
			changeX++;
		break;
//		case 'q':
//			changeZ--;
//		break;
//		case 'e':
//			changeZ++;
//		break;
        // Special Cases
	case 27: // Esc key
		ofstream fout;
		fout.open( "Quats.txt" );
		fout << QW << ',' << QX << ',' << QY << ',' << QZ;
		fout.close();
		glutDestroyWindow(window);
	break;
	   }
	}
/**
*Camera mousedrag
*
* @brief supports view changing using the mouse
*/
void camera::MouseDrag( int Xpos, int Ypos ) {
	changeX = float(Xpos)-clickX;
	changeY = (float(Ypos)-clickY);
//	clickX = Xpos;
//	clickY = Ypos;
}

void camera::readIn() {
	ifstream fin;
	fin.open("Quats.txt");
	char dummy;
	fin >> QW >>dummy>>QX>>dummy>>QY>>dummy>>QZ;
}

