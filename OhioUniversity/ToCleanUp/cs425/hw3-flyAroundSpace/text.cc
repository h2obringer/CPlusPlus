//*********************************************************************
//
//  Program: hw3 - model a 3D solar system for Asteroid Mining game. 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the implementation file for the functions that will 
//    produce any of the on screen messages for our program.
//
//  Last Updated: 10/26/2011
//
//*********************************************************************

#include "text.h"

//constructor
Text::Text(){
  line_height=300;
  sleep_time=5;
}

//*****************************************************
// Function: reset
//
// Parameters: int n - the integer to be converted into a string
//
// Purpose: This converts the parameter into type string
//
//*****************************************************
string Text::convert_int_to_string(int n){
  ostringstream out;
  out << n;
  return out.str();
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
void Text::drawText(int x, int y, char *message)
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
//    paused or if the game has been lost. Also displays the amount of fuel the
//    ship has
//
// Paramaters: bool P - is the game paused?
//             bool L - is the game lost?
//             int w - window width
//             int h - window height
//             float screen - size of screen
//             int score - score of the game
//             Ship ship - a ship object to get its fuel value
//
// Calls: drawText - display text on the screen.
//        convert_int_to_string - convert the score into a string for use with
//    the drawText function.
//
//***********************************************************************
void Text::show_score( bool &P, bool &L, int w, int h, float screen, int score, Ship &ship){

  glDisable(GL_TEXTURE_2D);
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,screen*w,0,screen*h,-1,1);
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  glColor4f(1.0,1.0,1.0,1.0);
  //line_height=300;
  if((P==false)&&(L==false)){
    drawText(20,h*10-line_height*1,"SCORE:");
  }else if(P==true){
    drawText(20,h*10-line_height*1, "PAUSED");
  }else if(L==true){
    drawText(20,h*10-line_height*1, "GAME OVER");
  }
  string temp=convert_int_to_string(score);
  char converted_score[SIZE2];
  for(int i=0;i<temp.length();i++){
    converted_score[i]=temp[i];
  }
  drawText(20,h*10-line_height*2, converted_score);

  drawText(20,h*10-line_height*3, "FUEL:");  
  string temp2=convert_int_to_string(ship.get_fuel());
  char converted_fuel[SIZE3];
  for(int i=0;i<temp2.length();i++){
    converted_fuel[i]=temp2[i];
  }
  drawText(20,h*10-line_height*4, converted_fuel);
  
  
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
// Paramaters: int w - window width
//             int h - window height
//
// Calls: drawText - display text on the screen
//
//***********************************************************************
void Text::post_message( int w, int h, float screen/*, int score, int sleep_time*/ ){
// Clear the window
  glDisable(GL_TEXTURE_2D);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,screen*w,0, screen*h, -1, 1);
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  glColor4f(1.0, 1.0, 1.0, 1.0);
  
  drawText(20,h*10-line_height*1,"        This is the Game \"ASTEROID MINING\"");
  drawText(20,h*10-line_height*3,"  You must get resources from mineable asteroids");
  drawText(20,h*10-line_height*4,"  for points while at the same time, avoiding incoming");
  drawText(20,h*10-line_height*5,"  asteroids.");
  drawText(20,h*10-line_height*7,"  You may press n for a new game,");
  drawText(20,h*10-line_height*8,"  You may press p to pause the game,");
  drawText(20,h*10-line_height*9,"  You may press h for this screen again,");
  drawText(20,h*10-line_height*10,"  or you can press q to quit");
  
  glPopMatrix();
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);

  //sleep(sleep_time); //not working here in Windows
}

//***********************************************************************
//
// Function: post_message
//
// Purpose: Displays the two choices of ships to choose from 
//
// Paramaters: int w - window width
//             int h - window height
//             float screen - screen size
//             Ship ship - ship to get draw functions from
//             int choice  - id of ship 1
//             int choice2 - id of ship 2
//
// Calls: Ship::draw_space_ship
//        Ship::draw_space_ship2
//
//***********************************************************************
void Text::pick_ship( int w, int h, float screen, Ship &ship, int choice, int choice2 ){
// Clear the window
    glDisable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0,screen*w,0, screen*h, -1, 1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glColor4f(1.0, 1.0, 1.0, 1.0);
  
    drawText(20,h*10-line_height*6,"                                    Please chooce a ship");
  
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 90, 1.0, 1.0, 400.0 );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0,-2.0,-3.0);//ship origin is behind camera
    ship.draw_space_ship(GL_RENDER,choice);
    glTranslatef(2.0,0.0,0.0);
    ship.draw_space_ship2(GL_RENDER,choice2);
    glTranslatef(-1.0,2.0,3.0);   
    
    glEnable(GL_TEXTURE_2D);
}

