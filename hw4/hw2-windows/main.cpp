/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shaders.h"
#include "Transform.h"
#include <FreeImage.h>
#include "UCB/grader.h"
#include <windows.h>
#include "imageloader.h"

using namespace std ; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp  
void display(void) ;  // prototype for display function.  

Grader grader;
bool allowGrader = false;
int oldx, oldy, xrot, yrot;
float movex = 0.02;
float movey = 0.02;
float movez = 0.1;

float lookz = 1;
float lookrotate = 0.05;



// Uses the Projection matrices (technically deprecated) to set perspective 
// We could also do this in a more modern fashion with glm.  
void reshape(int width, int height){
	w = width;
	h = height;
        mat4 mv ; // just like for lookat

	glMatrixMode(GL_PROJECTION);
        float aspect = w / (float) h, zNear = 0.1, zFar = 99.0 ;
        // I am changing the projection stuff to be consistent with lookat
        if (useGlu) mv = glm::perspective(fovy,aspect,zNear,zFar) ; 
        else {
          mv = Transform::perspective(fovy,aspect,zNear,zFar) ; 
          mv = glm::transpose(mv) ; // accounting for row major 
        }
        glLoadMatrixf(&mv[0][0]) ; 

	glViewport(0, 0, w, h);
}

void saveScreenshot(string fname) {
	int pix = w * h;
	BYTE *pixels = new BYTE[3*pix];	
	glReadBuffer(GL_FRONT);
	glReadPixels(0,0,w,h,GL_BGR,GL_UNSIGNED_BYTE, pixels);

	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	
	std::cout << "Saving screenshot: " << fname << "\n";

	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	delete pixels;
}


void printHelp() {
  std::cout << "\npress 'h' to print this message again.\n" 
       << "press '+' or '-' to change the amount of rotation that\noccurs with each arrow press.\n" 
	    << "press 'i' to run image grader test cases\n"
            << "press 'g' to switch between using glm::lookAt and glm::Perspective or your own LookAt.\n"       
            << "press 'r' to reset the transformations.\n"
            << "press 'v' 't' 's' to do view, translate [default], scale.\n"
			<< "press 'F1-3' to alter lights\n"
			<< "press '1-3' to alter individual objects\n"
            << "press ESC to quit.\n" ;      
}


void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case '+':
		amount++;
		std::cout << "amount set to " << amount << "\n" ;
		break;
	case '-':
		amount--;
		std::cout << "amount set to " << amount << "\n" ; 
		break;
	case 'i':
		if(allowGrader) {
			std::cout << "Running tests...\n";
			grader.runTests();
			std::cout << "Done! [ESC to quit]\n";
		} else {
			std::cout << "Error: no input file specified for grader\n";
		}
		break;
	case 'g':
		useGlu = !useGlu;
                reshape(w,h) ; 
		std::cout << "Using glm::LookAt and glm::Perspective set to: " << (useGlu ? " true " : " false ") << "\n" ; 
		break;
	case 'h':
		printHelp();
		break;
        case 27:  // Escape to quit
                exit(0) ;
                break ;
        case 'r': // reset eye and up vectors, scale and translate. 
		eye = eyeinit ; 
		up = upinit ; 
                //sx = sy = 1.0 ; 
                //tx = ty = tz = 0.0 ; 
		center = centerinit;
		break ;   
        case 'v': 
                transop = view ;
                std::cout << "Operation is set to View\n" ; 
                break ; 
        case 't':
                transop = translate ; 
                std::cout << "Operation is set to Translate\n" ; 
                break ; 
        case 'y':
                transop = scale ; 
                std::cout << "Operation is set to Scale\n" ; 
                break ; 

		case 'w':
				Transform::cam_y(eye, center, movey);
                break ; 

		case 's':
				Transform::cam_y(eye, center, -movey);
                break ; 

		case 'a':
				Transform::cam_x(eye, center, up, -movex);
                break ; 

		case 'd':
				Transform::cam_x(eye, center, up, movex);
                break ; 

		case 'c':
				Transform::cam_z(eye, center, movez);
                break ; 

		case 'x':
				Transform::cam_z(eye, center, -movez);
                break ; 

        case 'o':
                saveScreenshot("screenshot.jpg");
                std::cout << "Screenshot saved" ; 
                break ; 

		case 'p':
                isAnim = !isAnim;
                break ; 
		case 'l':
                useTex = !useTex;
                break ; 
		case '1':
			if (numobjects < 1)
				break;
			else
				type = obj0;
				std::cout << "Type is set to obj0\n" ; 
				break;
		case '2':
			if (numobjects < 2)
				break;
			else
				type = obj1;
				std::cout << "Type is set to obj1\n" ; 
				break;
		case '3':
			if (numobjects < 3)
				break;
			else
				type = obj2;
				std::cout << "Type is set to obj2\n" ; 
				break;
        }
	glutPostRedisplay();
}

//  You will need to enter code for the arrow keys 
//  When an arrow key is pressed, it will call your transform functions

void specialKey(int key, int x, int y) {
	switch(key) {
	case 100: //left
          /*if (transop == view) Transform::left(amount, eye,  up);
          else if (transop == scale) sx -= amount * 0.01 ; 
          else if (transop == translate) tx -= amount * 0.01 ; 
		  else*/ 
		  if (type == light0) lightposn[0] -= amount * 0.01;
		  else if (type == light1) lightposn[4] -= amount * 0.01;
		  else if (type == light2) lightposn[8] -= amount * 0.01;
		  else if (type == obj0) {
			  if (transop == translate)
					objects[0].tx -= amount * 0.01;
			  else if (transop == scale)
					objects[0].sx -= amount * 0.01;
		  }
		  else if (type == obj1) {
			  if (transop == translate)
					objects[1].tx -= amount * 0.01;
			  else if (transop == scale)
					objects[1].sx -= amount * 0.01;
		  }
		  else if (type == obj2) {
			  if (transop == translate)
					objects[2].tx -= amount * 0.01;
			  else if (transop == scale)
					objects[2].sx -= amount * 0.01;
		  }
          break;
	case 101: //up
          /*if (transop == view) Transform::up(amount,  eye,  up);
          else if (transop == scale) sy += amount * 0.01 ; 
          else if (transop == translate) ty += amount * 0.01 ; 
		  else if (transop == zTranslate) tz += amount * 0.01 ;
		  else*/ 
		  if (type == light0) lightposn[2] += amount * 0.01;
		  else if (type == light1) lightposn[6] += amount * 0.01;
		  else if (type == light2) lightposn[10] += amount * 0.01;
		  else if (type == obj0) {
			  if (transop == translate)
					objects[0].tz += amount * 0.01;
			  else if (transop == scale)
					objects[0].sy += amount * 0.01;
		  }
		  else if (type == obj1) {
			  if (transop == translate)
					objects[1].tz += amount * 0.01;
			  else if (transop == scale)
					objects[1].sz += amount * 0.01;
		  }
		  else if (type == obj2) {
			  if (transop == translate)
					objects[2].tz += amount * 0.01;
			  else if (transop == scale)
					objects[2].sz += amount * 0.01;
		  }
          break;
	case 102: //right
          /*if (transop == view) Transform::left(-amount, eye,  up);
          else if (transop == scale) sx += amount * 0.01 ; 
          else if (transop == translate) tx += amount * 0.01 ; 
		  else*/ if (type == light0) lightposn[0] += amount * 0.01;
		  else if (type == light1) lightposn[4] += amount * 0.01;
		  else if (type == light2) lightposn[8] += amount * 0.01;
		  else if (type == obj0) {
			  if (transop == translate)
					objects[0].tx += amount * 0.01;
			  else if (transop == scale)
					objects[0].sx += amount * 0.01;
		  }
		  else if (type == obj1) {
			  if (transop == translate)
					objects[1].tx += amount * 0.01;
			  else if (transop == scale)
					objects[1].sx += amount * 0.01;
		  }
		  else if (type == obj2) {
			  if (transop == translate)
					objects[2].tx += amount * 0.01;
			  else if (transop == scale)
					objects[2].sx += amount * 0.01;
		  }
          break;
	case 103: //down
          /*if (transop == view) Transform::up(-amount,  eye,  up);
          else if (transop == scale) sy -= amount * 0.01 ; 
          else if (transop == translate) ty -= amount * 0.01 ; 
		  else if (transop == zTranslate) tz -= amount * 0.01 ;
		  else*/ if (type == light0) lightposn[2] -= amount * 0.01;
		  else if (type == light1) lightposn[6] -= amount * 0.01;
		  else if (type == light2) lightposn[10] -= amount * 0.01;
		  else if (type == obj0) {
			  if (transop == translate)
					objects[0].tz -= amount * 0.01;
			  else if (transop == scale)
					objects[0].sy -= amount * 0.01;
		  }
		  else if (type == obj1) {
			  if (transop == translate)
					objects[1].tz -= amount * 0.01;
			  else if (transop == scale)
					objects[1].sy -= amount * 0.01;
		  }
		  else if (type == obj2) {
			  if (transop == translate)
					objects[2].tz -= amount * 0.01;
			  else if (transop == scale)
					objects[2].sy -= amount * 0.01;
		  }
          break;
	case GLUT_KEY_F1:
		if (numLights < 1)
			break;
		else
			type = light0;
			std::cout << "Type is set to move light0\n" ; 
			break;
	case GLUT_KEY_F2:
		if (numLights < 2)
			break;
		else
			type = light1;
			std::cout << "Type is set to move light1\n" ; 
			break;
	case GLUT_KEY_F3:
		if (numLights < 3)
			break;
		else
			type = light2;
			std::cout << "Type is set to move light2\n" ; 
			break;
	}
	glutPostRedisplay();
}

void mouse(int x, int y) {
	int midw = w  >> 1;	
	int midh = h >> 1;	
	float angley  = 0.0f;				
	float anglez  = 0.0f;											
	
	if( (x == midw) && (y == midh) ) return;
		
	glutWarpPointer(midw, midh);
	glutSetCursor(GLUT_CURSOR_NONE);
	

	// Get the direction from the mouse, and bring the number down to a reasonable amount
	angley = (float)( (midw - x) ) / 1000;		
	anglez = (float)( (midh - y) ) / 1000;

	// The higher the number(acceleration) is the faster the camera looks around.
	center.z += anglez * 10;

	// limit the rotation around the x-axis
	/*
	if((center.y - eye.y) > 8)  center.y = eye.y + 8;
	if((center.y - eye.y) <-8)  center.y = eye.y - 8;*/
	
	Transform::cam_rotate(eye, center, angley);
}

void showmouse (int x, int y) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

int speartime = 0;
int swordtime = 0;
void animate() {
	if(isAnim) {
		//throw
		if(speartime < 20)
			speartime++;
		else if(spearz > 50) {
			spearz = 0;
			speary = 0;
			speartime = 0;
		} else {
			spearz += 0.2;
			speary += 0.2;
			speartime++;
		}

		//stab
		if (swordtime < 10)
			swordx -= 0.1;
		else
			swordx += 0.1;
		swordtime++;

		if(swordtime > 19)
			swordtime = 0;

		/*if(spearz > 49)
			swordx = 0;*/

		glutPostRedisplay();
	}
}

void init() {
	  // Initialize attenuation to none
	  atten_const = 1.0;
	  atten_linear = 0;
	  atten_quad = 0;
	  // Initialize shaders
      vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
      fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
      shaderprogram = initprogram(vertexshader, fragmentshader) ; 
      enablelighting = glGetUniformLocation(shaderprogram,"enablelighting") ;
	  istex = glGetUniformLocation(shaderprogram,"istex") ;
	  tex = glGetUniformLocation(shaderprogram,"tex") ;
      lightpos = glGetUniformLocation(shaderprogram,"lightposn") ;       
      lightcol = glGetUniformLocation(shaderprogram,"lightcolor") ; 
      numusedcol = glGetUniformLocation(shaderprogram,"numused") ;       
      ambientcol = glGetUniformLocation(shaderprogram,"ambient") ;       
      diffusecol = glGetUniformLocation(shaderprogram,"diffuse") ;       
      specularcol = glGetUniformLocation(shaderprogram,"specular") ;       
      emissioncol = glGetUniformLocation(shaderprogram,"emission");       
      shininesscol = glGetUniformLocation(shaderprogram,"shininess");  
	  attenconst = glGetUniformLocation(shaderprogram, "atten_const");
	  attenlinear = glGetUniformLocation(shaderprogram, "atten_linear");
	  attenquad = glGetUniformLocation(shaderprogram, "atten_quad");
	  numspotval = glGetUniformLocation(shaderprogram, "numSpots");
	  spotdirnval = glGetUniformLocation(shaderprogram, "spot_directions");
	  spotexponentval = glGetUniformLocation(shaderprogram, "spot_exponents");
	  spotcoscutoffval = glGetUniformLocation(shaderprogram, "spot_coscutoffs");
	  spotindexval = glGetUniformLocation(shaderprogram, "spot_indices");
	  numusedval = glGetUniformLocation(shaderprogram, "numused");
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
		exit(-1); 
	}

  	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW2: Scene Viewer");

	GLenum err = glewInit() ; 
	if (GLEW_OK != err) { 
		std::cerr << "Error: " << glewGetString(err) << std::endl; 
	} 
	init();
    readfile(argv[1]) ; 
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(w, h);
	glutIdleFunc(animate);
	glutMotionFunc(mouse);
	glutPassiveMotionFunc(showmouse);
	cerr << "test" << vertices[1].x; 


	if (argc > 2) {
		allowGrader = true;
		stringstream tcid;
		tcid << argv[1] << "." << argv[2];
		grader.init(tcid.str());
		grader.loadCommands(argv[2]);
		grader.bindDisplayFunc(display);
		grader.bindSpecialFunc(specialKey);
		grader.bindKeyboardFunc(keyboard);
		grader.bindScreenshotFunc(saveScreenshot);
	}

	printHelp();
	glutMainLoop();
	FreeImage_DeInitialise();
	return 0;
}
