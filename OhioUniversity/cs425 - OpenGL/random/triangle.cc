/* Two-Dimensional Simple Triangle          */
// Written by dmc 9/13/04 
// 

#include <iostream>
#include <GL/glut.h>
#include <cstdlib>


void myinit(void)
{
  
  /* attributes */
  glClearColor(0.1, 0.1, 0.1, 0.5); /* dark background */

  //glColor3f(1.0, 0.0, 0.0); /* draw in red */

  glColor3f(0.0, 1.0, 0.0); /* draw in green */

  /* set up viewing */
  /* 700 x 700 window with origin lower left */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 700.0, 0.0, 700.0);
  glMatrixMode(GL_MODELVIEW);
}

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
  /* plot triangle */
  glBegin(GL_POLYGON);{
    glVertex2f(0.0, 0.0); 
    glVertex2f(500.0, 0.0); 
    glVertex2f(0.0, 500.0); 
  } glEnd();
   
  glFlush(); /* clear buffers */
}

int main(int argc, char** argv)
{

  /* Standard GLUT initialization */

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
  glutInitWindowSize(700,700); /* 700 x 700 pixel window */
  glutInitWindowPosition(0,0); /* place window top left on display */
  glutCreateWindow("Triangle Display"); /* window title */
  glutDisplayFunc(display); /* display callback invoked when window opened */

  myinit(); /* set attributes */

  glutMainLoop(); /* enter event loop */
    
  return(EXIT_SUCCESS); /* return successful exit code */
}
