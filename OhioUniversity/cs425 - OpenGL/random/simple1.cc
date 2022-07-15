// From Lecture 04 simple square display.
//
// What happens when we use larger values for vertex locations?
// 
#include <GL/glut.h>

void mydisplay()
{
  glClear(GL_COLOR_BUFFER_BIT); 
  glBegin(GL_POLYGON);{
    glVertex2f(0, 0);
    glVertex2f(0, 500);        
    glVertex2f(500, 500);        
    glVertex2f(500, 0);    
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
