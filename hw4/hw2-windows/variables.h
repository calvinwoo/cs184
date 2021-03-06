/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif 

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 
EXTERN vec3 center;
EXTERN float spearx, speary, spearz;
EXTERN float swordx, swordy, swordz;
EXTERN bool isAnim;


#ifdef MAINPROGRAM 
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 centerinit(0.0,0.0,0.0) ; // Center look at point 
int w = 1000, h = 700 ; // width and height 
float fovy = 90.0 ; // For field of view
#else 
EXTERN vec3 eyeinit ; 
EXTERN vec3 upinit ; 
EXTERN vec3 centerinit ; 
EXTERN int w, h ; 
EXTERN float fovy ; 
#endif 

EXTERN bool useGlu; // Toggle use of "official" opengl/glm transform vs user 
EXTERN bool useTex;
EXTERN GLuint vertexshader, fragmentshader, shaderprogram ; // shaders
static enum {translate, view, scale, zTranslate} transop ; // which operation to transform 
static enum {light0, light1, light2, obj0, obj1, obj2} type;
enum shape {cube, sphere, teapot, tri} ;
//EXTERN float sx, sy ; // the scale in x and y 
//EXTERN float tx, ty, tz ; // the translation in x and y

EXTERN int numvertex;
EXTERN vec3 vertices[10];

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ; 
EXTERN GLfloat lightposn [4*numLights] ; // Light Positions
EXTERN GLfloat lightcolor[4*numLights] ; // Light Colors
EXTERN GLfloat lightransf[4*numLights] ; // Lights transformed by modelview
// Spotlight params
EXTERN GLfloat spotdirections[3*numLights];
EXTERN GLfloat spotcoscutoffs[numLights];
EXTERN GLfloat spotexponents[numLights];
EXTERN GLfloat spotindices[numLights];
EXTERN int numSpots;

// Array storing the indices of the spotlights. Necessary global variable
//because we cannot pass in structs to shaders
EXTERN int numused ;              // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN GLfloat ambient[4] ; 
EXTERN GLfloat diffuse[4] ; 
EXTERN GLfloat specular[4] ; 
EXTERN GLfloat emission[4] ; 
EXTERN GLfloat shininess ; 

// Attenuation (read from file)
// Intialized to no attenuation
EXTERN GLfloat atten_const ;
EXTERN GLfloat atten_linear ;
EXTERN GLfloat atten_quad ;


// For multiple objects, read from a file.  
const int maxobjects = 30 ; 
EXTERN int numobjects ; 
EXTERN struct object {
  shape type ; 
  GLfloat size ;
  GLfloat ambient[4] ; 
  GLfloat diffuse[4] ; 
  GLfloat specular[4] ;
  GLfloat emission[4] ; 
  GLfloat shininess ;
  mat4 transform ; 
  float tx, ty, tz;
  float sx, sy, sz;
  vec3 vert1;
  vec3 vert2;
  vec3 vert3;
} objects[maxobjects] ;

// Variables to set uniform params for lighting fragment shader 
EXTERN GLuint lightcol ; 
EXTERN GLuint lightpos ; 
EXTERN GLuint numusedcol ; 
EXTERN GLuint enablelighting ; 
EXTERN GLuint istex ; 
EXTERN GLuint tex ;
EXTERN GLuint ambientcol ; 
EXTERN GLuint diffusecol ; 
EXTERN GLuint specularcol ; 
EXTERN GLuint emissioncol ; 
EXTERN GLuint shininesscol ; 
EXTERN GLuint attenconst ;
EXTERN GLuint attenlinear ;
EXTERN GLuint attenquad ;
// Shader information for spotlights
EXTERN GLuint numspotval ;
EXTERN GLuint spotdirnval ;
EXTERN GLuint spotcoscutoffval ;
EXTERN GLuint spotexponentval ;
EXTERN GLuint spotindexval;
EXTERN GLuint numusedval;

