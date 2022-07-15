//*********************************************************************
//
//  Program: hw3 - model a 3D solar system for Asteroid Mining game. 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the implementation file for the classes that produce
//    our objects in the game. Each class has its own position and spin
//    values that will allow it to move independently of other objects. 
//
//  Last Updated: 10/26/2011
//
//*********************************************************************

#include "objects.h"

//Constructor
Ship::Ship(){
  x_pos=ZERO;
  y_pos=ZERO;
  z_pos=ZERO;
  x_rot=ZERO;
  move_x=ZERO;
  move_y=ZERO;
  movement=ZERO;
  look_left_right=ZERO;
  look_up_down=ZERO;
  fuel=MAXFUEL;
  radius=1.5;
}

//accessor
float Ship::get_radius(){
  return radius;
}

void Ship::reset(){
  x_pos=ZERO;
  y_pos=ZERO;
  z_pos=ZERO;
  x_rot=ZERO;
  move_x=ZERO;
  move_y=ZERO;
  movement=ZERO;
  look_left_right=ZERO;
  look_up_down=ZERO;
  fuel=MAXFUEL;
  radius=1.5;
}

void Ship::reset_view(){
  look_left_right=ZERO;
  look_up_down=ZERO;
}

//accessor
int Ship::get_look_left_right(){
  return look_left_right;
}

//accessor
int Ship::get_look_up_down(){
  return look_up_down;
}

//accessor
int Ship::get_fuel(){
 return fuel;
}

//*****************************************************
// Function: incr_fuel
//
// Purpose: When fuel is clicked on in the world, this
//   adds the fuel to the ship's tank, (increase fuel value)
//
//*****************************************************
void Ship::incr_fuel(){
  fuel+=ADDFUEL;
  if(fuel>MAXFUEL){
    fuel=MAXFUEL;
  }
}

//accessor
float Ship::get_movement(){
  return movement;
}

//*****************************************************
// Function: decr_fuel
//
// Purpose: If the ship is moving, it lowers the ship's fuel
//   value
//
//*****************************************************
void Ship::decr_fuel(){
  fuel-=SUBTRACTFUEL;
}

//accessor
float Ship::get_x_pos(){
  return x_pos;
}

//accessor
float Ship::get_y_pos(){
  return y_pos;
}

//accessor
float Ship::get_z_pos(){
  return z_pos;
}

//accessor
float Ship::get_x_rot(){
  return x_rot;
}

//accessor
float Ship::get_y_rot(){
  return y_rot;
}

//*****************************************************
// Function: look_left
//
// Purpose: If the ship is in first person view, you can 
//    look left while still maintaining the ships movement
//
//*****************************************************
void Ship::look_left(){
  look_left_right-=RINCREMENT;
  if(look_left_right<CIRCLE-CIRCLE){
    look_left_right+=CIRCLE;
  }
}

//*****************************************************
// Function: look_right
//
// Purpose: If the ship is in first person view, you can 
//    look right while still maintaining the ships movement
//
//*****************************************************
void Ship::look_right(){
  look_left_right+=RINCREMENT;
  if(look_left_right>CIRCLE-1){
    look_left_right-=CIRCLE;
  }
}

//*****************************************************
// Function: look_up
//
// Purpose: If the ship is in first person view, you can 
//    look up while still maintaining the ships movement
//
//*****************************************************
void Ship::look_up(){
  look_up_down-=RINCREMENT;
  if(look_up_down<CIRCLE-CIRCLE){
    look_up_down+=CIRCLE;
  }
}

//*****************************************************
// Function: look_down
//
// Purpose: If the ship is in first person view, you can 
//    look down while still maintaining the ships movement
//
//*****************************************************
void Ship::look_down(){
  look_up_down+=RINCREMENT;
  if(look_up_down>CIRCLE-1){
    look_up_down-=CIRCLE;
  }
}

//*****************************************************
// Function: incr_x_rot
//
// Purpose: When the user has chosen the blue ship (ship1),
//   this allows the ship to turn right
//
//*****************************************************
void Ship::incr_x_rot(){
  x_rot+=RINCREMENT;
  if(x_rot>CIRCLE-1){
    x_rot-=CIRCLE;
  }
}
  
//*****************************************************
// Function: decr_x_rot
//
// Purpose: When the user has chosen the blue ship (ship1),
//   this allows the ship to turn left
//
//*****************************************************
void Ship::decr_x_rot(){
  x_rot-=RINCREMENT;
  if(x_rot<CIRCLE-CIRCLE){
    x_rot+=CIRCLE;
  }
}

//*****************************************************
// Function: incr_y_rot
//
// Purpose: When the user has chosen the blue ship (ship2),
//   this allows the ship to turn down
//
//*****************************************************
void Ship::incr_y_rot(){
  y_rot+=RINCREMENT;
  if(y_rot>CIRCLE-1){
    y_rot-=CIRCLE;
  }
}

//*****************************************************
// Function: decr_y_rot
//
// Purpose: When the user has chosen the blue ship (ship2),
//   this allows the ship to turn up
//
//*****************************************************
void Ship::decr_y_rot(){
  y_rot-=RINCREMENT;
  if(y_rot<CIRCLE-CIRCLE){
    y_rot+=CIRCLE;
  }
}

//*****************************************************
// Function: speed_up
//
// Purpose: Allows the user to move the ship faster through
//   space
//
//*****************************************************
void Ship::speed_up(){
  movement+=INCREMENT;
  if(movement>MAXSPEED){
    movement=MAXSPEED;
  }
}

//*****************************************************
// Function: update_movement
//
// Calls: return_value()
//
// Purpose: Computes the x, y, and z movements that the 
//   ship is moving in using the current angles of the 
//   ship and the current speed of the ship. It then updates
//   the x, y, and z positions of the ship in space to make 
//   the ship actually move.
//
//*****************************************************
void Ship::update_move(){
  int t_x_rot,t_y_rot;
  t_x_rot=(int)x_rot%(CIRCLE/4);
  t_y_rot=(int)y_rot%(CIRCLE/4);
  float x,y,z;
  x=return_value(t_x_rot,x_rot);
  y=return_value(t_y_rot,y_rot);

  /*FIXES TO MY AWEFUL MATH ABILITIES*/
  if(movement!=0.0){
    z=sqrt(1.0-(x*x)-(y*y)); //movement is 1.0
  }

  if((x_rot>=(CIRCLE/4))&&(x_rot<=(3*CIRCLE/4))){
    z=-z;
  }
  if((y_rot>=(CIRCLE/4))&&(y_rot<=(3*CIRCLE/4))){
    z=-z;
  }

  if(x_rot==(CIRCLE/2)){
    x=0; z=-1;
  }

  if(y_rot==(CIRCLE/2)){
    y=0; z=-1;
  }

  if((x==1)||(x==-1)||(y==1)||(y==-1)){
    z=0;
  }

  if((y_rot>=(CIRCLE/2))||(y_rot>=CIRCLE)){
    if(y<0.0){
      y=-y;
    }
  }else if((y_rot>=0)||(y_rot<=(CIRCLE/2))){
    if(y>0.0){
      y=-y;
    }
  }/*END FIXES*/

  /*ADD MOVEMENT FROM ROTATIONAL CHANGES*/
  x_pos-=(movement*x);
  y_pos-=(movement*y);
  z_pos+=(movement*z);

  /*ADD MOVEMENT FROM VELOCITY CHANGES*/
  x_pos+=move_x;
  y_pos+=move_y;
}

//*****************************************************
// Function: return_value
//
// Parameters: int &t - a temporary rotation
//             float &rot - the rotation corresponding to 
//                   the temporary one.
//
// Purpose: When the user has chosen the blue ship (ship1),
//   this allows the ship to turn right
//
//*****************************************************
float Ship::return_value(int &t,float &rot){
  float temp;
  if(t==ZERO){
    temp=ZERO;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==5){
    temp=0.0871556;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==10){
    temp=0.1736481;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==15){
    temp=0.2588189;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==20){
    temp=0.3420200;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==25){
    temp=0.4226182;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==30){
    temp=0.5000000;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==35){
    temp=0.5735763;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==40){
    temp=0.6427875;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==45){
    temp=0.7071067;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==50){
    temp=0.7660443;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==55){
    temp=0.8191519;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==60){
    temp=0.8660253;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==65){
    temp=0.9063077;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==70){
    temp=0.9396925;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==75){
    temp=0.9659257;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==80){
    temp=0.9848077;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==85){
    temp=0.9961946;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }else if(t==90){
    temp=1.0;
    if(((rot>=(CIRCLE/4))&&(rot<=(CIRCLE/2)))||((rot>=(3*CIRCLE/4))&&(rot<=CIRCLE))){
      temp=1.0-temp;
    }
    if(x_rot>=(CIRCLE/2)){
      temp*=-1;
    }
  }
  return temp;
}

//*****************************************************
// Function: slow_down
//
// Purpose: Allows the user to stop the ship completely,
//   or move backwards.
//
//*****************************************************
void Ship::slow_down(){
  movement-=INCREMENT;
  if(movement<-INCREMENT){
    movement=-INCREMENT;
  }
}

//accessor
float Ship::get_move_x(){
  return move_x;
}

//accessor
float Ship::get_move_y(){
  return move_y;
}

//*****************************************************
// Function: incr_move_x
//
// Purpose: If the user chose the red ship (ship2), this
//   allows the user to move right or stop movement to the
//   left
//
//*****************************************************
void Ship::incr_move_x(){
  if(move_x<ZERO){
    move_x=ZERO;
  }else{
    move_x+=INCREMENT;
    if(move_x>=MAXSPEED){
      move_x=MAXSPEED;
    }
  }
}

//*****************************************************
// Function: decr_move_x
//
// Purpose: If the user chose the red ship (ship2), this
//   allows the user to move left or stop movement to the
//   right
//
//*****************************************************
void Ship::decr_move_x(){
  if(move_x>ZERO){
    move_x=ZERO;
  }else{
    move_x-=INCREMENT;
    if(move_x<=-MAXSPEED){
      move_x=-MAXSPEED;
    }
  }
}

//*****************************************************
// Function: incr_move_y
//
// Purpose: If the user chose the blue ship (ship1), this
//   allows the user to move up or stop movement downward
//
//*****************************************************
void Ship::incr_move_y(){
  if(move_y<ZERO){
    move_y=ZERO;
  }else{
    move_y+=INCREMENT;
    if(move_y>=MAXSPEED){
      move_y=MAXSPEED;
    }
  }
}

//*****************************************************
// Function: decr_move_y
//
// Purpose: If the user chose the blue ship (ship1), this
//   allows the user to move down or stop movement upward
//
//*****************************************************
void Ship::decr_move_y(){
  if(move_y>ZERO){
    move_y=ZERO;
  }else{
    move_y-=INCREMENT;
    if(move_y<=-MAXSPEED){
      move_y=-MAXSPEED;
    }
  }
}

//*****************************************************
// Function: draw_space_ship
//
// Parameters: GLenum mode - either GL_RENDER or GL_SELECT
//             int name - the objects name
//
// Purpose: Draws the blue space ship (ship1)
//
//*****************************************************
void Ship::draw_space_ship(GLenum mode, const int name){ 
  glDisable(GL_TEXTURE_2D);
  
  if(mode==GL_SELECT){
    glLoadName(name);
  }

  glBegin(GL_TRIANGLE_FAN);{ //top of ship
    glColor4f(1.0,1.0,1.0,1.0);
    glVertex3f(0.0,0.0,-3.0); //front of ship
    glColor4f(0.0,0.2,1.0,1.0); //blue
   //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
    glVertex3f(-0.4,0.0,0.0);
    glVertex3f(0.0,1.0,2.0); //back top of ship
    glVertex3f(0.4,0.0,0.0);
     //right most point
    glVertex3f(1.0,-1.0,0.5); 
  }glEnd();
  glBegin(GL_TRIANGLE_FAN);{ //bottom of ship
    glColor4f(1.0,1.0,1.0,1.0);
    glVertex3f(0.0,0.0,-3.0); //front of ship
    glColor4f(0.0,0.2,1.0,1.0); //blue
    //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
    //back bottom of ship
    glVertex3f(0.0,-0.5,0.1); //replacing above
    //right most point
    glVertex3f(1.0,-1.0,0.5);//replacing above
  }glEnd();
  glBegin(GL_TRIANGLE_FAN);{ //back of ship
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1);//replacing above
    glVertex3f(-0.4,0.0,0.0);
    glVertex3f(0.0,1.0,2.0); //back top of ship
    glVertex3f(0.4,0.0,0.0);
  }glEnd();
  glBegin(GL_POLYGON);{ //back left booster
    glColor4f(0.7,0.2,0.0,1.0); //dark red-orange
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1);//replacing above
    glVertex3f(-0.4,0.0,0.0);
    //glVertex3f(-0.5,-0.25,-1.0); //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
  }glEnd();
  glBegin(GL_POLYGON);{ //back right booster
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1); //replacing above
    glVertex3f(0.4,0.0,0.0);
    //glVertex3f(-0.5,-0.25,1.0); //right most point
    glVertex3f(1.0,-1.0,0.5); //replacing above
  }glEnd();
  glBegin(GL_LINE_STRIP);{
    glColor4f(0.0,0.0,0.0,1.0);
    glVertex3f(0.4,0.0,0.0);
    glVertex3f(0.0,0.0,-3.0);
    glVertex3f(-0.4,0.0,0.0);
  }glEnd();
    
  glEnable(GL_TEXTURE_2D);
}

//*****************************************************
// Function: draw_space_ship2
//
// Parameters: GLenum mode - either GL_RENDER or GL_SELECT
//             int name - the objects id
//
// Purpose: Draws the red space ship (ship2)
//
//*****************************************************
void Ship::draw_space_ship2(GLenum mode, const int name){ 
  glDisable(GL_TEXTURE_2D);

  if(mode==GL_SELECT){
    glLoadName(name);
  }
    
  glBegin(GL_TRIANGLE_FAN);{ //top of ship
    glColor4f(0.2,0.2,0.65,1.0);
    glVertex3f(0.0,0.0,-3.0); //front of ship
    glColor4f(1.0,0.2,0.0,1.0); //red
   //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
    glVertex3f(-0.4,0.0,0.0);
    glVertex3f(0.0,1.0,2.0); //back top of ship
    glVertex3f(0.4,0.0,0.0);
     //right most point
    glVertex3f(1.0,-1.0,0.5); 
  }glEnd();
  glBegin(GL_TRIANGLE_FAN);{ //bottom of ship
    glColor4f(0.2,0.2,0.65,1.0);
    glVertex3f(0.0,0.0,-3.0); //front of ship
    glColor4f(1.0,0.2,0.0,1.0); //red
    //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
    //back bottom of ship
    glVertex3f(0.0,-0.5,0.1); //replacing above
    //right most point
    glVertex3f(1.0,-1.0,0.5);//replacing above
  }glEnd();
  glBegin(GL_TRIANGLE_FAN);{ //back of ship
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1);//replacing above
    glVertex3f(-0.4,0.0,0.0);
    glVertex3f(0.0,1.0,2.0); //back top of ship
    glVertex3f(0.4,0.0,0.0);
  }glEnd();
  glBegin(GL_POLYGON);{ //back left booster
    glColor4f(0.0,0.7,0.2,1.0); //greenish blue
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1);//replacing above
    glVertex3f(-0.4,0.0,0.0);
    //glVertex3f(-0.5,-0.25,-1.0); //left most point
    glVertex3f(-1.0,-1.0,0.5); //replacing above
  }glEnd();
  glBegin(GL_POLYGON);{ //back right booster
    //glVertex3f(-0.1,-0.15,0.0); //back bottom of ship
    glVertex3f(0.0,-0.5,0.1); //replacing above
    glVertex3f(0.4,0.0,0.0);
    //glVertex3f(-0.5,-0.25,1.0); //right most point
    glVertex3f(1.0,-1.0,0.5); //replacing above
  }glEnd();
  glBegin(GL_LINE_STRIP);{
    glColor4f(0.0,0.0,0.0,1.0);
    glVertex3f(0.4,0.0,0.0);
    glVertex3f(0.0,0.0,-3.0);
    glVertex3f(-0.4,0.0,0.0);
  }glEnd();
    
  glEnable(GL_TEXTURE_2D);
}

//constructor
Mysun::Mysun(){
  radius=20.0;
  slices_stacks=SS;
}

float Mysun::get_radius(){
  return radius;
}

//*****************************************************
// Function: draw
//
// Parameters: GLenum mode - either GL_RENDER or GL_SELECT
//             int name - the obects id
//
// Purpose: draws all astronomical objects in the program
//   (The sun class is the parent to all other terrestrial objects)
//
//*****************************************************
void Mysun::draw(GLenum mode,int name ){
  if(mode==GL_SELECT){
    glLoadName(name);
  }
  GLUquadric *qobj=gluNewQuadric();
  gluQuadricTexture(qobj,GL_TRUE); //allow quadric to map texture coordinates
  gluSphere(qobj,radius,slices_stacks,slices_stacks);
  gluDeleteQuadric(qobj);
}

//constructor
Space::Space(){
  radius=200;
  slices_stacks=70;
}

//constructor
Mercury::Mercury(){
  radius=4.0;
  slices_stacks=SS;
  x_pos=34.0;
  rot_incr=3.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Mercury::reset(){
  radius=4.0;
  slices_stacks=SS;
  x_pos=34.0;
  rot_incr=3.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//*****************************************************
// Function: unmineable
//
// Purpose: Mainly for asteroid objects (child of Mercury)
//   When an asteroid is clicked it becomes unmineable.
//
//*****************************************************
void Mercury::unmineable(){
  mineable=false;
}

//accessor
bool Mercury::get_mine_status(){
  return mineable;
}

//accessor
int Mercury::get_x_axis(){
  return x_axis;
}

//accessor
int Mercury::get_y_axis(){
  return y_axis;
}

//accessor
int Mercury::get_z_axis(){
  return z_axis;
}

//accessor
float Mercury::get_x_pos(){
  return x_pos;
}

//accessor
float Mercury::get_total_rot(){
  return total_rot;
}

//*****************************************************
// Function: update_orbit
//
// Purpose: increases the rotation angle of the terrestrial
//   object to make it orbit the sun.
//
//*****************************************************
void Mercury::update_orbit( void ){
  total_rot+=rot_incr;
  if(total_rot>CIRCLE-1){
    total_rot-=CIRCLE;
  }
}

//constructor
Venus::Venus(){
  radius=6.0;
  slices_stacks=SS;
  x_pos=54.0;
  rot_incr=6.0;
  total_rot=0.0;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Venus::reset(){
  radius=6.0;
  slices_stacks=SS;
  x_pos=54.0;
  rot_incr=6.0;
  total_rot=0.0;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//constructor
Earth::Earth(){
  radius=8.0;
  slices_stacks=SS;
  x_pos=78.0;
  rot_incr=2.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Earth::reset(){
  radius=8.0;
  slices_stacks=SS;
  x_pos=78.0;
  rot_incr=2.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//constructor
Mars::Mars(){
  radius=5.0;
  slices_stacks=SS;
  x_pos=101.0;
  rot_incr=4.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Mars::reset(){
  radius=5.0;
  slices_stacks=SS;
  x_pos=101.0;
  rot_incr=4.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//constructor
Jupiter::Jupiter(){
  radius=12.0;
  slices_stacks=SS;
  x_pos=128.0;
  rot_incr=1.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Jupiter::reset(){
  radius=12.0;
  slices_stacks=SS;
  x_pos=128.0;
  rot_incr=1.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//constructor
Uranus::Uranus(){
  radius=7.0;
  slices_stacks=SS;
  x_pos=157.0;
  rot_incr=5.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

void Uranus::reset(){
  radius=7.0;
  slices_stacks=SS;
  x_pos=157.0;
  rot_incr=5.0;
  total_rot=ZERO;
  x_axis=z_axis=ZERO;
  y_axis=1;
}

//*****************************************************
// Function: Asteroid (constructor)
//
// Purpose: randomly computes the position in space, its radius,
//   its orbit speed, and direction of orbit.
//   
//
//*****************************************************
Asteroid::Asteroid(){
  int j=rand();
  int temp=j%6;
  int temp1=j%4;
  int temp2=j%2;

  mineable=true;
  radius=temp1; //4 sizes different sizes to be created as

  if(temp2==0){
    x_pos=j%100; //100 random starting positions
    if(x_pos<20){ //make sure it isn't where the sun is
      x_pos+=20;
    }
  }else{
    x_pos=-(j%100);
    if(x_pos>-20){
      x_pos-=20;
    }
  }

  if(temp2==ZERO){ //randomly choose to rotate clockwise or counter-clockwise
    rot_incr=temp2+1;
  }else{
    rot_incr=-(temp2+1);
  }
  //randomly choose axis to spin around
  if(temp==ZERO){ //x-axis
    x_axis=1; 
    y_axis=z_axis=ZERO;
  }else if(temp==1){ //all axese
    y_axis=x_axis=z_axis=1;
  }else if(temp==2){ //z-axis
    z_axis=1;
    x_axis=y_axis=ZERO;
  }else if(temp==3){ //x and y-axis
    x_axis=y_axis=1;
    z_axis=ZERO;
  }else if(temp==4){ //x and z-axis
    x_axis=z_axis=1;
    y_axis=ZERO;
  }else if(temp==5){ //y and z-axis
    y_axis=z_axis=1;
    z_axis=ZERO;
  }    

  total_rot=ZERO;
  slices_stacks=30.0;
}

//*****************************************************
// Function: reset
//
// Purpose: Recalculates what the constructor does to make
//   recreate the asteroid somewhere else after it is destroyed.
//
//*****************************************************
void Asteroid::reset(){
  //Asteroid();
  int j=rand();
  int temp=j%6;
  int temp1=j%4;
  int temp2=j%2;

  mineable=true;
  radius=temp1; //4 sizes different sizes to be created as

  if(temp2==ZERO){
    x_pos=j%100; //100 random starting positions
    if(x_pos<20){ //make sure it isn't where the sun is
      x_pos+=20;
    }
  }else{
    x_pos=-(j%100);
    if(x_pos>-20){
      x_pos-=20;
    }
  }
  if(temp2==ZERO){ //randomly choose to rotate clockwise or counter-clockwise
    rot_incr=temp2+1;
  }else{
    rot_incr=-(temp2+1);
  }
  //randomly choose axis to spin around
  if(temp==ZERO){ //x-axis
    x_axis=1; 
    y_axis=z_axis=ZERO;
  }else if(temp==1){ //all axese
    y_axis=x_axis=z_axis=1;
  }else if(temp==2){ //z-axis
    z_axis=1;
    x_axis=y_axis=ZERO;
  }else if(temp==3){ //x and y-axis
    x_axis=y_axis=1;
    z_axis=ZERO;
  }else if(temp==4){ //x and z-axis
    x_axis=z_axis=1;
    y_axis=ZERO;
  }else if(temp==5){ //y and z-axis
    y_axis=z_axis=1;
    z_axis=ZERO;
  }    

  total_rot=ZERO;
  slices_stacks=30.0;
}

//*****************************************************
// Function: Items (constructor)
//
// Purpose: randomly computes the position in space.
//   
//
//*****************************************************
Items::Items(){
  int temp=rand();
  int temp2=rand();
  int temp3=rand();
  int temp4=rand();

  x=temp%170; //random within our program
  y=temp%170;
  z=temp%170;

  if(temp2%2==ZERO){
    x=-x;
  }
  if(temp3%2==ZERO){
    y=-y;
  }
  if(temp4%2==ZERO){
    z=-z;
  }
  
  if(x<22.0){ //not within the sun either
    x+=21.0;
  }
  if(y<22.0){ //not within the sun either
    y+=21.0;
  }
  if(z<22.0){ //not within the sun either
    z+=21.0;
  }
}

//*****************************************************
// Function: Asteroid (constructor)
//
// Purpose: draws the fuel object in space
//
//*****************************************************
void Items::draw_fuel(GLenum mode, int name){
  if(mode==GL_SELECT){
    glLoadName(name);
  }
  glBegin(GL_POLYGON);{
    glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(0, 0);
    glVertex3f(1.0,-1.0,1.0);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0,-1.0,1.0);
    glTexCoord2f(1, 1);
    glVertex3f(-1.0,1.0,1.0);
    glTexCoord2f(0, 1);
  }glEnd();
  glBegin(GL_POLYGON);{
    glVertex3f(-1.0,1.0,1.0);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0,-1.0,1.0);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0,-1.0,-1.0);
    glTexCoord2f(1, 1);
    glVertex3f(-1.0,1.0,-1.0);
    glTexCoord2f(0, 1);
  }glEnd();
  glBegin(GL_POLYGON);{
    glVertex3f(1.0,-1.0,1.0);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0,-1.0,1.0);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0,-1.0,-1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0,-1.0,-1.0);
    glTexCoord2f(0, 1);
  }glEnd();
  glBegin(GL_POLYGON);{
    glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(0, 0);
    glVertex3f(1.0,-1.0,1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0,-1.0,-1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0,1.0,-1.0);
    glTexCoord2f(0, 1);
  }glEnd();
  glBegin(GL_POLYGON);{
    glVertex3f(1.0,-1.0,-1.0);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0,-1.0,-1.0);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0,1.0,-1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0,1.0,-1.0);
    glTexCoord2f(0, 1);
  }glEnd();
  glBegin(GL_POLYGON);{
    glVertex3f(-1.0,1.0,-1.0);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0,1.0,1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0,1.0,-1.0);
    glTexCoord2f(0, 1);//END CUBE 1
  }glEnd();
}

//accessor
float Items::get_x(){
  return x;
}

//accessor
float Items::get_y(){
  return y;
}

//accessor
float Items::get_z(){
  return z;
}

//*****************************************************
// Function: reset
//
// Purpose: After fuel has been used up, relocate it 
//   to within the sun object so it cannot be used again.
//
//*****************************************************
void Items::reset(){
  x=y=z=ZERO;
}

void Items::new_items(){
  int temp=rand();
  int temp2=rand();
  int temp3=rand();
  int temp4=rand();

  x=temp%170; //random within our program
  y=temp%170;
  z=temp%170;

  if(temp2%2==ZERO){
    x=-x;
  }
  if(temp3%2==ZERO){
    y=-y;
  }
  if(temp4%2==ZERO){
    z=-z;
  }
  
  if(x<22.0){ //not within the sun either
    x+=21.0;
  }
  if(y<22.0){ //not within the sun either
    y+=21.0;
  }
  if(z<22.0){ //not within the sun either
    z+=21.0;
  }
}

//*****************************************************
// Function: Asteroid (constructor)
//
// Purpose: randomly computes the position in space,
//   its speed, and direction of movement.
//   
//
//*****************************************************
Alien::Alien(){
  int temp=rand();
  int temp2=rand();
  int temp3=rand();
  int temp4=rand();
  x=temp%170;
  y=temp%170;
  z=temp%170;
  start_x=x;//trying
  start_y=y;//trying
  start_z=z;//trying
  direction=0;

  if(x<22.0){ //not within the sun either
    x+=21.0;
  }
  if(y<22.0){ //not within the sun either
    y+=21.0;
  }
  if(z<22.0){ //not within the sun either
    z+=21.0;
  }

  if(temp2%2==ZERO){
    x=-x;
  }
  if(temp3%2==ZERO){
    y=-y;
  }
  if(temp4%2==ZERO){
    z=-z;
  }

  move_x=ZERO;
  move_y=ZERO;
  move_z=ZERO;
  TextureWrapVert=6;
  TextureWrapHoriz=6;

  MajorRadius = 3.0;
  MinorRadius = 1.0;
  NumWraps = 10;
  NumPerWrap = 8;
  PI2 = 2.0f*3.1415926535;
  radius=1.0;
}

void Alien::reset(){
  int temp=rand();
  int temp2=rand();
  int temp3=rand();
  int temp4=rand();
  x=temp%170;
  y=temp%170;
  z=temp%170;
  start_x=x;//trying
  start_y=y;//trying
  start_z=z;//trying
  direction=0;

  if(x<22.0){ //not within the sun either
    x+=21.0;
  }
  if(y<22.0){ //not within the sun either
    y+=21.0;
  }
  if(z<22.0){ //not within the sun either
    z+=21.0;
  }

  if(temp2%2==ZERO){
    x=-x;
  }
  if(temp3%2==ZERO){
    y=-y;
  }
  if(temp4%2==ZERO){
    z=-z;
  }

  move_x=ZERO;
  move_y=ZERO;
  move_z=ZERO;
  TextureWrapVert=6;
  TextureWrapHoriz=6;

  MajorRadius = 3.0;
  MinorRadius = 1.0;
  NumWraps = 10;
  NumPerWrap = 8;
  PI2 = 2.0f*3.1415926535;
  radius=1.0;
}

float Alien::get_radius(){
  return radius;
}

//accessor
float Alien::get_x(){
  return x;
}

//accessor
float Alien::get_y(){
  return y;
}

//accessor
float Alien::get_z(){
  return z;
}
/*****************************************************

// Function: putVertTexture
// Purpose: Helps draw the alien objects (as a torus)
//   gives the torus texture coordinates
 * The triangles or quadrilaterals are wrapped around the
 * torus in a single long strip.    See figure 13 Chapter I
 * in the book mentioned below.
 *
 *
 * Author: Samuel R. Buss
 *
 * Software accompanying the book
 *		3D Computer Graphics: A Mathematical Introduction with OpenGL,
 *		by S. Buss, Cambridge University Press, 2003.
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 *   restriction, but if you modify it, please change the filenames to
 *   prevent confusion between different versions.
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
********************************************************/
void Alien::putVertTexture(int i,int j){
  float wrapFrac = (j%NumPerWrap)/(float)NumPerWrap;
  float wrapFracTex = (float)j/(float)NumPerWrap;
  float phi = PI2*wrapFrac;
  float thetaFrac = ((float)(i%NumWraps)+wrapFracTex)/(float)NumWraps;
  float thetaFracTex = ((float)i+wrapFracTex)/(float)NumWraps;
  float theta = PI2*thetaFrac;
  float sinphi = sin(phi);
  float cosphi = cos(phi);
  float sintheta = sin(theta);
  float costheta = cos(theta);
  float y = MinorRadius*sinphi;
  float r = MajorRadius + MinorRadius*cosphi;
  float x = sintheta*r;
  float z = costheta*r;

  glTexCoord2f( wrapFracTex*(float)TextureWrapVert, thetaFracTex*(float)TextureWrapHoriz );
  glNormal3f(sintheta*cosphi, sinphi, costheta*cosphi);
  glVertex3f(x,y,z);
}

/********************************************************
//Function: draw
//Purpose: Actually draws the alien objects
 * The triangles or quadrilaterals are wrapped around the
 * torus in a single long strip.    See figure 13 Chapter I
 * in the book mentioned below.
 *
 *
 * Author: Samuel R. Buss 
 *
 * Software accompanying the book
 *		3D Computer Graphics: A Mathematical Introduction with OpenGL,
 *		by S. Buss, Cambridge University Press, 2003.
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 *   restriction, but if you modify it, please change the filenames to
 *   prevent confusion between different versions.
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
********************************************************/
void Alien::draw(){
  for (int i=0; i<NumWraps; i++ ) {
    glBegin(GL_QUAD_STRIP);
    for (int j=0; j<=NumPerWrap; j++) {
      putVertTexture(i, j);
      putVertTexture(i+1,j);
    }
    glEnd();
  }
}

//*****************************************************
// Function: look_left
//
// Purpose: Controls the movement of the aliens
//
//*****************************************************
void Alien::update_movement(){
    if(direction==0){//positive x direction
      x+=INCREMENT;
      if(((abs(x-start_x))>39.5)&&((abs(x-start_x))<40.5)){
        direction=2;
      }
    }
    if(direction==3){//negative x direction
      x-=INCREMENT;
      if((x>start_x-0.5)&&(x<start_x+0.5)){
        direction=5;
      }
    }
    if(direction==2){
      z+=INCREMENT;
      if(((abs(z-start_z))>39.5)&&((abs(x-start_x))<40.5)){
        direction=3;
      }
    }
    if(direction==5){
      z-=INCREMENT;
      if((z>start_z-0.5)&&(z<start_z+0.5)){
        direction=0;
      }
    }
}
