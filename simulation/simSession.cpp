#include "simSession.h"
#define NUMBER_OF_BOXES 20
#define FALL_AREA 20
#define MAX_VELOCITY 10
#define MAX_A_VELOCITY 20/10.0
#define STEP_SIZE 0.005
#define FRP 10000
Quaternion simSession::currentRotation(3.141526/2,0,0);
std::vector<rigid_body> simSession::boxes;
int simSession::x_dir=0;
int simSession::y_dir=0;
int simSession::z_dir=0;
int simSession::rotY=0;
bool simSession::simulate=false;
bool simSession::generated=false;
bool simSession::moveOneFrame=false;
int simSession::window;
double simSession::timer=0;
int simSession::frameRatePrecision=FRP;

void keyPressed(unsigned char key, int x, int y);

/**
*simSession setups openGL and the enviornment, such as the plane and hold
*
* @brief 
*/
simSession::simSession(int *argc, char **argv) {
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffered for automatic clipping */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  /* get a 640 x 480 window */
  glutInitWindowSize(640, 480);  
  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  
  /* Open a window */  
  window = glutCreateWindow("CS 282 - Project 1");  
	
  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Initialize our window. */
  InitGL(640, 480);
  
  // Ag -- Initialize Camera
  camera Camera1(window);


  /*capture key input for Camera*/
  glutKeyboardFunc( &keyPressed); // 

	// setup camera //
	x_dir=y_dir=z_dir=0;

	// get mouse clicking input
	glutMouseFunc( &camera::MouseClick);

  // Get Mouse dragging input
  glutMotionFunc( &camera::MouseDrag);

  /* Start Event Processing Engine */  
  glutMainLoop();
}

/**
*simSession 
*
* @brief A general OpenGL initialization function.  Sets all of the initial parameters. 
*/
void simSession::InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
		
    // Lighting properties
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    // set the lighting properties
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);			        // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);		        // Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading


  glEnable (GL_LIGHTING);
  glEnable (GL_COLOR_MATERIAL);
  glEnable (GL_LIGHT0);


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
	timer = time(NULL);
}

/**
*simSession 
*
* @brief The main drawing function.
*/
void simSession::DrawGLScene()
{
//cout <<"start frame"<<endl;
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
  glLoadIdentity();																		// Reset The View
  usleep(100);
	if (generated) {
		//frame rate stuff
			frameRatePrecision--;
			if (frameRatePrecision == 0) {
				timer -= time(NULL);
				timer *= -1;
				timer = double(FRP)/timer;
				cout <<"FPS: "<<timer<<endl;
				frameRatePrecision = FRP;
				timer = time(NULL);
			}

		// draw environment and look at it
		glPushMatrix();
		glTranslatef(-10.5,-10,-50);
		  glTranslatef(x_dir,y_dir,z_dir); // this moves the environment around for looking purposes
		  glRotatef(rotY,0.0,1.0,0.0); // this rotates the environment around for looking purposes

		for (unsigned int i=0;i<boxes.size();i++) {
//			if (boxes[i].COM.y<=0.1)
//				boxes.erase(boxes.begin()+i);
			glPushMatrix();

//			glColor3f(1.0f,0.0f,1.0f);
				//do movement
				if (simulate || moveOneFrame) {
						boxes[i].collision = false;
						boxes[i].updateRotation(STEP_SIZE);
						boxes[i].updateVelocity(STEP_SIZE);
						boxes[i].updatePosition(STEP_SIZE);
						for (unsigned int j=0;j<boxes.size();j++) {
							if ((i!=j) && !boxes[i].collision) { // be sure we are not doing collisions with self, this will inteterfere with the erase for step 1
								boxes[i].handleCollisions(boxes[j]);
							}
						}
				}
			if (!boxes[i].collision)
				glColor3f(1.0,1.0,1.0);
			else
				glColor3f(1.0,0.0,0.0);
			boxes[i].draw();
			glPopMatrix();
		}
		moveOneFrame=false;
		glPopMatrix();
	}
		// swap the buffers to display, since double buffering is used.
		glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this call */
    usleep(100);

    /* If escape is pressed, kill everything. */
    switch (key)
    {
        case ESCAPE:
        {
            /* shut down our window */
            glutDestroyWindow(simSession::window);

            /* exit the program...normal termination. */
            exit(0);
            break;
        }
        case 'w':
        {
            simSession::z_dir+= 1.0;
            break;
        }
        case 's':
        {
            simSession::z_dir-= 1.0;
            break;
        }
        case 'a':
        {
            simSession::x_dir+= 3.5;
            break;
        }
        case 'd':
        {
            simSession::x_dir-= 3.5;
            break;
        }
        case '2':
        {
            simSession::y_dir -= 1.0;
            break;
        }
        case 'x':
        {
            simSession::y_dir += 1.0;
            break;
        }
        case 'q':
        {
            simSession::rotY -= 1.5;
            break;
        }
        case 'e':
        {
            simSession::rotY +=1.5;
            break;
        }
        // generate a new set of circles when user hits enter
        case ENTER: case '0':
        {
           // delete old vector
            simSession::boxes.clear();

						//make boxes
						srand(time(NULL));

						for (int i=0;i<NUMBER_OF_BOXES;i++) {
//							double edgeLength = rand()%3+1;
							double edgeLength = 2;
							vec thisCenter(rand()%FALL_AREA,rand()%FALL_AREA,rand()%FALL_AREA);
//							vec thisCenter(i*3+1,1,1);
//cout <<"Center: "<<thisCenter.x<<","<<thisCenter.y<<","<<thisCenter.z<<" edge length: "<<edgeLength<<endl;
							vec thisLinearVelocity((rand()%MAX_VELOCITY-5.0)/20.0,(rand()%MAX_VELOCITY-5.0)/20.0,(rand()%MAX_VELOCITY-5.0)/20.0);
//							vec thisLinearVelocity((i+9001)%2,0,0);
//							vec thisLinearVelocity(0,0,0);

							vec thisAngularVelocity(rand()%MAX_A_VELOCITY/10.0,rand()%MAX_A_VELOCITY/10.0,rand()%MAX_A_VELOCITY/10.0);
//							vec thisAngularVelocity(0,0,0);
							simSession::boxes.push_back(rigid_body(thisCenter,edgeLength,thisLinearVelocity,thisAngularVelocity));
						}

/*						vec thisCenter(1,1,1);
						vec thisLinearVelocity(0,5,0);
						vec thisAngularVelocity(0,0,0);
						simSession::boxes.push_back(rigid_body(thisCenter,2,thisLinearVelocity,thisAngularVelocity));
						thisLinearVelocity.set(0,0,0);
						thisCenter.set(1,10,1);
						simSession::boxes.push_back(rigid_body(thisCenter,2,thisLinearVelocity,thisAngularVelocity));

						thisCenter.set(4,1,1);
						thisLinearVelocity.set(5,0,0);
						simSession::boxes.push_back(rigid_body(thisCenter,2,thisLinearVelocity,thisAngularVelocity));
						thisLinearVelocity.set(0,0,0);
						thisCenter.set(8,1,1);
						simSession::boxes.push_back(rigid_body(thisCenter,2,thisLinearVelocity,thisAngularVelocity));
*/
            simSession::generated = true;
            simSession::simulate = false;
            break;
        }
				//step frame by frame
				case 'f':
				{
						simSession::moveOneFrame=true;
				}
        case '1':
        {
/*            for (int j = 0; j < NUM_CIRCLES; j++)
            {
                for (int k = 0; k < NUM_CIRCLES; k++)
                {
                    if (j !=k)
                    {
                        
                        if (circles[j].sphere2sphere(circles[j], circles[k]));
                        {
                            k = NUM_CIRCLES;
                        }
                    }
                }

            }*/
            break;
        }
        case ' ':
        {
            // call collision detection
            simSession::simulate = !simSession::simulate;
            break;
        }
    }

}
