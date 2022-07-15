//*********************************************************************
//
//  Program: hw3 - model a 3D solar system for Asteroid Mining game. 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the header file for the classes that produce
//    our objects in the game. Each class has its own position and spin
//    values that will allow it to move independently of other objects.
//    Function headers in implementation file 
//
//  Last Updated: 10/26/2011
//
//*********************************************************************

#ifndef OBJECTS_H
#define OBJECTS_H

#include <math.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

#define MAXFUEL 1500 //maximum amount of fuel the ship can have
#define ADDFUEL 400 //how much a tank of fuel gives the ship
#define SUBTRACTFUEL 1 //how much fuel a tank loses when it is moving
#define SS 50.0 //number of slices and stacks to draw on our quadrics
#define MAXSPEED 3.0 //fastest speed the ship can go
#define RINCREMENT 5.0 //incremental angle for moving ship around
#define CIRCLE 360 //degrees in a circle
#define INCREMENT 1.0 //value to increase or decrease movements.
#define ZERO 0.0 //zeros

class Ship{
  public:
    Ship();
    int get_look_left_right();
    int get_look_up_down();
    void look_up();
    void look_down();
    void look_left();
    void look_right();
    void reset_view();
    void reset();
    float return_value(int &t,float &rot);
    float get_y_pos();
    float get_x_pos();
    float get_z_pos();
    float get_move_x();
    float get_move_y();
    void incr_move_x();
    void decr_move_x();
    void incr_move_y();
    void decr_move_y();
    void speed_up();
    void slow_down();
    float get_movement();
    float get_x_rot();
    float get_y_rot();
    void incr_x_rot();
    void decr_x_rot();
    void incr_y_rot();
    void decr_y_rot();
    void update_move();
    int get_fuel();
    float get_radius();
    void incr_fuel();
    void decr_fuel();
    void draw_space_ship(GLenum mode, const int name);
    void draw_space_ship2(GLenum mode, const int name);
  private:
    float x_pos; 
    float y_pos; 
    float z_pos; 
    float x_rot; 
    float y_rot; 
    float radius;
    float movement; 
    float move_x,move_y;
    int fuel;
    int look_left_right;
    int look_up_down;
};

class Mysun{
  public:
    Mysun();
    float get_radius();
    void draw(GLenum mode,int name);
  protected:
    float radius,slices_stacks;
};

class Space:public Mysun{
  public:
    Space();
  private:
};

class Mercury:public Mysun{ //parent for planets and asteroids
  public:
    Mercury();
    void reset();
    float get_x_pos();
    float get_total_rot();
    bool get_mine_status();
    void unmineable();
    int get_x_axis();
    int get_y_axis();
    int get_z_axis();
    void update_orbit( void );
  protected:
    float x_pos,rot_incr,total_rot;
    bool mineable;
    int x_axis,y_axis,z_axis;
};

class Venus:public Mercury{
  public:
    Venus();
    void reset();
  private:
};

class Earth:public Mercury{
  public:
    Earth();
    void reset();
  private:
};

class Mars:public Mercury{
  public:
    Mars();
    void reset();
  private:
};

class Jupiter:public Mercury{
  public:
    Jupiter();
    void reset();
  private:
};

class Uranus:public Mercury{
  public:
    Uranus();
    void reset();
  private:
};

class Asteroid:public Mercury{
  public:
    Asteroid();
    void reset();
  private:
};

class Items{
  public:
    Items();
    float get_x();
    float get_y();
    float get_z();
    void reset();
    void new_items();
    void draw_fuel(GLenum mode, int name);
  private:
    float x,y,z;
};

class Alien{
  public:
    Alien();
    float get_x();
    float get_y();
    float get_z();
    void reset();
    float get_radius();
    void putVertTexture(int i,int j);
    void draw();
    void update_movement();
  private:
    float x,y,z;
    float start_x,start_y,start_z;
    int direction;
    float move_x,move_y,move_z;
    int TextureWrapVert;
    int TextureWrapHoriz;
    float MajorRadius;
    float MinorRadius;
    int NumWraps;
    int NumPerWrap;
    float PI2;
    float radius;
};

#endif
