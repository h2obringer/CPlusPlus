// From Lecture 04 simple square display.

#include <GL/glut.h>

void mydisplay()
{
  glClear(GL_COLOR_BUFFER_BIT); 
  glBegin(GL_POLYGON);{
    glVertex2f(-0.5, -0.5);        
    glVertex2f(-0.5, 0.5);        
    glVertex2f(0.5, 0.5);        
    glVertex2f(0.5, -0.5);    
  } glEnd();
  glFlush(); 
}

int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutCreateWindow("simple");     
  glutDisplayFunc(mydisplay);    
  glutMainLoop();
}
