//*********************************************************************
//
//  Program: hw3 - model a 3D solar system for Asteroid Mining game. 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the 3D version of the asteroid mining game. The
//    user may pick between one of two ships to use for the game. Each
//    ship will behave in a different manner. When the ship moves the 
//    ship will lose fuel. Clicking on fuel through space will replenish
//    your ship's fuel to a certain extent. The user will get points for 
//    mining mineable asteroids.  
//
//  Last Updated: 11/1/2011
//
//*********************************************************************

#include "bitmap.h"
#include "text.h"
#include "objects.h"
#include <iostream>
#include <list>
//#include <unistd.h> //for unix
#include <io.h>
#include <GL/glut.h>
using namespace std;

#define FOVYINCREMENT 5 //increment to increase/decrease field of view in gluPerspective
#define MAXFOVY 110 //max field of view in gluPerspective
#define MINFOVY 80 //min field of view in gluPerspective
#define ONESECOND 1000 //used with fps (frames per second) to get amount of redraws per second
#define LEVELONE 10 //draw another asteroid at this score
#define LEVELTWO 20 //draw another asteroid at this score
#define LEVELTHREE 30 //draw another asteroid at this score
#define LEVELFOUR 40 //draw another asteroid at this score
#define TEXTSCREEN 15 //size of screen for text
#define ADDSCORE 10 //amount to add score
#define MOUSEBOX 5.0 //half the size of the square around the mouse for picking
#define FARSIGHT 400.0 //far clipping plane in gluPerspective
#define NEARSIGHT 1.0 //near clipping plane in gluPerspective
#define SELECTIONFOVY 90 //at ship selection screen field of view
#define SELECTIONPOSITIONX 1.0 //x position of ship during ship picking screen
#define SELECTIONPOSITIONY 2.0 //y position of ship during ship picking screen
#define SELECTIONPOSITIONZ 3.0 //z position of ship during ship picking screen
#define FIRSTPERSONX 0.0 //x position of the camera during first person view
#define FIRSTPERSONY 0.0 //y position of the camera during first person view
#define FIRSTPERSONZ 2.0 //z position of the camera during first person view
#define THIRDPERSONX 0.0 //x position of the camera during third person view
#define THIRDPERSONY 2.0 //y position of the camera during third person view
#define THIRDPERSONZ 3.0 //z position of the camera during third person view
#define DISPLACEMENTX 0.0 //x value to place camera and ship away from origin
#define DISPLACEMENTY 0.0 //y value to place camera and ship away from origin
#define DISPLACEMENTZ 45.0 //z value to place camera and ship away from origin
#define POSITION 100 //starting x and y position of the screen when it is created
#define STARTSCORE 0 //starting score
#define NOFUEL 0 //when there is no fuel left
#define NOSHIP 0 //no ship has been chosen yet
#define FIRSTSHIP 1 //you chose the first ship (blue)
#define SECONDSHIP 2 //you chose the second ship (red)
#define MAX_NUM_TEXTURES 12 //max number of textures loadable into the program
#define SIZE 512
#define ZEROMOVEMENT 0 //ship is not moving

int winw=500; //initial width of screen
int winh=500; //initial height of screen
int score=STARTSCORE;
int fovy=SELECTIONFOVY;
float ratio=1.0;

int fps=15; //frames per second
bool paused=false; //game paused?
bool lose=false; //game lost?
bool first_person=false; //will really initialize to false //first person view or not?
bool alien_view=false; //third person from an alien's perspective? not implemented yet
int choice=NOSHIP; //ship choice

/* texture data */
GLint WRAP_S=GL_REPEAT;
GLint WRAP_T=GL_REPEAT;
GLint MAG_FILTER=GL_LINEAR;
GLint MIN_FILTER=GL_LINEAR;
GLint TEXTURE_ENV=GL_REPLACE;
GLint PERSPECTIVE_HINT=GL_NICEST;
int NUM_TEXTURES=0;
BITMAPINFO *TexInfo[MAX_NUM_TEXTURES]; /* Texture bitmap information */
GLubyte    *TexBits[MAX_NUM_TEXTURES]; /* Texture bitmap pixel bits */

//names of textures
#define LINED 0
#define RED 1
#define VIVIDCRACKED 2
#define CRAZED 3
#define CRACKED 4
#define FIRE 5
#define LADYOFTHELAKE 6
#define STORMY 7
#define WATER 8
#define CRACKEDPAINT 9
#define STARS 10
#define FUELPOSTER 11
/* end texture data */

//create our objects for use in the program
Text text;
Ship ships;
Mysun mysun;
Mercury mercury;
Venus venus;
Earth earth;
Mars mars;
Jupiter jupiter;
Uranus uranus;
Space space;
Asteroid asteroid,asteroid2,asteroid3,asteroid4,asteroid5;
Items f1,f2,f3,f4;
Alien a1,a2,a3,a4;
Alien *ap;

//all the possible objects in the program
enum Object {SHIP1=FIRSTSHIP,SHIP2,MYSUN,MERCURY,VENUS,EARTH,MARS,JUPITER,URANUS,
	SPACE,ASTEROID,ASTEROID2,ASTEROID3,ASTEROID4,ASTEROID5,FUEL,FUEL2,
        FUEL3,FUEL4,ALIEN,ALIEN2,ALIEN3,ALIEN4};


//***********************************************************************
//
// Function: compute_distance
//
// Purpose: Compute the distance between the sun and the Ship
//
// Paramaters: Ship s - the ship to get position from
//             Mysun obj - the sun object to get position from
//
// Calls: 
//
//***********************************************************************
float compute_distance(Ship &s, Mysun &obj){
  float x=s.get_x_pos()-DISPLACEMENTX;
  float y=s.get_y_pos()-DISPLACEMENTY;
  float z=s.get_z_pos()-DISPLACEMENTZ;
  float x2=-THIRDPERSONX;
  float y2=-THIRDPERSONY;
  float z2=-THIRDPERSONZ;
  return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2))+((z-z2)*(z-z2)));
}

//***********************************************************************
//
// Function: compute_distance
//
// Purpose: Compute the distance between the ship and an alien object
//
// Paramaters: Ship s - The ship to get position from 
//             Alien obj - The Alien to get position from
//
// Calls: 
//
//***********************************************************************
float compute_distance(Ship &s, Alien &obj){
  float x=s.get_x_pos()-DISPLACEMENTX;
  float y=s.get_y_pos()-DISPLACEMENTY;
  float z=s.get_z_pos()-DISPLACEMENTZ;
  float x2=obj.get_x();-THIRDPERSONX;
  float y2=obj.get_y();-THIRDPERSONY;
  float z2=obj.get_z();-THIRDPERSONZ;
  return sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2))+((z-z2)*(z-z2)));
}

//***********************************************************************
//
// Function: compute_distance
//
// Purpose: Determines the distance that the ship is away from the origin of the sun
//
// Paramaters: Ship s - The ship object to get its position
//
// Calls: Ship::get_x_pos
//        Ship::get_y_pos
//        Ship::get_z_pos
//        Ship::get_radius
//
//***********************************************************************
float compute_distance(Ship&s){
  float x=s.get_x_pos()-DISPLACEMENTX;
  float y=s.get_y_pos()-DISPLACEMENTY;
  float z=s.get_z_pos()-DISPLACEMENTZ;
  return (sqrt((x*x)+(y*y)+(z*z))+s.get_radius());
}

//***********************************************************************
//
// Function: detect_collisions
//
// Purpose: Detects if a collision with the ship has happened
//
// Paramaters:  
//
// Calls: Ship::get_radius
//        Alien::get_radius
//        Mysun::get_radius
//        Space::get_radius
//        compute_distance
//
//***********************************************************************
void detect_collisions(){
  if((ships.get_radius()+mysun.get_radius())>compute_distance(ships,mysun)){ //ship with sun
    lose=true;
  }else if((ships.get_radius()+a1.get_radius())>compute_distance(ships,a1)){//not working
    lose=true;
  }else if((ships.get_radius()+a2.get_radius())>compute_distance(ships,a2)){//not working
    lose=true;
  }else if((ships.get_radius()+a3.get_radius())>compute_distance(ships,a3)){//not working
    lose=true;
  }else if((ships.get_radius()+a4.get_radius())>compute_distance(ships,a4)){//not working
    lose=true;
  }else if(compute_distance(ships)>space.get_radius()){ //if outside our program
    lose=true;
  }
}

//***********************************************************************
//
// Function: new_game
//
// Purpose: resets all object data, score, view, and lose status
//
// Paramaters: 
//
// Calls: Obj::reset
//
//***********************************************************************
void new_game(){
  lose=false;
  first_person=false;
  alien_view=false;
  score=STARTSCORE;
  ships.reset();
  mercury.reset();
  venus.reset();
  earth.reset();
  mars.reset();
  jupiter.reset();
  uranus.reset();
  asteroid.reset();
  asteroid2.reset();
  asteroid3.reset();
  asteroid4.reset();
  asteroid5.reset();
  f1.new_items();
  f2.new_items();
  f3.new_items();
  f4.new_items();
  a1.reset();
  a2.reset();
  a3.reset();
  a4.reset();
}

//***********************************************************************
//
// Function: my_timer
//
// Purpose: Slow the program down so the objects will move at a desired pace
//
// Paramaters: int extra - extra time 
//
// Calls: 
//
//***********************************************************************
void my_timer(int extra){
  glutPostRedisplay();
  glutTimerFunc(ONESECOND/fps,my_timer,0);
}

//***********************************************************************
//
// Function: change_texture
//
// Purpose: changes the texture so it will be applied to the next object drawn
//
// Paramaters: int tex - the texture id to apply to the next object drawn
//
// Calls: 
//
//***********************************************************************
void change_texture(int tex){
  glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo[tex]->bmiHeader.biWidth,
		   TexInfo[tex]->bmiHeader.biHeight, 0, GL_RGB,
		   GL_UNSIGNED_BYTE, TexBits[tex]);
}

//***********************************************************************
//
// Function: draw_object
//
// Purpose: does the transformations, changes the texture, and draws the 
//    desired object to clean up code
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//             Mercury& obj - the parent is a mercury object so its children
//                     can also be passed through. 
//             const int ITEM - the id of the object
//             const int TEX - the texture of the object
//
// Calls: obj.draw
//        change_texture
//        obj.update_orbit
//
//***********************************************************************
void draw_object(GLenum mode, Mercury& obj, const int ITEM, const int TEX){
  if((paused==false)&&(lose==false)&&(mode==GL_RENDER)){
    obj.update_orbit();
  }
  glRotatef(obj.get_total_rot(),obj.get_x_axis(),obj.get_y_axis(),obj.get_z_axis()); 
  glTranslatef(obj.get_x_pos(),0,0);
  change_texture(TEX);
  obj.draw(mode,ITEM);
  glTranslatef(-obj.get_x_pos(),0,0);
  glRotatef(-obj.get_total_rot(),obj.get_x_axis(),obj.get_y_axis(),obj.get_z_axis());
}

//***********************************************************************
//
// Function: draw_asteroid
//
// Purpose: does the transformations, changes the texture, and draws the 
//    desired object to clean up code. Specific to asteroid objects
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//             Asteroid& aster - get the asteroids personal variables for 
//                     movements 
//             const int ITEM - the id of the object
//
// Calls: draw_object
//
//***********************************************************************
void draw_asteroid(GLenum mode, Asteroid& aster,const int ITEM){
  if(aster.get_mine_status()==true){
    draw_object(mode,aster,ITEM,LADYOFTHELAKE);
  }else{
    draw_object(mode,aster,ITEM,LINED);
  }
}

//***********************************************************************
//
// Function: draw_item
//
// Purpose: does the transformations, changes the texture, and draws the 
//    desired object to clean up code
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//             Items& it - get the items specific variables 
//             const int ITEM - the id of the object
//             const int TEX - the texture of the object
//
// Calls: it.draw_fuel
//        change_texture
//
//***********************************************************************
void draw_item(GLenum mode, Items& it, const int ITEM, const int TEX){
  glTranslatef(it.get_x(),it.get_y(),it.get_z());
  change_texture(TEX);
  it.draw_fuel(mode,ITEM);
  glTranslatef(-it.get_x(),-it.get_y(),-it.get_z());
}

//***********************************************************************
//
// Function: draw_alien
//
// Purpose: does the transformations, changes the texture, and draws the 
//    desired object to clean up code
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//             Alien& it - the parent is a mercury object so its children
//                     can also be passed through. 
//             const int ITEM - the id of the object
//             const int TEX - the texture of the object
//
// Calls: it.draw
//        change_texture
//
//***********************************************************************
void draw_alien(GLenum mode, Alien& it, const int ITEM, const int TEX){
  if(mode==GL_SELECT){
    glLoadName(ITEM);
  }
  if((paused==false)&&(lose==false)&&(mode==GL_RENDER)){
    it.update_movement();
  }
  glTranslatef(it.get_x(),it.get_y(),it.get_z());
  change_texture(TEX);
  it.draw();
  glTranslatef(-it.get_x(),-it.get_y(),-it.get_z());
}

//***********************************************************************
//
// Function: place_ships
//
// Purpose: clean up code and make it more readable. draws the ship in the program.
//    places the camera behind the ship. Updates the ship's movements.
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//
// Calls: Ship::draw_space_ship
//        Ship::draw_space_ship2
//        Ship::update_move
//        Ship::get_look_left_right
//        Ship::get_look_up_down
//
//***********************************************************************
void place_ships(GLenum mode){
  glRotatef(ships.get_look_left_right(),0,1,0);
  glRotatef(ships.get_look_up_down(),1,0,0);
  if(first_person){
    glTranslatef(FIRSTPERSONX,FIRSTPERSONY,FIRSTPERSONZ);//ship origin is behind camera
    if(choice==FIRSTSHIP){
      ships.draw_space_ship(mode,SHIP1);
    }else{
      ships.draw_space_ship2(mode,SHIP2);
    }
    glTranslatef(THIRDPERSONX,THIRDPERSONY,THIRDPERSONZ);//move everything else to where ship was relative to the camera
  }else{ //start position
    glTranslatef(THIRDPERSONX,-THIRDPERSONY,-THIRDPERSONZ);
    if(choice==FIRSTSHIP){
      ships.draw_space_ship(mode,SHIP1);
    }else{
      ships.draw_space_ship2(mode,SHIP2);
    }
    glTranslatef(THIRDPERSONX,THIRDPERSONY,THIRDPERSONZ);
  }
  if(mode==GL_RENDER){
    if((paused==false)&&(lose==false)){
      ships.update_move();
    }
  }
}

//***********************************************************************
//
// Function: place_planets
//
// Purpose: clean up code and make it more readable. draws the planets in the program
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//
// Calls: draw_object
//
//***********************************************************************
void place_planets(GLenum mode){
  glCallList(SPACE);
  glCallList(MYSUN);

  draw_object(mode,mercury,MERCURY,CRACKEDPAINT);
  draw_object(mode,venus,VENUS,STORMY);
  draw_object(mode,earth,EARTH,WATER);
  draw_object(mode,mars,MARS,RED);
  draw_object(mode,jupiter,JUPITER,STORMY);
  draw_object(mode,uranus,URANUS,WATER);
}

//***********************************************************************
//
// Function: place_items
//
// Purpose: clean up code and make it more readable. draws the items in the program
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//
// Calls: draw_item
//
//***********************************************************************
void place_items(GLenum mode){
  draw_item(mode,f1,FUEL,FUELPOSTER);
  draw_item(mode,f2,FUEL2,FUELPOSTER);
  draw_item(mode,f3,FUEL3,FUELPOSTER);
  draw_item(mode,f4,FUEL4,FUELPOSTER);
}

//***********************************************************************
//
// Function: place_aliens
//
// Purpose: clean up code and make it more readable. draws the aliens in the program
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//
// Calls: draw_alien
//
//***********************************************************************
void place_aliens(GLenum mode){
  draw_alien(mode, a1,ALIEN,LADYOFTHELAKE);
  draw_alien(mode, a2,ALIEN2,VIVIDCRACKED);
  draw_alien(mode, a3,ALIEN3,FIRE);
  draw_alien(mode, a4,ALIEN4,WATER);
}

//***********************************************************************
//
// Function: place_asteroids
//
// Purpose: clean up code and make it more readable. draws the asteroids in the program
//
// Paramaters: GLenum mode - GL_RENDER OR GL_SELECT
//
// Calls: draw_asteroid
//
//***********************************************************************
void place_asteroids(GLenum mode){
  draw_asteroid(mode,asteroid,ASTEROID);
  if(score>=LEVELONE){
    draw_asteroid(mode,asteroid2,ASTEROID2);
  }if(score>=LEVELTWO){
    draw_asteroid(mode,asteroid3,ASTEROID3);
  }if(score>=LEVELTHREE){
    draw_asteroid(mode,asteroid4,ASTEROID4);
  }if(score>=LEVELFOUR){
    draw_asteroid(mode,asteroid5,ASTEROID5);
  }
}

//***********************************************************************
//
// Function: handle_fuel
//
// Purpose: clean up code and make it more readable. handles anything that has to 
//     do with the fuel in the program. 
//
// Paramaters: 
//
// Calls: Ship::decr_fuel
//        Ship::get_movement
//        Ship::get_move_x
//        Ship::get_move_y
//        Ship::get_fuel
//
//***********************************************************************
void handle_fuel(){
  if((ships.get_movement()!=ZEROMOVEMENT)||(ships.get_move_x()!=ZEROMOVEMENT)||
	(ships.get_move_y()!=ZEROMOVEMENT)){
    if((lose==false)&&(paused==false)){
      ships.decr_fuel();
    }
  }
  if(ships.get_fuel()==NOFUEL){
    lose=true;
  }
}

//***********************************************************************
//
// Function: build_list
//
// Purpose: demonstrates I know how to do this. Used it for stationary objects
//
// Calls: space.draw
//        change_texture
//        mysun.draw
//
//***********************************************************************
void build_list( void ){

  glNewList(SPACE, GL_COMPILE);{
    change_texture(STARS);
    space.draw(GL_RENDER,MYSUN);
  }glEndList();

  glNewList(MYSUN, GL_COMPILE);{
    change_texture(FIRE);
    mysun.draw(GL_RENDER, MYSUN);
  }glEndList();
}

//***********************************************************************
//
// Function: zoom_camera
//
// Purpose: change the field of view to zoom in
//
//***********************************************************************
void zoom_camera(){
  fovy+=FOVYINCREMENT;
  if(fovy>MAXFOVY){
    fovy=MAXFOVY;
  }
}

//***********************************************************************
//
// Function: unzoom_camera
//
// Purpose: change the field of view to unzoom the camera (zoom out)
//
//***********************************************************************
void unzoom_camera(){
  fovy-=FOVYINCREMENT;
  if(fovy<MINFOVY){
    fovy=MINFOVY;
  }
}

//***********************************************************************
//
// Function: KeyPunch
//
// Purpose: Process keyboard input to start a new game, pause the game, display
//    the help screen, or quit the program.
//
// Paramaters: unsigned char key - the key that was pressed.
//             int x - the x coordinate of where the mouse is on the screen?
//             int y - the y coordinate of where the mouse is on the screen?
//
// Calls: Text::post_message
//        zoom_camera
//        unzoom_camera
//
//***********************************************************************
void KeyPunch (unsigned char key, int x, int y){
  switch (key)  {
    case 'c':
      zoom_camera();
      break;
    case 'C':
      unzoom_camera();
      break;
    case 'f':
      first_person=!first_person;
      ships.reset_view();
      alien_view=false;
      break;
    case 'N':
    case 'n':
      new_game();
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
      text.post_message(winw,winh,TEXTSCREEN);
      break;
    case 'q':
    case 'Q':	// Quit the program completely
      //exit(EXIT_SUCCESS);
      break;
  }
  glutPostRedisplay();
} 

//***********************************************************************
//
// Function: SpecialKeyFunc
//
// Purpose: Process keyboard input to start a new game, pause the game, display
//    the help screen, or quit the program.
//
// Paramaters: int key - the key that was pressed.
//             int x - the x coordinate of where the mouse is on the screen?
//             int y - the y coordinate of where the mouse is on the screen?
//
// Calls: Ship::incr_x_rot
//        Ship::decr_move_x
//        Ship::decr_x_rot
//        Ship::incr_move_x
//        Ship::decr_y_rot
//        Ship::incr_y_rot
//        Ship::decr_move_y
//        Ship::incr_move_y
//        Ship::speed_up
//        Ship::slow_down
//
//***********************************************************************
void SpecialKeyFunc( int Key, int x, int y )
{
  switch (Key) {
    case GLUT_KEY_RIGHT:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(first_person)){
            ships.look_right();
          }else{
            if(choice==FIRSTSHIP){
              ships.incr_x_rot();
            }else{
              ships.decr_move_x();
            }
          }
        }
      }
      break;
    case GLUT_KEY_LEFT:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(first_person)){
            ships.look_left();
          }else{
            if(choice==FIRSTSHIP){
              ships.decr_x_rot();
            }else{
              ships.incr_move_x();
            }
          }
        }
      }
      break;
    case GLUT_KEY_UP:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(first_person)){
            ships.look_up();
          }else{
            if(choice==SECONDSHIP){
              ships.decr_y_rot();
            }else{
              ships.decr_move_y();
            }
          }
        }
      }
      break;
    case GLUT_KEY_DOWN:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(first_person)){
            ships.look_down();
          }else{
            if(choice==SECONDSHIP){
              ships.incr_y_rot();
            }else{
              ships.incr_move_y();
            }
          }
        }
      }
      break;
    case GLUT_KEY_PAGE_UP:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          ships.speed_up();
        }
      }
      break;
    case GLUT_KEY_PAGE_DOWN:
      if(!alien_view){
        if((paused==false)&&(lose==false)){
          ships.slow_down();
        }
      }
      break;
  }
}

//***********************************************************************
// Function:find_textures
//
// Purpose: loads in textures to the program in a certain order so that we
//       can define the textures for their easy use
//
// Calls: LoadDIBitmap
//
//***********************************************************************
void find_textures( void ){
  list<string> imageFileList; 

  //force order of textures for definition
  imageFileList.push_back("textures/lined.bmp");
  imageFileList.push_back("textures/red.bmp");
  imageFileList.push_back("textures/vividCracked.bmp");
  imageFileList.push_back("textures/crazed.bmp");
  imageFileList.push_back("textures/cracked.bmp");
  imageFileList.push_back("textures/fire.bmp");
  imageFileList.push_back("textures/ladyofthelake.bmp");
  imageFileList.push_back("textures/stormy.bmp");
  imageFileList.push_back("textures/water.bmp");
  imageFileList.push_back("textures/crackedPaint.bmp");
  imageFileList.push_back("textures/stars.bmp");
  imageFileList.push_back("textures/fuelPoster.bmp");

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
    if(TexBits[i]==NULL){
      cout << endl;
      cout << "Failed to load in " << files[i] << endl;
      cout << "Check if the name is correct or if it " << endl;
      cout << "is even in the textures/ folder" << endl;
      //exit(-1);
    }
  }
}

//***********************************************************************
//
// Function: case_asteroid
//
// Purpose: adds up the score when an asteroid is clicked. Makes a mineable 
//       asteroid unmineable or an unmineable asteroid disappear and recreate
//       it somewhere else
//
// Paramaters: Asteroid aster - an asteroid object to get its mine status
//
// Calls: aster.reset
//        aster.unmineable
//        aster.get_mine_status
//
//***********************************************************************
void case_asteroid(Asteroid& aster){
  if(aster.get_mine_status()==true){ //if clicked on mineable asteroid
    score+=ADDSCORE;
    aster.unmineable(); //make it unmineable
  }else{ //if unmineable clicked on
    aster.reset(); //recreate it somewhere else
  }
}

//***********************************************************************
//
// Function: case_alien
//
// Purpose: pick the alien for which to have as the view point. 
//
// Paramaters: Alien it - The alien object for which to get position coordinates
//      from.
//
// Calls: 
//
//***********************************************************************
void case_alien(Alien& it){
  alien_view=true;
  ap=&it;
  first_person=false;
}

//***********************************************************************
//
// Function: case_fuel
//
// Purpose: increases the ship's fuel in case a fuel object is clicked.
//    Also makes it disappear and recreated away from the user so it can't
//    get used again.
//
// Paramaters: Items f - to get the reset function of the item
//
// Calls: f.reset
//        Ship::incr_fuel
//
//***********************************************************************
void case_fuel(Items& f){
  ships.incr_fuel();
  f.reset();
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
      switch (*ptr){
        case SHIP1: //select the first ship to play with
          choice=FIRSTSHIP;
          break;
        case SHIP2: //select the second ship to play with
          choice=SECONDSHIP;
          break;
        case ASTEROID: //mine asteroid or recreate it
          case_asteroid(asteroid);
	  break;
        case ASTEROID2: //mine asteroid or recreate it
          case_asteroid(asteroid2);
	  break;
        case ASTEROID3: //mine asteroid or recreate it
          case_asteroid(asteroid3);
	  break;
        case ASTEROID4: //mine asteroid or recreate it
          case_asteroid(asteroid4);
	  break;
        case ASTEROID5: //mine asteroid or recreate it
          case_asteroid(asteroid5);
	  break;
        case FUEL: //gather fuel and relocate it
          case_fuel(f1);
          break;
        case FUEL2: //gather fuel and relocate it
          case_fuel(f2);
          break;
        case FUEL3: //gather fuel and relocate it
          case_fuel(f3);
          break;
        case FUEL4: //gather fuel and relocate it
          case_fuel(f4);
          break;
        case ALIEN: //view the world from the first alien's point of view
          case_alien(a1);
          break;
        case ALIEN2: //view the world from the second alien's point of view
          case_alien(a2);
          break;
        case ALIEN3: //view the world from the third alien's point of view
          case_alien(a3);
          break;
        case ALIEN4: //view the world from the fourth alien's point of view
          case_alien(a4);
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
// Calls: (any_object).draw(_space_ship(2))(_object)(_item) etc...
//        processHits
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
    glPushName(0);// Dummy first name on stack

    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
    glLoadIdentity ();

    /*  create 5x5 pixel picking region near cursor location	*/
    gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
		   MOUSEBOX, MOUSEBOX, viewport);
    if(choice==NOSHIP){
      gluPerspective( SELECTIONFOVY, ratio, NEARSIGHT, FARSIGHT );
    
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(-SELECTIONPOSITIONX,-SELECTIONPOSITIONY,-SELECTIONPOSITIONZ);//ship origin is behind camera
      ships.draw_space_ship(GL_SELECT,SHIP1);
      glTranslatef((2*SELECTIONPOSITIONX),0.0,0.0);
      ships.draw_space_ship2(GL_SELECT,SHIP2);
      glTranslatef(-SELECTIONPOSITIONX,SELECTIONPOSITIONY,SELECTIONPOSITIONZ);
    }else{
      gluPerspective( fovy, ratio, NEARSIGHT, FARSIGHT );
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
 
      place_ships(GL_SELECT);

      if(!alien_view){
        glRotatef(ships.get_x_rot(),0,1,0); 
        glRotatef(ships.get_y_rot(),1,0,0); 
      }

      glTranslatef(ships.get_x_pos(),ships.get_y_pos(),ships.get_z_pos());

      glTranslatef(DISPLACEMENTX,DISPLACEMENTY,-DISPLACEMENTZ); //draw everything 45 units in front

      place_planets(GL_SELECT);
      place_asteroids(GL_SELECT);
      place_items(GL_SELECT);
      place_aliens(GL_SELECT);

      glPopMatrix();
    }
    
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);
    //glutSwapBuffers ();

    hits = glRenderMode (GL_RENDER);
    processHits (hits, selectBuf);
  }
  glutPostRedisplay();
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
// Calls: LoadDIBitmap - load the specifications from each bitmap picture
//    for use as textures in the program
//        build_list - compile the objects for drawing later
//        find_textures - load in the textures for the program
//
//***********************************************************************
void my_init( void ){
  /* attributes */
  glClearColor(0.0, 0.0, 0.0, 1.0); // black background
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Define the 2D texture image.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, TEXTURE_ENV);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, PERSPECTIVE_HINT);
  
  find_textures(); //load in the textures for the program

  build_list(); //compile objects

  glMatrixMode(GL_PROJECTION); //SET UP CAMERA VIEW
  glLoadIdentity();
  gluPerspective(fovy,ratio,NEARSIGHT,FARSIGHT);

  glMatrixMode(GL_MODELVIEW);
  
  glEnable(GL_TEXTURE_2D);
}

//***********************************************************************
//
// Function: my_reshape
//
// Purpose: Allows the user to resize the window and keep the same view under
//              gluPerspective 
//
// Paramaters: int w - the width of the new window
//             int h - the height of the new window 
//
// Calls: 
//
//***********************************************************************
void my_reshape(int w, int h){
  winw=w;
  winh=h;
  ratio=winw/winh;
  glViewport(0, 0, winw, winh);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, ratio, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

//***********************************************************************
//
// Function: display - the glue to the program.
//
// Purpose: Ties everything together. Draws all the objects and screens when
//    necessary. Allows for more asteroids to come into play as the user's
//    score increases. 
//
// Paramaters: None
//
// Calls: (any_object).draw(_space_ship(2))(_object)(_item) etc...
//        Ship::decr_fuel
//        Ship::get_fuel
//        Text::pick_ship
//        Text::show_score
//
//***********************************************************************
void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor4f(1.0,0.2,0.0,1.0);

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  gluPerspective(fovy,ratio,NEARSIGHT,FARSIGHT); //will ALLOW ZOOMING
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if(alien_view){
    glTranslatef(-(ap->get_x()),-(ap->get_y()),-(ap->get_z()));
  }

  place_ships(GL_RENDER);

  if(!alien_view){
    glRotatef(ships.get_x_rot(),0,1,0); 
    glRotatef(ships.get_y_rot(),1,0,0); 
    glTranslatef(DISPLACEMENTX,DISPLACEMENTY,-DISPLACEMENTZ); //draw everything 45 units in front
    glTranslatef(ships.get_x_pos(),ships.get_y_pos(),ships.get_z_pos()); //trying
  }else{
    glTranslatef(THIRDPERSONX,THIRDPERSONY,-THIRDPERSONZ);
  }

  place_planets(GL_RENDER);
  place_asteroids(GL_RENDER);
  place_items(GL_RENDER);
  place_aliens(GL_RENDER);

  handle_fuel();

  detect_collisions();
  
  if(choice==NOSHIP){
    text.pick_ship(winw,winh,TEXTSCREEN,ships,FIRSTSHIP,SECONDSHIP);
  }else{
    text.show_score(paused,lose,winw,winh,TEXTSCREEN,score,ships);
  }  

  glutSwapBuffers();
}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize (winw, winh);
  glutInitWindowPosition (POSITION, POSITION);
  glutCreateWindow("Asteroid Mining"); //initialize the name of the window to be "Asteroid Mining"
  glutReshapeFunc(my_reshape);
  glutMouseFunc (mouse);
  glutKeyboardFunc (KeyPunch);	// Set function for key command processing 
  glutSpecialFunc( SpecialKeyFunc );
  my_init();

  glutDisplayFunc(display);
  glutTimerFunc(0,my_timer,0);

  text.post_message(winw,winh,TEXTSCREEN);
  glutMainLoop(); //necessary for proper display

  return(EXIT_SUCCESS);
}
