//*********************************************************************
//
//  Program: hw1 - model and project a 3D object onto a 2D screen
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This program models a 3D spaceship onto a 2D screen. 
//    It provides some user interaction using left and right mouse clicks.
//    Right mouse clicks make the ship appear to move. Left click and drag
//    or right click and drag shoots an invisible laser that destroys the 
//    stars in the background. Reshaping the screen is supported and the ship
//    will remain the same size. 
//
//  Last Updated: 09/29/2011
//
//*********************************************************************

#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
using namespace std;

/*declare global variables*/

int mouse_x=0; //position of mouse horizontally on the screen
int mouse_y=0; //position of mouse vertically on the screen
int win_h=500; //height of the window
int win_w=500; //width of the window
float alpha_color_increment=0.0; //change the opaquenes of objects

/*space ship modeled as arrays of floats*/
  //ship wing
  float wing1[]={ 12.0,19.0, 0.4 };
  float wing2[]={ 24.0, 19.0, 0.4 };
  float wing3[]={ 9.5, 19.0, 0.7 };

  //ship back-end front-face
  float sbf1[]={ 6.0, 28.0, 0.4 };
  float sbf2[]={ 6.0, 10.0, 0.4 };
  float sbf3[]={ 9.0, 14.0, 0.4 };
  float sbf4[]={ 9.0, 24.0, 0.4 };

  //ship back-end top-face
  float sbt1[]={ 6.0, 28.0, 0.3 };
  float sbt2[]={ 6.0, 28.0, 0.4 };
  float sbt3[]={ 9.0, 24.0, 0.4 };
  float sbt4[]={ 9.0, 24.0, 0.3 };

  //ship middle-top
  float smt1[]={ 9.0, 24.0, 0.3 }; 
  float smt2[]={ 9.0, 24.0, 0.4 }; 
  float smt3[]={ 24.0, 24.0, 0.4 };  
  float smt4[]={ 24.0, 24.0, 0.3 }; 

  //ship middle-front
  float smf1[]={ 9.0, 24.0, 0.4 }; 
  float smf2[]={ 9.0, 14.0, 0.4 };
  float smf3[]={ 24.0, 14.0, 0.4 }; 
  float smf4[]={ 24.0, 24.0, 0.4 };

  //ship front-end front-face
  float sff1[]={ 24.0, 24.0, 0.4 };
  float sff2[]={ 24.0, 14.0, 0.4 };
  float sff3[]={ 30.0, 18.0, 0.4 };
  float sff4[]={ 30.0, 20.0, 0.4 };

  //ship front-end top-face
  float sft1[]={ 24.0, 24.0, 0.3 };
  float sft2[]={ 24.0, 24.0, 0.4 };
  float sft3[]={ 30.0, 20.0, 0.4 };
  float sft4[]={ 30.0, 20.0, 0.3 };

  //ship front-end right-face
  float sfr1[]={ 30.0, 20.0, 0.3 };
  float sfr2[]={ 30.0, 20.0, 0.4 };
  float sfr3[]={ 30.0, 18.0, 0.4 };
  float sfr4[]={ 30.0, 18.0, 0.3 };

  //ship front-end bottom-face
  float sfb1[]={ 24.0, 14.0, 0.3 };
  float sfb2[]={ 24.0, 14.0, 0.4 };
  float sfb3[]={ 30.0, 18.0, 0.4 };
  float sfb4[]={ 30.0, 18.0, 0.3 };

float a,b; //new x and y coordinates of space ship in projection equation
bool move=false; //is ship moving?
bool active_mouse=false; //is mouse active?

/* End declaration of global variables */


//*******************************************************************
//
//  Function:   project
//
//  Purpose:    modifies a and b to be the new x and y coordinates of
//              an object to be rendered onto a 2D screen. 
//
//  Parameters: a - modified to give the new x coordinate of the object
//              b - modified to give the new y coordinate of the object
//              arg[] - an array of the points of the 3D object that is 
//                being translated into 2D.
//
//  User
//  Defined
//  Calls:      none
//
//*******************************************************************
void project(float &a,float &b,float arg[]){
  a=arg[0]/(arg[2]/4.0);
  b=arg[1]/(arg[2]/4.0);
}

//*******************************************************************
//
//  Function:   cyber_space
//
//  Purpose:    randomly places stars of red white and blue onto the 
//              screen. Also makes the ship appear to be moving when
//              used correctly.  
//
//  Parameters: none
//
//  User 
//  Defined
//  Calls:      none
//
//*******************************************************************
void cyber_space( void ){
  glPointSize(3.0);
  glColor4f(1.0,1.0,1.0,1.0); //white stars
  for(int i=0;i<=250;i++){
    glBegin(GL_POINTS);{
      int j=rand()%win_w;
      int k=rand()%win_h;
      glVertex2f(j,k);
    }glEnd();
  }

  glPointSize(2.0);
  glColor4f(0.2,0.2,1.0,1.0); //blue stars
  for(int i=0;i<=200;i++){
    glBegin(GL_POINTS);{
      int j=rand()%win_w;
      int k=rand()%win_h;
      glVertex2f(j,k);
    }glEnd();
  }

  glPointSize(1.0);
  glColor4f(1.0,0.2,0.2,1.0); //red stars
  for(int i=0;i<=100;i++){
    glBegin(GL_POINTS);{
      int j=rand()%win_w;
      int k=rand()%win_h;
      glVertex2f(j,k);
    }glEnd();
  }
}

//*******************************************************************
//
//  Function:   my_idle
//
//  Purpose:    used to make the ship appear to be moving or standing
//              still depending on the state of the boolean variable
//              move which is changed within the function mouse().  
//
//  Parameters: none
//
//  Calls:      function glutPostRedisplay() which actively calls the
//              display function. Actively redraws the stars to give
//              the appearance of motion. 
//
//*******************************************************************
void my_idle( void ){
  if(move==true){
    glutPostRedisplay();  
  }
}

//*******************************************************************
//
//  Function:   mouse
//
//  Purpose:    Allows for interaction with the user. Causes the 
//              space ship to move/stop and disappear/reappear.
//
//  Parameters: btn - tells function what button is being used
//              state - tells the function what state the button is in
//              x - gives the horizontal position of the mouse on the screen
//              y - gives the vertical position of the mouse on the screen
//
//  Calls:      none
//
//*******************************************************************
void mouse( int btn, int state, int x, int y ){
  if((glutGetModifiers()!=GLUT_ACTIVE_SHIFT) && btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    mouse_x=x;
    mouse_y=y;
    if(move==true){ //when right mouse is clicked, it sets the space ship in motion
      move=false;   //  or stops the space ship
    }else{
      move=true;
    }
  }else if((glutGetModifiers()==GLUT_ACTIVE_SHIFT) && btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    alpha_color_increment-=0.1;
    if(alpha_color_increment<0.0){ //when left mouse is clicked and shift is held, the space ship
      alpha_color_increment=0.0;   //will begin to reappear
    }
  }else if((glutGetModifiers()==GLUT_ACTIVE_SHIFT) && btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    alpha_color_increment+=0.1;
    if(alpha_color_increment>1.0){ //when right mouse is clicked and shift is held, the space ship
      alpha_color_increment=1.0;   //will begin to disappear
    }
  }
  glutPostRedisplay();
}

//*******************************************************************
//
//  Function:   motion
//
//  Purpose:    allows for the laser to work when the mouse is active
//              (click and dragged) 
//
//  Parameters: x - the horizontal position of the mouse on the screen
//              y - the vertical position of the mouse on the screen
//
//  Calls:      glutPostRedisplay() which effectively draws the laser
//              and thus destroying the stars on the screen. 
//
//*******************************************************************
void motion( int x, int y ){
  mouse_x = x;
  mouse_y = y;
  active_mouse=true; 
  glutPostRedisplay(); 
}

//*******************************************************************
//
//  Function:   passive_motion
//
//  Purpose:    effectively undoes the effects of the motion() function.
//
//  Parameters: x - the horizontal position of the mouse on the screen.
//              y - the vertical position of the mouse on the screen.
//              (both are not actually used but are necessary for the 
//              function to work)
//
//  Calls:      none
//
//*******************************************************************
void passive_motion(int x, int y){ 
  active_mouse=false;
}

//*******************************************************************
//
//  Function:   my_init
//
//  Purpose:     initializes the attributes necessary for the program
//               to work properly
//
//  Parameters: none
//
//  User
//  Defined
//  Calls:      none
//
//*******************************************************************
void my_init( void ){
  /* attributes */
  glClearColor(0.0, 0.1, 0.1, 1.0); // dark turqoise background
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, win_w, 0.0, win_h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//*******************************************************************
//
//  Function:   my_reshape
//
//  Purpose:    Allows for the user to properly reshape the screen
//              and maintain desirable properties necessary for the 
//              program to work. Maintains the same shape and size
//              of the space ship. 
//
//  Parameters: w - the horizontal distance in pixels of the screen
//              h - the vertical distance in pixels of the screen
//
//  User
//  Defined
//  Calls:      none
//
//*******************************************************************
void my_reshape(int w, int h){
  win_w = w;
  win_h = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,win_w,0.0,win_h);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

//*******************************************************************
//
//  Function:   display
//
//  Purpose:    The bulk of the program. Creates the actual graphics
//              necessary for the program. Clears the screen, draws 
//              the ship, draws the actual invisible laser which 
//              destroys the stars, draws the thrusters on the ship, 
//              makes the ship disappear/reappear, and swaps the 
//              buffer necessary for double buffering.
//
//  Parameters: none
//
//  Calls:      cyber_space() - draws the stars to the screen
//              project() - translates the 3D coordinates of the ship
//                into 2D coordinates.
//
//*******************************************************************
void display( void ){
  if(active_mouse==false){ //for purposes of shooting and destroying stars with lasers

    glClear(GL_COLOR_BUFFER_BIT);  // clear the window 

    cyber_space(); //create stars first so space ship can be in front of them
  }else{ //if mouse is active (click and drag) then...
    glColor4f(0.0,0.0,0.0,1.0); //shoot invisible laser to destroy the stars
    glLineWidth(10.0);
    glBegin(GL_LINES); {
      glVertex2f(300.0,300.0); 
      glVertex2f(mouse_x,win_h-mouse_y); 
    }glEnd();
  } //end shooting lasers

  //NOTE: holding shift and clicking the mouse (left or right) will
  //      toggle any object with the -alpha_color_increment into 
  //      disappearing/reappearing from this point and on

  //makes space ship appear to be moving with thrusters
  //  when mouse is right clicked. Remains in motion until mouse
  //  is right clicked again. (toggle thrusters with right click)
  if(move==true){
    GLUquadricObj * circ = gluNewQuadric();
    glTranslatef(60.0,220,0);  
    glColor4f(1.0,1.0,0.0,1.0-alpha_color_increment);  //draw outer thruster yellow
    gluDisk(circ, 0.0, 40.0, 60.0, 150.0);
    glColor4f(1.0,0.6,0.0,1.0-alpha_color_increment);  //draw mid thruster orange
    gluDisk(circ, 0.0, 30.0, 60.0, 150.0);
    glColor4f(0.8,0.0,0.0,1.0-alpha_color_increment);  //draw inside thruster red
    gluDisk(circ, 0.0, 20.0, 60.0, 150.0);
    glTranslatef(-60.0, -220, 0);
    gluDeleteQuadric(circ);
  } //end thrusters


  /*draw back portion of the ship*/
  glColor4f(0.2,0.2,0.2,1.0-alpha_color_increment); //blackish/grey
  glBegin(GL_POLYGON);{ 
    project(a,b,sbf1);
    glVertex2f(a,b);
    project(a,b,sbf2); 
    glVertex2f(a,b);
    project(a,b,sbf3);
    glVertex2f(a,b);
    project(a,b,sbf4);
    glVertex2f(a,b);
  }glEnd();
  glColor4f(0.25,0.25,0.25,1.0-alpha_color_increment); //black/greyish
  glBegin(GL_POLYGON);{ 
    project(a,b,sbt1);
    glVertex2f(a,b);
    project(a,b,sbt2);
    glVertex2f(a,b);
    project(a,b,sbt3);
    glVertex2f(a,b);
    project(a,b,sbt4);
    glVertex2f(a,b);
  }glEnd(); //end drawing the back portion of the ship

  /*draw middle portion of the ship*/
  glColor4f((131.0/256.0),(139.0/256.0),(131.0/256.0),1.0-alpha_color_increment); //dark grey
  glBegin(GL_POLYGON);{ 
    project(a,b,smt1);
    glVertex2f(a,b);
    project(a,b,smt2);
    glVertex2f(a,b);
    project(a,b,smt3);
    glVertex2f(a,b);
    project(a,b,smt4);
    glVertex2f(a,b);
  }glEnd();
  glColor4f((110.0/256.0),(117.0/256.0),(110.0/256.0),1.0-alpha_color_increment); //dark grey
  glBegin(GL_POLYGON);{
    project(a,b,smf1);
    glVertex2f(a,b);
    project(a,b,smf2);
    glVertex2f(a,b);
    project(a,b,smf3);
    glVertex2f(a,b);
    project(a,b,smf4);
    glVertex2f(a,b);
  }glEnd();//end drawing middle portion of ship */

  /*draw front portion of the ship*/
  glColor4f(0.3,0.3,0.3,1.0-alpha_color_increment); //grey
  glBegin(GL_POLYGON);{
    project(a,b,sfb1);
    glVertex2f(a,b);
    project(a,b,sfb2);
    glVertex2f(a,b);
    project(a,b,sfb3);
    glVertex2f(a,b);
    project(a,b,sfb4);
    glVertex2f(a,b);
  }glEnd();
  glColor4f((110.0/256.0),(117.0/256.0),(110.0/256.0),1.0-alpha_color_increment); //dark grey
  glBegin(GL_POLYGON);{
    project(a,b,sff1);
    glVertex2f(a,b);
    project(a,b,sff2);
    glVertex2f(a,b);
    project(a,b,sff3);
    glVertex2f(a,b);
    project(a,b,sff4);
    glVertex2f(a,b);
  }glEnd();
  glColor4f((175.0/256.0),(238.0/256.0),(238.0/256.0),1.0-alpha_color_increment); //pale turquoise
  glBegin(GL_POLYGON);{
    project(a,b,sft1);
    glVertex2f(a,b);
    project(a,b,sft2);
    glVertex2f(a,b);
    project(a,b,sft3);
    glVertex2f(a,b);
    project(a,b,sft4);
    glVertex2f(a,b);
  }glEnd();
  glBegin(GL_POLYGON);{
    project(a,b,sfr1);
    glVertex2f(a,b);
    project(a,b,sfr2);
    glVertex2f(a,b);
    project(a,b,sfr3);
    glVertex2f(a,b);
    project(a,b,sfr4);
    glVertex2f(a,b);
  }glEnd(); //end drawing of front portion of ship

  /*draw the wing*/
  glColor4f((100.0/256.0),(107.0/256.0),(100.0/256.0),1.0-alpha_color_increment); //color base of wing dark grey
  glBegin(GL_POLYGON);{
    project(a,b,wing1);
    glVertex2f(a,b);
    project(a,b,wing2);
    glVertex2f(a,b);
    glColor4f(1.0,1.0,1.0,1.0-alpha_color_increment); //color tip of wing white
    project(a,b,wing3);
    glVertex2f(a,b);
  }glEnd(); //end drawing of wing

  glutSwapBuffers(); //needed with double buffering scheme
}


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
  glutInitWindowSize(500, 500); //initialize the window to be 500x500 pixels
  glutCreateWindow("Spaceship"); //initialize the name of the window to be "Spaceship"
  glutDisplayFunc(display);
  glutReshapeFunc(my_reshape);
  glutIdleFunc(my_idle);
  glutMotionFunc (motion);
  glutPassiveMotionFunc (passive_motion);
  glutMouseFunc (mouse); 
  my_init();
  glClearColor(0.0, 0.0, 0.0, 1.0); //black
  glutMainLoop(); //necessary for proper display

  return(EXIT_SUCCESS);
}
