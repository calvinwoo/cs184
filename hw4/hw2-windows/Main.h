#ifndef _MAIN_H
#define _MAIN_H


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <fstream>
#include <vector>									
#include <crtdbg.h>
using namespace std;


#define MAXTEXTURE 100


//////////////////////////////////////
//The tVector3 Struct
//////////////////////////////////////
typedef struct tVector3					// expanded 3D vector struct
{			
	tVector3() {}	// constructor
	tVector3 (float new_x, float new_y, float new_z) // initialize constructor	 
	{x = new_x; y = new_y; z = new_z;}
	// overload + operator so that we easier can add vectors
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator that we easier can subtract vectors
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator that we easier can multiply by scalars
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator that we easier can divide by a scalar
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;						// 3D vector coordinates
}tVector3;

//////////////////////////////////////
//The tVector2 Struct
//////////////////////////////////////											
struct tVector2 
{
	float x, y;							// 2D vector coordinates
};



//////////////////////////////////////
//The Global Variables
//////////////////////////////////////
extern	HDC			hDC;			// Device Context
extern	HGLRC		hRC;			// Permanent Rendering Context
extern	HWND		hWnd;			// Holds Our Window Handle
extern	HINSTANCE	hInstance;		// Holds The Instance Of The Application



#endif

//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com