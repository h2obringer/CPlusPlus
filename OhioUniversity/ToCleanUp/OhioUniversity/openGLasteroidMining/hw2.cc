//************************************************************************
//
// Program: hw2 - Practice picking and selection of objects
//
// Author: Randal M. Obringer
// Email: ro120908@ohio.edu
//
// Professor: David M. Chelberg
//
// Description: This is an implementation of the computer game: Asteroid Mining.
//    Users must click asteroids on the screen. If the asteroid is mineable for 
//    minerals, the user recieves points for the score. If an asteroid hits the 
//    ship it is a game over and the ship will blow up. As your score increases,
//    the number of asteroids will increase as well...
//
// Last Updated: 12 October 2011
//
//************************************************************************ 

#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <list>
#include <math.h>
#include "bitmap.h"		// Enables reading in simple image files
#include "directory.h"          // Enables reading a directory of files

using namespace std;

int winh=500;
int winw=500;

#define CIRCLE 360 //degrees in a full circle
#define ADDSCORE 10 //increment to add to score when mining asteroids
#define SHIPHORIZONTAL 0.5 //collision boundary on bottom with respect to the ship
#define SHIPBOTTOM -1.5 //collision boundary on bottom with respect to the ship
#define SHIPTOP 2.5 //collision boundary on top with respect to the ship
#define XYAXIS 0 //do not rotate x or y axis during rotation transformations
#define ZAXIS 1 //rotate around the z axis during rotation transformations
#define SCREENPERSPECTIVE 15.0 //change world coordinate system from (-1 to 1,-1 to 1) to (-15 to 15,-15 to 15)
#define SLEEPTIME 10 //amount of time to display start/help message
#define LEVELONE 50 //score needed to add an additional asteroid
#define LEVELTWO 100 //score needed to add an additional asteroid
#define LEVELTHREE 200 //score needed to add an additional asteroid
#define LEVELFOUR 250 //score needed to add an additional asteroid
#define STEEP 0.001 //controls how fast asteroids move horizontally/vertically across the screen
#define SLIGHT 0.0004 //controls how fast asteroids move horizontally/vertically across the screen
#define SPIN  0.03 //controls how fast all asteroids spin
#define XYSCALE 4.0 //scale x and y by this much for explosion of ship
#define ZSCALE 1.0 //keep scaling of z the same for explosion of ship
#define SIZE 512 // Something big enough to hold any number of hit
		 // records that is likely to occur. Used with the buffer
		 // for processing hits
#define SIZE2 5 //size of the char array used to display the score

int score=0; //running score of the game

int random_number; //used to pick random positions of asteroids for the game
int ship_rotincr; //controls the rotational transformation of the space ship
bool paused=false; //is the game paused?
bool lose=false; //have you lost yet?
bool starting=true; //have you displayed the start menu upon start up?
float collide_left_bound=-SHIPHORIZONTAL; //left collision boundary between ship and asteroids
float collide_right_bound=SHIPHORIZONTAL; //right collision boundary between ship and asteroids
float collide_top_bound=SHIPTOP; //top collision boundary between ship and asteroids
float collide_bottom_bound=SHIPBOTTOM; //bottom collision boundary between ship and asteroids

/*  texture data */

#define MAX_NUM_TEXTURES 20 //max number of textures loadable from file for use in program

int NUM_TEXTURES=0; //number of textures actually loaded into the proghram from file
BITMAPINFO *TexInfo[MAX_NUM_TEXTURES]; /* Texture bitmap information */
GLubyte    *TexBits[MAX_NUM_TEXTURES]; /* Texture bitmap pixel bits */

#define COLOREDPEBBLES 4 /*allow correct easy use of textures that are loaded from */
#define CRACKED 1 /*    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
#define CRACKEDPAINT 8/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV */
#define STORMY 2 
#define EXTREMECRACKED 5
#define LINED 13 
#define CONCRETESTONES 11
#define VIVIDCRACKED 12 
#define RED 0 
#define FIRE 10
#define LADYOFTHELAKE 3
#define CRAZED 9
#define WATER 7			    /* (continued from above)       */
#define WETROCKS 6                  /* the textures folder provided */

GLint WRAP_S=GL_REPEAT; /* V SPECIFY EXACTLY HOW TO TEXTURE OBJECTS  V  */
GLint WRAP_T=GL_REPEAT;
GLint MAG_FILTER=GL_LINEAR;
GLint MIN_FILTER=GL_LINEAR;
GLint TEXTURE_ENV=GL_REPLACE;
GLint PERSPECTIVE_HINT=GL_NICEST; /* ^ SPECIFY EXACTLY HOW TO TEXTURE OBJECTS ^  */

/* picking data */

enum Object {SHIP=1, MINEABLE, USELESS1, MINEABLE2, USELESS3, USELESS4, 
		QUADRANT1,QUADRANT2,QUADRANT3,QUADRANT4,QUADRANT5,
		QUADRANT6,QUADRANT7,QUADRANT8}; //ALL POSSIBLE TYPES OF OBJECTS

/* BEGIN ASTEROID SPECIFIC DATA */
//each variable controls certain aspects of how each individual asteroid moves
//allows for each asteroid to be rotating/moving independently of other asteroids

/* mineable asteroids data */
bool mine_present=false; //is asteroid present on screen?
bool mineable=true; //if originally mineable, have you mind it or not?
float mine_trans_x; //movement horizontally
float mine_trans_y; //movement vertically
float mine_start_x; //starting x coordinate on border of screen
float mine_start_y; //starting y coordinate on border of screen
float mine_rotincr=0; //rotation (will be set to SPIN however each asteroid will start spinning at different times)

/* useless1 asteroids data */
bool u1_present=false;
float u1_trans_x;
float u1_trans_y;
float u1_start_x;
float u1_start_y;
float u1_rotincr=0;

/*useless2 asteroids data */
bool mine2_present=false;
bool mineable2=true;
float mine2_trans_x;
float mine2_trans_y;
float mine2_start_x;
float mine2_start_y;
float mine2_rotincr=0;

/*useless3 asteroids data */
bool u3_present=false;
float u3_trans_x;
float u3_trans_y;
float u3_start_x;
float u3_start_y;
float u3_rotincr=0;

/*useless4 asteroids data */
bool u4_present=false;
float u4_trans_x;
float u4_trans_y;
float u4_start_x;
float u4_start_y;
float u4_rotincr=0;

/* END ASTEROID SPECIFIC DATA */


/* data for all objects in program */
GLfloat vertices[][3] = {/*start squares coordinates*/{-1.0,-1.0,0.0},{1.0,-1.0,0.0},
			 {1.0,1.0,0.0}, {-1.0,1.0,0.0},/*end squares*//*start background*/ {0.0,0.0,0.0}, 
			 {-7.5,15.0,0.0}, {7.5,15.0,0.0}, {15.0,7.5,0.0},
			 {15.0,-7.5,0.0}, {7.5,-15.0,0.0}, {-7.5,-15.0,0.0},
			 {-15.0,-7.5,0.0},{-15.0,7.5,0.0},{15.0,15.0,0.0},
			 {15.0,-15.0,0.0},{-15.0,-15.0,0.0},{-15.0,15.0,0.0}/*end background*/};


//***********************************************************************
//
// Function: convert_int_to_string
//
// Purpose: convert an integer into a string 
//
// Paramaters: n, an integer
//
// Calls: None
//
//***********************************************************************
string convert_int_to_string(int n){
	ostringstream out;
	out << n;
	return out.str();
}

//***********************************************************************
//
// Function: polygon
//
// Purpose: easily construct a square from a set of pre-defined vertices
//    and render them with a texture. This function is used in the octal function
//    to help create asteroids.
//
// Paramaters: a,b,c, and d - integers that will decide which indices of the 
//    array to use to correctly draw a square
//
// Calls: None
//
//***********************************************************************
void polygon(int a,int b,int c,int d){
	// draw a polygon via list of vertices
	glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glTexCoord2f(0, 0);
		glVertex3fv(vertices[b]);
		glTexCoord2f(1, 0);
		glVertex3fv(vertices[c]);
		glTexCoord2f(1, 1);
		glVertex3fv(vertices[d]);
		glTexCoord2f(0, 1);
	glEnd();
}

//***********************************************************************
//
// Function: triangle
//
// Purpose: easily construct a triangle from a set of pre-defined vertices
//    and render them black. Primarily used in the draw_background function
//    to allow picking of different quadrants on the screen.This is to give the ship
//    angles to rotate in the direction of the mouse.
//
// Paramaters: a,b, and c - integers that will decide which indices of the 
//    array to use to correctly draw a square
//
// Calls: None
//
//***********************************************************************
void triangle(int a,int b,int c){
	// draw a triangle via list of vertices
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0); //use black
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

//***********************************************************************
//
// Function: draw_octal
//
// Purpose: easily construct an octahedron from a set of pre-defined vertices
//    and render them with a texture. Used to draw asteroids and explosions.
//
// Paramaters: None
//
// Calls: polygon - used twice to create an 8 pointed shape
//
//***********************************************************************
void draw_octal( void ){
	polygon(1,0,3,2);
	glRotatef(CIRCLE/8.0,XYAXIS,XYAXIS,ZAXIS); //45
	polygon(1,0,3,2);
	glRotatef(-CIRCLE/8.0,XYAXIS,XYAXIS,ZAXIS); //-45
}

//***********************************************************************
//
// Function: my_init
//
// Purpose: initializes the texture, screen, and fill color specifications
//    for the program. 
//
// Paramaters: None
//
// Calls: read_directory - read in a file of textures to load into the 
//    program.
//        LoadDIBitmap - load the specifications from each bitmap picture
//    for use as textures in the program
//
//***********************************************************************
void my_init( void ){
	/* attributes */
	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-SCREENPERSPECTIVE, SCREENPERSPECTIVE, -SCREENPERSPECTIVE, SCREENPERSPECTIVE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Define the 2D texture image.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, TEXTURE_ENV);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, PERSPECTIVE_HINT);

	list<string> filelist; //all files in the directory
	list<string> imageFileList; // just the bmp files

	filelist = read_directory("textures/"); //read in the texture directory
	for (list<string>::iterator li= filelist.begin(); li != filelist.end(); ++li) {
		// Filter for .bmp files.
		if ((li->rfind(".bmp")!=-1)&&
			(li->rfind(".bmp")==(li->length()-4))) {
			imageFileList.push_back("textures/" + *li);
		}
	}
	// At this point imageFileList has a list of all the bmp files in
	// the directory.

	// Load in the texture map - must be 2^m by 2^n (all files should be 128x128)
	const char *files[MAX_NUM_TEXTURES];
	NUM_TEXTURES=imageFileList.size();
	list<string>::iterator li= imageFileList.begin();
	for (size_t i=0; i<NUM_TEXTURES; ++i) {
		files[i]=li->c_str();
		cout << files[i] << endl;
		++li;
	}
		 
	for (size_t i=0; i<NUM_TEXTURES;++i){
		TexBits[i] = LoadDIBitmap(files[i], &TexInfo[i]);
	}

	/* Enable texture to be used */
	glEnable(GL_TEXTURE_2D);
}

//***********************************************************************
//
// Function: my_idle
//
// Purpose: while nothing is being done by the user, this function keeps the 
//    objects moving on the screen to allow smooth game play. 
//
// Paramaters: None
//
// Calls: glutPostRedisplay
//
//***********************************************************************
void my_idle( void ){
	glutPostRedisplay();
}

//***********************************************************************
//
// Function: shift_collide_left
//
// Purpose: mutates global variables to change the area set for collision
//    with the ship. Orients that area to the area of the ship when it is
//    facing left.
//
// Paramaters: None
//
// Calls: None
//
//***********************************************************************
void shift_collide_left( void ){
	ship_rotincr=-(3.0*CIRCLE)/4.0; //-270 degrees
	collide_left_bound=-SHIPTOP;
	collide_right_bound=-SHIPBOTTOM;
	collide_bottom_bound=-SHIPHORIZONTAL;
	collide_top_bound=SHIPHORIZONTAL;
}

//***********************************************************************
//
// Function: shift_collide_right
//
// Purpose: mutates global variables to change the area set for collision
//    with the ship. Orients that area to the area of the ship when it is
//    facing right.
//
// Paramaters: None
//
// Calls: None
//
//***********************************************************************
void shift_collide_right( void ){
	ship_rotincr=-CIRCLE/4.0; //-90 degrees
	collide_left_bound=SHIPBOTTOM;
	collide_right_bound=SHIPTOP;
	collide_bottom_bound=-SHIPHORIZONTAL;
	collide_top_bound=SHIPHORIZONTAL;
}

//***********************************************************************
//
// Function: shift_collide_up
//
// Purpose: mutates global variables to change the area set for collision
//    with the ship. Orients that area to the area of the ship when it is
//    facing up.
//
// Paramaters: None
//
// Calls: None
//
//***********************************************************************
void shift_collide_up( void ){
	ship_rotincr=0;
	collide_left_bound=-SHIPHORIZONTAL;
	collide_right_bound=SHIPHORIZONTAL;
	collide_bottom_bound=SHIPBOTTOM;
	collide_top_bound=SHIPTOP;
}

//***********************************************************************
//
// Function: shift_collide_down
//
// Purpose: mutates global variables to change the area set for collision
//    with the ship. Orients that area to the area of the ship when it is
//    facing down.
//
// Paramaters: None
//
// Calls: None
//
//***********************************************************************
void shift_collide_down( void ){
	ship_rotincr=CIRCLE/2.0; //180 degrees
	collide_left_bound=-SHIPHORIZONTAL;
	collide_right_bound=SHIPHORIZONTAL;
	collide_bottom_bound=SHIPBOTTOM;
	collide_top_bound=SHIPTOP;
}

//***********************************************************************
//
// Function: processHits - Created by E. Angel, Interactive Computer Graphics
//    A Top-Down Approach with OpenGL, Third Edition. Addison-Wesley Longman, 2003.
//    Modified by David Chelberg for readablility and further modified by 
//    Randal M. Obringer (me) for use in this program.
//
// Purpose: Allows the user to pick and distinguish between objects on the screen
//    to allow the game to operate correctly and make it fun to play. Allows the user
//    to mine mineable asteroids, destroy asteroids, and rotate the ship.
//
// Paramaters: GLint hits - the number of different objects the user has clicked
//    on at a certain moment in time. 
//             GLuint buffer[] - the identification data that distinguishes which 
//    object is being processed
//
// Calls: None
//
//***********************************************************************
void processHits (GLint hits, GLuint buffer[]){
/* Each hit record has the following (and note it is of variable length):

   Number of names in the name stack for this hit record
   Minimum depth value of primitives (range 0 to 232-1)
   Maximum depth value of primitives (range 0 to 232-1)
   Name stack contents (one name for each unsigned int).*/

	unsigned int i, j;
	GLuint names, *ptr;
	ptr = (GLuint *) buffer; 
	for (i = 0; i < hits; i++) {	/*  for each hit  */
		names = *ptr;
		ptr+=3;
		for (j = 0; j < names; j++) { /*  for each name */
			switch (*ptr) {
				case SHIP:
					break;
				case MINEABLE:
					if((paused==false)&&(lose==false)){
						if(mineable==true){
							score+=ADDSCORE;
						}
						if(mineable==false){
							mine_present=false;
							mineable=true;
						}else{
							mineable=false;
						}
					}
					break;
				case USELESS1:
					if((paused==false)&&(lose==false)){
						u1_present=false;
					}
					break;
				case MINEABLE2:
					if((paused==false)&&(lose==false)){
						if(mineable2==true){
							score+=(2*ADDSCORE);
						}
						if(mineable2==false){
							mine2_present=false;
							mineable2=true;
						}else{
							mineable2=false;
						}
					}
					break;
				case USELESS3:
					if((paused==false)&&(lose==false)){
						u3_present=false;
					}
					break;
				case USELESS4:
					if((paused==false)&&(lose==false)){
						u4_present=false;
					}
					break;
				case QUADRANT1:
					shift_collide_up();
					break;
				case QUADRANT2:
					ship_rotincr=-CIRCLE/8.0; //-45 degrees
					break;
				case QUADRANT3:
					shift_collide_right();
					break;
				case QUADRANT4:
					ship_rotincr=-(3.0*CIRCLE)/8.0; //-135 degrees
					break;
				case QUADRANT5:
					shift_collide_down();
					break;
				case QUADRANT6:
					ship_rotincr=-(5.0*CIRCLE)/8.0; //-225 degrees
					break;
				case QUADRANT7:
					shift_collide_left();
					break;
				case QUADRANT8:
					ship_rotincr=-(7.0*CIRCLE)/8.0; //-315 degrees
					break;
				default:
					break;
			}
			ptr++;
		}
	}
}

//***********************************************************************
//
// Function: draw_background
//
// Purpose: Fills the background of the screen completely black but also
//    splits up the screen into 8 quadrants that all radiate from the center
//    of the screen. This allows for the user to pick each quadrant and
//    orient the ship to that quadrant in which the user clicked. 
//
// Paramaters: GLenum mode - allows the user to render the object or select 
//    it for picking.
//             int Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8 - will be an enumerated type, 
//    allowing the user to put an identification to each quadrant of the 
//    screen.
//
// Calls: triangle - draw triangles to split up the screen. Some quadrants
//    take two traingles to draw.
//
//***********************************************************************
void draw_background(GLenum mode,int Q1,int Q2,int Q3,int Q4,int Q5,int Q6,int Q7,int Q8){
	if(mode == GL_SELECT){
		glLoadName(Q1);
	}
	triangle(4,5,6);
	if(mode == GL_SELECT){
		glLoadName(Q2);
	}
	triangle(4,6,7);
	triangle(6,13,7);
	if(mode == GL_SELECT){
		glLoadName(Q3);
	}
	triangle(4,7,8);
	if(mode == GL_SELECT){
		glLoadName(Q4);
	}
	triangle(4,8,9);
	triangle(8,14,9);
	if(mode == GL_SELECT){
		glLoadName(Q5);
	}
	triangle(4,9,10);
	if(mode == GL_SELECT){
		glLoadName(Q6);
	}
	triangle(4,10,11);
	triangle(10,15,11);
	if(mode == GL_SELECT){
		glLoadName(Q7);
	}
	triangle(4,11,12);
	if(mode == GL_SELECT){
		glLoadName(Q8);
	}
	triangle(4,12,5);
	triangle(12,16,5);
}


//***********************************************************************
//
// Function: draw_asteroid
//
// Purpose: draws asteroids. This part of the overloaded function draws
//    mineable asteroids in specific. It manipulates asteroid specific data
//    to give it its motion and rotation that will be independent of any other
//    asteroid created. All that is needed to to create new asteroid specific
//    global variables in order to effectively add another type of asteroid
//    to the program. 
//
// Paramaters: GLenum mode - allows the user to render the object or select 
//    it for picking.
//             int type - will be an enumerated object, used to give the asteroid
//    an identity.
//             float &rot - the asteroid specific rotation data
//             float &tran_x - the asteroid specific horizontal movement speed
//             float &tran_y - the asteroid specific vertical movement speed
//             float &start_x - the starting x coordinate as well as the current 
//    horizontal position of the asteroid.
//             float &start_y - the starting y coordinate as well as the current
//    vertical position of the asteroid. 
//             bool &present - allows for destruction and recreation of the asteroid
//             bool &P - allows for the asteroid to react to a paused game
//             bool &L - allows for the asteroid to react to a game over
//             const int TEX - gives the asteroid its texture after being mined
//             const int TEX2 - gives the asteroid its texture before being mined
//             bool &M - tells if the asteroid is still mineable or not
//
// Calls: draw_octal - give the asteroid the shape of an octahedron
//
//***********************************************************************
void draw_asteroid(GLenum mode, /*enum type*/int type, float &rot, float &tran_x, float &tran_y,
	float &start_x, float &start_y, bool &present, bool &P,bool &L,const int TEX,const int TEX2, bool &M){
	
	if(mode == GL_SELECT){
		glLoadName(type);
	}
	if((P==false)&&(L==false)){
		rot+=SPIN;
		if(rot>CIRCLE-1){
			rot-=CIRCLE;
		}
		start_x+=tran_x;
		start_y+=tran_y;
	}
	glTranslatef(start_x,start_y,0);
	glRotatef(rot,XYAXIS,XYAXIS,ZAXIS);
	if(M==false){
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[TEX]->bmiHeader.biWidth,
		   TexInfo[TEX]->bmiHeader.biHeight, 0, GL_RGB,
		   GL_UNSIGNED_BYTE, TexBits[TEX]);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[TEX2]->bmiHeader.biWidth,
		   TexInfo[TEX2]->bmiHeader.biHeight, 0, GL_RGB,
		   GL_UNSIGNED_BYTE, TexBits[TEX2]);
	}
	draw_octal();
	glRotatef(-rot,XYAXIS,XYAXIS,ZAXIS);
	glTranslatef(-start_x,-start_y,0);
    
	if((start_x<(-SCREENPERSPECTIVE))||(start_x>SCREENPERSPECTIVE)||
		(start_y<(-SCREENPERSPECTIVE))||(start_y>SCREENPERSPECTIVE)){
		present=false;
		M=true;
	}
	if((((start_x+M_SQRT2>=collide_left_bound)&&(start_x+M_SQRT2<=collide_right_bound))&&
		((start_y+M_SQRT2<=collide_top_bound)&&(start_y+M_SQRT2>=collide_bottom_bound)))||
		(((start_x+M_SQRT2>=collide_left_bound)&&(start_x+M_SQRT2<=collide_right_bound))&&
		((start_y-M_SQRT2<=collide_top_bound)&&(start_y-M_SQRT2>=collide_bottom_bound)))||
		(((start_x-M_SQRT2>=collide_left_bound)&&(start_x-M_SQRT2<=collide_right_bound))&&
		((start_y-M_SQRT2<=collide_top_bound)&&(start_y-M_SQRT2>=collide_bottom_bound)))||
		(((start_x-M_SQRT2>=collide_left_bound)&&(start_x-M_SQRT2<=collide_right_bound))&&
		((start_y+M_SQRT2<=collide_top_bound)&&(start_y+M_SQRT2>=collide_bottom_bound)))){
		L=true;
	}
}

//***********************************************************************
//
// Function: draw_asteroid
//
// Purpose: draws asteroids. This part of the overloaded function draws
//    asteroids that are not mineable. It manipulates asteroid specific data
//    to give it its motion and rotation that will be independent of any other
//    asteroid created. All that is needed to to create new asteroid specific
//    global variables in order to effectively add another type of asteroid
//    to the program. 
//
// Paramaters: GLenum mode - allows the user to render the object or select 
//    it for picking.
//             int type - will be an enumerated object, used to give the asteroid
//    an identity.
//             float &rot - the asteroid specific rotation data
//             float &tran_x - the asteroid specific horizontal movement speed
//             float &tran_y - the asteroid specific vertical movement speed
//             float &start_x - the starting x coordinate as well as the current 
//    horizontal position of the asteroid.
//             float &start_y - the starting y coordinate as well as the current
//    vertical position of the asteroid. 
//             bool &present - allows for destruction and recreation of the asteroid
//             bool &P - allows for the asteroid to react to a paused game
//             bool &L - allows for the asteroid to react to a game over
//             const int TEX - gives the asteroid its texture
//             bool different - tells whether the asteroid will spin as it moves
//    or circle around the screen as it migrates closer to the ship.
//
// Calls: draw_octal - give the asteroid the shape of an octahedron
//
//***********************************************************************
void draw_asteroid(GLenum mode, /*enum type*/int type, float &rot, float &tran_x, float &tran_y,
	float &start_x, float &start_y, bool &present, bool &P,bool &L,const int TEX,bool different){
  
	if(mode == GL_SELECT){
		glLoadName(type);
	}
	if((P==false)&&(L==false)){
		rot+=SPIN;
		if(rot>CIRCLE-1){
			rot-=CIRCLE;
		}
		start_x+=tran_x;
		start_y+=tran_y;
	}
	if(different==true){
		glRotatef(rot,XYAXIS,XYAXIS,ZAXIS);
		glTranslatef(start_x,start_y,0);
	}else{
		glTranslatef(start_x,start_y,0);
		glRotatef(rot,XYAXIS,XYAXIS,ZAXIS);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[TEX]->bmiHeader.biWidth,
		   TexInfo[TEX]->bmiHeader.biHeight, 0, GL_RGB,
		   GL_UNSIGNED_BYTE, TexBits[TEX]);

	draw_octal();

	if(different==true){
		glTranslatef(-start_x,-start_y,0);
		glRotatef(-rot,XYAXIS,XYAXIS,ZAXIS);
	}else{
		glRotatef(-rot,XYAXIS,XYAXIS,ZAXIS);
		glTranslatef(-start_x,-start_y,0);
	}
    
	if((start_x<(-SCREENPERSPECTIVE))||(start_x>SCREENPERSPECTIVE)||
		(start_y<(-SCREENPERSPECTIVE))||(start_y>SCREENPERSPECTIVE)){
		present=false;
	}
	if((((start_x+M_SQRT2>=collide_left_bound)&&(start_x+M_SQRT2<=collide_right_bound))&&
		((start_y+M_SQRT2<=collide_top_bound)&&(start_y+M_SQRT2>=collide_bottom_bound)))||
		(((start_x+M_SQRT2>=collide_left_bound)&&(start_x+M_SQRT2<=collide_right_bound))&&
		((start_y-M_SQRT2<=collide_top_bound)&&(start_y-M_SQRT2>=collide_bottom_bound)))||
		(((start_x-M_SQRT2>=collide_left_bound)&&(start_x-M_SQRT2<=collide_right_bound))&&
		((start_y-M_SQRT2<=collide_top_bound)&&(start_y-M_SQRT2>=collide_bottom_bound)))||
		(((start_x-M_SQRT2>=collide_left_bound)&&(start_x-M_SQRT2<=collide_right_bound))&&
		((start_y+M_SQRT2<=collide_top_bound)&&(start_y+M_SQRT2>=collide_bottom_bound)))){
		L=true;
	}
}

//***********************************************************************
//
// Function: draw_space_ship
//
// Purpose: draws the spaceship. Will rotate the ship with correspondence to
//    the last quadrant clicked on.  
//
// Paramaters: GLenum mode - allows the user to render the object or select 
//    it for picking.
//
// Calls: None
//
//***********************************************************************
void draw_space_ship(GLenum mode){
	glDisable(GL_TEXTURE_2D);
    if(mode == GL_SELECT) {
		glLoadName(SHIP);
    }

    glRotatef(ship_rotincr,XYAXIS,XYAXIS,ZAXIS);
    glBegin(GL_TRIANGLE_FAN);{
		glColor3f(1.0,1.0,1.0); //white
		glVertex3f(0.0,3.0,0.0); //top of ship
		glColor3f(0.0,0.2,1.0); //blue
		glVertex3f(-1.0,-0.5,0.0); //left most point
		glVertex3f(-0.4,0.0,0.0);
		glVertex3f(0.0,-2.0,0.0); //bottom of ship
		glVertex3f(0.4,0.0,0.0);
		glVertex3f(1.0,-0.5,0.0); //right most point
    }glEnd();

    glBegin(GL_LINE_STRIP);{
		glColor3f(0.0,0.0,0.0);
		glVertex3f(-0.4,0.0,0.0);
		glVertex3f(0.0,2.0,0.0);
		glVertex3f(0.4,0.0,0.0);
    }glEnd();
	
    glRotatef(-ship_rotincr,XYAXIS,XYAXIS,ZAXIS);
    glEnable(GL_TEXTURE_2D);
}


//***********************************************************************
//
// Function: mouse
//
// Purpose: gives the user mouse interactivity with the program. Allows for the 
//    user to click on specific objects and manipulate them.
//
// Paramaters: int btn - the button pressed with the mouse.
//             int state - the current state of the button being pressed by the 
//    mouse (up or down).
//             int x - the x coordinate of the mouse on the screen
//             int y - the y coordinate of the mouse on the screen
//
// Calls: draw_asteroid - put each asteroid into selection mode (mineable or not)
//        draw_space_ship - put the spaceship into selection mode
//        draw_background - put the quadrants of the screen into selection mode
//        
//
//***********************************************************************
void mouse( int btn, int state, int x, int y ){
  
  GLuint selectBuf[SIZE];
  GLint hits;
  GLint viewport[4];

  if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glGetIntegerv (GL_VIEWPORT, viewport);

		// Must do the following BEFORE glInitNames()!
		glSelectBuffer (SIZE, selectBuf);
		glRenderMode(GL_SELECT);

		glInitNames();
		// Dummy first name on stack
		glPushName(0);

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();

		/*  create 5x5 pixel picking region near cursor location	*/
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
			   5.0, 5.0, viewport);
		gluOrtho2D (-SCREENPERSPECTIVE, SCREENPERSPECTIVE, -SCREENPERSPECTIVE, SCREENPERSPECTIVE);

		draw_background(GL_SELECT,QUADRANT1,QUADRANT2,QUADRANT3,QUADRANT4,QUADRANT5,QUADRANT6,QUADRANT7,QUADRANT8);
		draw_space_ship(GL_SELECT);

		draw_asteroid(GL_SELECT,MINEABLE,mine_rotincr,mine_trans_x,mine_trans_y,mine_start_x,mine_start_y,
			mine_present,paused,lose,VIVIDCRACKED,WATER,mineable);
		if(score>=LEVELONE){ 
			draw_asteroid(GL_SELECT,USELESS1,u1_rotincr,u1_trans_x,u1_trans_y,u1_start_x,u1_start_y,u1_present,
				paused,lose,CRACKEDPAINT,false);
		}
		if(score>=LEVELTWO){ 
			draw_asteroid(GL_SELECT,MINEABLE2,mine2_rotincr,mine2_trans_x,mine2_trans_y,mine2_start_x,mine2_start_y,
				mine2_present,paused,lose,VIVIDCRACKED,LADYOFTHELAKE,mineable2);
		}
		if(score>=LEVELTHREE){ 
			draw_asteroid(GL_SELECT,USELESS3,u3_rotincr,u3_trans_x,u3_trans_y,u3_start_x,u3_start_y,u3_present,
				paused,lose,RED,false);
		}
		if(score>=LEVELFOUR){ 
			draw_asteroid(GL_SELECT,USELESS4,u4_rotincr,u4_trans_x,u4_trans_y,u4_start_x,u4_start_y,u4_present,
				paused,lose,LINED,true);
		}

		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glutSwapBuffers ();

		hits = glRenderMode (GL_RENDER);
		processHits (hits, selectBuf);
	}
	glutPostRedisplay();
}

//***********************************************************************
//
// Function: drawText - function part of a program by Bryson R. Payne, M.Ed.
//    Georgia State University, Submitted in Partial Fulfillment of CSc 6820
//    - Computer Graphics Algorithms Under the Instruction of Dr. G. Scott Owen.
//    Substantially modified by Prof. David Chelberg and further modified by
//    Randal M. Obringer (me) on 12 October 2011 for use in this program
//
// Purpose: Auxilliary function to draw text at a particular
//     point on the window.
//
// Paramaters: int x - the x coordinate of where to place the text on the screen
//             int y - the y coordinate of where to place the text on the screen
//             char *message - the text to be drawn to the screen
//
// Calls: None
//
//***********************************************************************

void drawText(int x, int y, char *message)
{
	string string1=message; // my fix
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRasterPos2i(x/2, y/2);
	size_t len;
	len = string1.length(); //my fix
	for (size_t i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
	}
	glPopMatrix();
}


//***********************************************************************
//
// Function: show_score
//
// Purpose: displays the running score of the game and whether the game has been
//    paused or if the game has been lost
//
// Paramaters: None
//
// Calls: drawText - display text on the screen.
//        convert_int_to_string - convert the score into a string for use with
//    the drawText function.
//
//***********************************************************************
void show_score( void ){
	glDisable(GL_TEXTURE_2D);
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,SCREENPERSPECTIVE*winw,0,SCREENPERSPECTIVE*winh,-1,1);
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	int line_height=300;
	if((paused==false)&&(lose==false)){
		drawText(20,winh*10-line_height*1,"SCORE:");
	}else if(paused==true){
		drawText(20,winh*10-line_height*1, "PAUSED");
	}else if(lose==true){
		drawText(20,winh*10-line_height*1, "GAME OVER");
	}
	string temp=convert_int_to_string(score);
	const int len=temp.length();
	char converted_score[SIZE2];
	for(int i=0;i<len;i++){
		converted_score[i]=temp[i];
		if(i+1==len){
			converted_score[i+1]='\n';
		}
	}
	drawText(20,winh*10-line_height*2, converted_score);
  
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}


//***********************************************************************
//
// Function: post_message
//
// Purpose: Displays the starting splash screen/help screen for the game of 
//    asteroid mining. Explains the objectives of the game as well as what
//    mineable asteroids look like within the game. 
//
// Paramaters: int TEX,TEX2 - the textures of the mineable asteroids
//
// Calls: drawText - display text on the screen
//        draw_octal - draw the shape the asteroids will be in
//
//***********************************************************************
void post_message(int TEX,int TEX2){
	// Clear the window
	glDisable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,SCREENPERSPECTIVE*winw,0, SCREENPERSPECTIVE*winh, -1, 1);
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	int line_height=300;
	drawText(20,winh*10-line_height*1,"        This is the Game \"ASTEROID MINING\"");
	drawText(20,winh*10-line_height*3,"  You must get resources from mineable asteroids");
	drawText(20,winh*10-line_height*4,"  for points while at the same time, avoiding incoming");
	drawText(20,winh*10-line_height*5,"  asteroids.");
	drawText(20,winh*10-line_height*7,"  You may press n for a new game,");
	drawText(20,winh*10-line_height*8,"  You may press p to pause the game,");
	drawText(20,winh*10-line_height*9,"  You may press h for this screen again,");
	drawText(20,winh*10-line_height*10,"  or you can press q to quit");
	drawText(20,winh*10-line_height*12," MINEABLE ASTEROIDS =");
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(1.5,-5.5,0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[TEX]->bmiHeader.biWidth,
	   TexInfo[TEX]->bmiHeader.biHeight, 0, GL_RGB,
	   GL_UNSIGNED_BYTE, TexBits[TEX]);
	draw_octal();
	glTranslatef(3.0,0.0,0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[TEX2]->bmiHeader.biWidth,
	   TexInfo[TEX2]->bmiHeader.biHeight, 0, GL_RGB,
	   GL_UNSIGNED_BYTE, TexBits[TEX2]);
	draw_octal();
	glTranslatef(-4.5,5.5,0.0);
	glutSwapBuffers();
	sleep(SLEEPTIME);
	glEnable(GL_TEXTURE_2D);
}


//***********************************************************************
//
// Function: keys
//
// Purpose: Process keyboard input to start a new game, pause the game, display
//    the help screen, or quit the program.
//
// Paramaters: unsigned char key - the key that was pressed.
//             int x - the x coordinate of where the mouse is on the screen?
//             int y - the y coordinate of where the mouse is on the screen?
//
// Calls: post_message - display the help screen
//
//***********************************************************************
// Process keyboard input to change object attributes
void keys (unsigned char key, int x, int y){
	switch (key)  {
		case 'N':
		case 'n':
			mine_present=false;
			u1_present=false;
			mine2_present=false;
			u3_present=false;
			u4_present=false;
			lose=false;
			mineable=true;
			mineable2=true;
			score=0;
			break;
		case 'P':
		case 'p':
			if(paused==false){
				paused=true;
			}else{
				paused=false;
			}
			break;
		case 'H':
		case 'h':
			post_message(WATER,LADYOFTHELAKE);
			break;
		case 'q':
		case 'Q':	// Quit the program completely
			exit(EXIT_SUCCESS);
			break;
	}
	glutPostRedisplay();
} 

//***********************************************************************
//
// Function: pick_pos_dir
//
// Purpose: pick the starting position, the horizontal speed, and the vertical
//    speed of an asteroid at random. Allows for the game to always be different and fun. 
//
// Paramaters: bool &which_present - if an asteroid is put out of existence (destroyed),
//    put it back into existence.
//             float &trans_x - the horizontal speed of the asteroid.
//             float &trans_y - the vertical speed of the asteroid.
//             float &start_x - the starting x coordinate of the asteroid.
//             float &start_y - the starting y coordinate of the asteroid.
//
// Calls: None
//
//***********************************************************************
void pick_pos_dir(bool &which_present,float &trans_x,float &trans_y,float &start_x,float &start_y){
	if(which_present==false){
		which_present=true;
		random_number=random()%(int)(SCREENPERSPECTIVE*8); // % by perimeter of screen with its coordinate system
		if((random_number>=0)&&(random_number<=(SCREENPERSPECTIVE*2))){ //top of screen
			start_y=SCREENPERSPECTIVE;
			trans_y=-STEEP;
			if((random_number>0)&&(random_number<=SCREENPERSPECTIVE)){ //top left of screen
				start_x=-random_number;
				trans_x=SLIGHT;
			}else{ //top right of screen
				start_x=random_number%(int)SCREENPERSPECTIVE;
				trans_x=-SLIGHT;
			}
		}else if((random_number>=((SCREENPERSPECTIVE*2)+1))&&(random_number<=4*SCREENPERSPECTIVE)){ //right of screen
			start_x=SCREENPERSPECTIVE;
			trans_x=-STEEP;
			if((random_number>=((SCREENPERSPECTIVE*2)+1))&&(random_number<=3*SCREENPERSPECTIVE)){ //right top of screen
				start_y=random_number%(int)SCREENPERSPECTIVE;
				trans_y=-SLIGHT;
			}else{ //right bottom of screen
				start_y=-(random_number%(int)SCREENPERSPECTIVE);
				trans_y=SLIGHT;
			}
		}else if((random_number>=((SCREENPERSPECTIVE*4)+1))&&(random_number<=SCREENPERSPECTIVE*6)){ //bottom of screen
			start_y=-SCREENPERSPECTIVE;
			trans_y=STEEP;
			if((random_number>=((SCREENPERSPECTIVE*4)+1))&&(random_number<=SCREENPERSPECTIVE*5)){ //bottom right of screen
				start_x=random_number%(int)SCREENPERSPECTIVE;
				trans_x=-SLIGHT;
			}else{ //bottom left of screen
				start_x=-(random_number%(int)SCREENPERSPECTIVE);
				trans_x=SLIGHT;
			}
		}else if((random_number>=((SCREENPERSPECTIVE*6)+1))&&(random_number<=SCREENPERSPECTIVE*8)){ //left of screen
			start_x=-SCREENPERSPECTIVE;
			trans_x=STEEP;
			if((random_number>=((SCREENPERSPECTIVE*6)+1))&&(random_number<=SCREENPERSPECTIVE*7)){ //left bottom of screen
				start_y=-(random_number%(int)SCREENPERSPECTIVE);
				trans_y=SLIGHT;
			}else{ //left top of screen
				start_y=random_number%(int)SCREENPERSPECTIVE;
				trans_y=-SLIGHT;
			}
		}
	}
}

//***********************************************************************
//
// Function: my_reshape
//
// Purpose: Allows for the screen to be reshaped and have the game still
//    function properly under the new window dimensions
//
// Paramaters: int w - the width of the screen
//             int h - the height of the screen
//
// Calls: None
//
//***********************************************************************
void my_reshape(int w, int h){
	winw = w;
	winh = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-SCREENPERSPECTIVE,SCREENPERSPECTIVE,-SCREENPERSPECTIVE,SCREENPERSPECTIVE);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

//***********************************************************************
//
// Function: display - the glue to the program.
//
// Purpose: Ties everything together. Draws all the objects and screens when
//    necessary. Allows for more asteroids to come into play as the user's
//    score increases. Draws the explosion of the ship upon impact with an 
//    asteroid.
//
// Paramaters: None
//
// Calls: draw_background - draw the background
//        draw_space_ship - draw the ship
//        pick_pos_dir - decide the data for the asteroids
//        draw_asteroid - draw the asteroids
//        post_message - display the help screen on start up
//        draw_octal - display the explosion
//        show_score - display the score and status of game
//
//***********************************************************************
void display( void ){
	glClear(GL_COLOR_BUFFER_BIT);

	if(starting==true){
		post_message(WATER,LADYOFTHELAKE);
		starting=false;
	}
  
	draw_background(GL_RENDER,QUADRANT1,QUADRANT2,QUADRANT3,QUADRANT4,QUADRANT5,QUADRANT6,QUADRANT7,QUADRANT8);
	draw_space_ship(GL_RENDER);

	pick_pos_dir(mine_present,mine_trans_x,mine_trans_y,mine_start_x,mine_start_y);
	draw_asteroid(GL_RENDER,MINEABLE,mine_rotincr,mine_trans_x,mine_trans_y,mine_start_x,mine_start_y,
		mine_present,paused,lose,VIVIDCRACKED,WATER,mineable);

	if(score>=LEVELONE){
		pick_pos_dir(u1_present,u1_trans_x,u1_trans_y,u1_start_x,u1_start_y);
		draw_asteroid(GL_RENDER,USELESS1,u1_rotincr,u1_trans_x,u1_trans_y,u1_start_x,u1_start_y,u1_present,
			paused,lose,CRACKEDPAINT,false);
	}
	if(score>=LEVELTWO){
		pick_pos_dir(mine2_present,mine2_trans_x,mine2_trans_y,mine2_start_x,mine2_start_y);
		draw_asteroid(GL_RENDER,MINEABLE2,mine2_rotincr,mine2_trans_x,mine2_trans_y,mine2_start_x,mine2_start_y,
			mine2_present,paused,lose,VIVIDCRACKED,LADYOFTHELAKE,mineable2);
	}
	if(score>=LEVELTHREE){
		pick_pos_dir(u3_present,u3_trans_x,u3_trans_y,u3_start_x,u3_start_y);
		draw_asteroid(GL_RENDER,USELESS3,u3_rotincr,u3_trans_x,u3_trans_y,u3_start_x,u3_start_y,u3_present,
			paused,lose,RED,false);
	}
	if(score>=LEVELFOUR){
		pick_pos_dir(u4_present,u4_trans_x,u4_trans_y,u4_start_x,u4_start_y);
		draw_asteroid(GL_RENDER,USELESS4,u4_rotincr,u4_trans_x,u4_trans_y,u4_start_x,u4_start_y,u4_present,
			paused,lose,LINED,true);
	}
    

	if(lose==true){
		glScalef(XYSCALE,XYSCALE,ZSCALE);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[FIRE]->bmiHeader.biWidth,
			TexInfo[FIRE]->bmiHeader.biHeight, 0, GL_RGB,
		GL_UNSIGNED_BYTE, TexBits[FIRE]);
		draw_octal();
		glScalef(1.0/XYSCALE,1.0/XYSCALE,1.0/ZSCALE);
	}
	show_score();

	glutSwapBuffers();
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (winw, winh);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Asteroid Mining"); //initialize the name of the window to be "Asteroid Mining"
	glutReshapeFunc(my_reshape);
	glutIdleFunc(my_idle);
	glutMouseFunc (mouse);
	glutKeyboardFunc (keys);	// Set function for key command processing 
	my_init();
	glutDisplayFunc(display);
  
	glutMainLoop(); //necessary for proper display

	return(EXIT_SUCCESS);
}
