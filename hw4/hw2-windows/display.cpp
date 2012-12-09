/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This file is display.cpp.  It includes the skeleton for the display routine

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h"
#include "windows.h"
#include <stdio.h> 
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include "imageloader.h"
#include "glm.h"


using namespace std ; 
#include "variables.h"
#include "readfile.h"

GLuint _textureId;
GLuint _textureId2;

GLMmodel* f16;
int displayList=0;

// New helper transformation function to transform vector by modelview 
// May be better done using newer glm functionality.
// Provided for your convenience.  Use is optional.  
// Some of you may want to use the more modern routines in readfile.cpp 
// that can also be used.  


void transformvec (const GLfloat input[4], GLfloat output[4]) {
  GLfloat modelview[16] ; // in column major order
  glGetFloatv(GL_MODELVIEW_MATRIX, modelview) ; 
  
  for (int i = 0 ; i < 4 ; i++) {
    output[i] = 0 ; 
    for (int j = 0 ; j < 4 ; j++) 
      output[i] += modelview[4*j+i] * input[j] ; 
  }
}

void DrawWall(float transx,float transy,float transz,float scalex,float scaley,float scalez) {
	glUniform1i(istex, useTex);

	glPushMatrix();
	glTranslatef(transx, transy, transz);
	glScalef(scalex, scaley, scalez);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glUniform1i(istex, false);
}

void DrawGround(float transx,float transy,float transz,float scalex,float scaley,float scalez) {
	glUniform1i(istex, useTex);

	glPushMatrix();
	glTranslatef(transx, transy, transz);
	glScalef(scalex, scaley, scalez);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glUniform1i(istex, false);
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void display() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	Image* image = loadBMP("stone.bmp");
	_textureId = loadTexture(image); 

	image = loadBMP("dirt.bmp");
	_textureId2 = loadTexture(image); 

	image = loadBMP("dirt.bmp");
	delete image;

	
	/*f16 = (GLMmodel*)malloc(sizeof(GLMmodel));
	f16 = glmReadOBJ("objs/f16.obj");
	
	displayList=glGenLists(1);
	glNewList(displayList,GL_COMPILE);
		glmDraw(f16, GLM_SMOOTH);
	glEndList();
	free(f16);*/


	glClearColor(0, .3, .8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // I'm including the basic matrix setup for model view to 
        // give some sense of how this works.  

	glMatrixMode(GL_MODELVIEW);
	mat4 mv ; 
	useGlu = true;

        if (useGlu) mv = glm::lookAt(eye,center,up) ; 
	else {
          mv = Transform::lookAt(eye,center,up) ; 
          mv = glm::transpose(mv) ; // accounting for row major
        }
        glLoadMatrixf(&mv[0][0]) ; 

        // Set Light and Material properties for the teapot
        // Lights are transformed by current modelview matrix. 
        // The shader can't do this globally. 
        // So we need to do so manually.  
		
        if (numused) {
          glUniform1i(enablelighting,true) ;
		  glUniform1f(attenconst, atten_const);
		  glUniform1f(attenlinear, atten_linear);
		  glUniform1f(attenquad, atten_quad);

          // YOUR CODE FOR HW 2 HERE.  
          // You need to pass the lights to the shader. 
          // Remember that lights are transformed by modelview first.  

		  for(int i = 0; i < 4*numLights; i = i + 4) {
			  GLfloat temp [4] = {lightposn[i], lightposn[i+1], lightposn[i+2], lightposn[i+3]};
			  GLfloat temp2 [4] = {};
			  transformvec(temp, temp2);
			  lightransf[i] = temp2[0];
			  lightransf[i+1] = temp2[1];
			  lightransf[i+2] = temp2[2];
			  lightransf[i+3] = temp2[3];
		  }
		  glUniform4fv(lightpos, numLights, lightransf);
		  glUniform4fv(lightcol, numLights, lightcolor);
		  // Specific spotlight values
		  glUniform1fv(spotindexval, numLights, spotindices) ;
		  glUniform3fv(spotdirnval, numLights, spotdirections);
		  glUniform1i(numspotval, numSpots);
		  glUniform1fv(spotexponentval, numLights, spotexponents);
		  glUniform1fv(spotcoscutoffval, numLights, spotcoscutoffs);
		  glUniform1i(numusedval, numused);
        }
        else glUniform1i(enablelighting,false) ; 

		glUniform1i(istex, false);
		glUniform1i(tex, 0) ;
		

        // Transformations for objects, involving translation and scaling 
        mat4 sc(1.0) , tr(1.0), transf(1.0) ; 
        /*sc = Transform::scale(sx,sy,1.0) ; 
        tr = Transform::translate(tx,ty,tz) ;*/

        // YOUR CODE FOR HW 2 HERE.  
        // You need to use scale, translate and modelview to 
        // set up the net transformation matrix for the objects.  
        // Account for GLM issues etc.  
		transf =  mv * tr * sc;
		glLoadMatrixf(&transf[0][0]) ;

		glPushMatrix();
			glTranslatef(0, 0, 13);
			glScalef(.1, .1, .1);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
			glCallList(displayList);
		glPopMatrix();

		GLfloat array[] = {1,1,1,1};
		glUniform4fv(specularcol, 1, array);
		glUniform1f(shininesscol, 100); 

		/*
		DrawWall(0, 1.8, 2, 5.9, 0.1, 2);	//back left
		DrawWall(-6, 0, 2.0, 0.1, 1.9, 2);	//left
		DrawWall(3.8, 0.2, 5.9, 0.1, 2.1, 1.9);	//middle
		DrawWall(6.0, 0.2, 3.9, 0.1, 2.1, 4.0);	//far right
		DrawWall(-1.1, 0, 4, 4.9, 2, 0.1);	//roof
		DrawWall(4.8, 2, 6, 1.2, 0.1, 2);	//tower wall
		DrawWall(4.9, -0.4, 7, 1.1, 1.4, 0.1);	//tower roof
		DrawWall(0, -2, 2, 6.2, 0.1, 2);	//front
		DrawWall(4.8, -1.9, 3.7, 1.4, 0.1, 3.4);	//front tower
		
		DrawGround(0, 0, 0, 15, 15, 0.1);	//ground

		//guy bottom left attacker
		glPushMatrix();
			glTranslatef(-3, -.5, 1.25); 
			glutSolidSphere(0.2, 20, 20) ; 
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-3, -.5, 0.6); 
			glScalef(1 ,1, 1.7);
			glutSolidCube(0.5) ; 
		glPopMatrix();

		//guy bottom left
		glPushMatrix();
			glTranslatef(-4, -0.3, 1.25); 
			glutSolidSphere(0.2, 20, 20) ; 
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-4, -0.3, 0.6); 
			glScalef(1 ,1, 1.7);
			glutSolidCube(0.5) ; 
		glPopMatrix();

		//sword
		glPushMatrix();
			glTranslatef(-3.3 + swordx, -.1, 1.0); 
			//glRotatef(45, -1, 1, 0);
			glScalef(3.4, 0.2, 0.2);
			glutSolidCube(0.5) ; 
		glPopMatrix();
		
		//guy top
		glPushMatrix();
			glTranslatef(4.5, -.5, 8.65); 
			glutSolidSphere(0.2, 20, 20) ; 
		glPopMatrix();

		glPushMatrix();
			glTranslatef(4.5, -.5, 8); 
			glScalef(1 ,1, 1.7);
			glutSolidCube(0.5) ; 
		glPopMatrix();

		//spear1
		glPushMatrix();
			glTranslatef(4.3, -.4 - speary, 8.7 - spearz); 
			glRotatef(45, 1, 0, 0);
			glScalef(0.2, 3, 0.2);
			glutSolidCube(0.5) ; 
		glPopMatrix();

		//guy outside
		glPushMatrix();
			glTranslatef(4.5, -6, 1.25); 
			glutSolidSphere(0.2, 20, 20) ; 
		glPopMatrix();

		glPushMatrix();
			glTranslatef(4.5, -6, 0.6); 
			glScalef(1 ,1, 1.7);
			glutSolidCube(0.5) ; 
		glPopMatrix();

		//spear2
		glPushMatrix();
			glTranslatef(4.7, -6 + speary, 1.95 + 1.4*spearz); 
			glRotatef(45, 1, 0, 0);
			glScalef(0.2, 3, 0.2);
			glutSolidCube(0.5) ; 
		glPopMatrix();*/


        for (int i = 0 ; i < numobjects ; i++) {
          object * obj = &(objects[i]) ; 

          {
          // YOUR CODE FOR HW 2 HERE. 
          // Set up the object transformations 
          // And pass in the appropriate material properties

			glUniform4fv(ambientcol, 1, obj->ambient);
			glUniform4fv(diffusecol, 1, obj->diffuse);
			glUniform4fv(specularcol, 1, obj->specular);
			glUniform4fv(emissioncol, 1, obj->emission);
			glUniform1f(shininesscol, obj->shininess); 

			mat4 transformation = transf * glm::transpose(obj->transform);
			glLoadMatrixf(&transformation[0][0]);
          }

          // Actually draw the object
          // We provide the actual glut drawing functions for you.  
          if (obj -> type == cube) {
            glutSolidCube(obj->size) ; 
          }
          else if (obj -> type == sphere) {
            const int tessel = 20 ; 
            glutSolidSphere(obj->size, tessel, tessel) ; 
          }
          else if (obj -> type == teapot) {
            glutSolidTeapot(obj->size) ; 
          }
		  else if (obj -> type == tri) {
			  glBegin(GL_TRIANGLES);
				  glVertex3f(obj->vert1.x, obj->vert1.y,  obj->vert1.z);
				  glVertex3f(obj->vert2.x, obj->vert2.y, obj->vert2.z);
				  glVertex3f(obj->vert3.x, obj->vert3.y, obj->vert3.z);
			  glEnd();
		  }

        }
        glutSwapBuffers();
}