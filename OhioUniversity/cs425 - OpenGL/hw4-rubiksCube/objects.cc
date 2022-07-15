//*********************************************************************
//
//  File: objects.cc
//  Program: final 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the class implementation file for individual 
//    cubes and the Rubiks Cube. Arrays are included here for compilation
//    purposes.  
//
//  Last Updated: 11/16/2011
//
//*********************************************************************

#include "objects.h"

GLfloat my_vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			 {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
			 {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat my_normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
			{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat my_colors[][3] = {{0.0,0.0,0.0}/*black*/,{1.0,1.0,1.0}/*white*/,
		       {1.0,0.0,0.0}/*red*/, {0.0,1.0,0.0}/*green*/, {0.0,0.0,1.0}/*blue*/, 
		       {1.0,1.0,0.0}/*yellow*/, {1.0,0.5,0.0}/*orange*/};

//constructor
TLF::TLF(){
  x_axis=ZERO;
  y_axis=ONE;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=YELLOW;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
TLM::TLM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
TLB::TLB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
TMF::TMF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
TMM::TMM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
TMB::TMB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
TRF::TRF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
TRM::TRM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
TRB::TRB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=YELLOW;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
MLF::MLF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=ZERO;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
MLM::MLM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=ZERO;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
MLB::MLB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=ZERO;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
MMF::MMF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=ZERO;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
MMM::MMM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=ZERO;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
MMB::MMB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=ZERO;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
MRF::MRF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=ZERO;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
MRM::MRM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=ZERO;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
MRB::MRB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=ZERO;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=BLACK;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
DLF::DLF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=-PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=WHITE;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
DLM::DLM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=-PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
DLB::DLB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=-PLACEMENT;
  y=-PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=RED;
  right=BLACK;
  temp=BLACK;
}

//constructor
DMF::DMF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=-PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
DMM::DMM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=-PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
DMB::DMB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=ZERO;
  y=-PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=BLACK;
  temp=BLACK;
}

//constructor
DRF::DRF(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=-PLACEMENT;
  z=PLACEMENT;
  back=BLACK;
  front=GREEN;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
DRM::DRM(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=-PLACEMENT;
  z=ZERO;
  back=BLACK;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//constructor
DRB::DRB(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
  rotation=ZERO;
  x=PLACEMENT;
  y=-PLACEMENT;
  z=-PLACEMENT;
  back=BLUE;
  front=BLACK;
  top=BLACK;
  bottom=WHITE;
  left=BLACK;
  right=ORANGE;
  temp=BLACK;
}

//accessor
int TLF::get_rotation(){
  return rotation;
}

//accessor
int TLF::get_x_axis(){
  return x_axis;
}

//accessor
int TLF::get_y_axis(){
  return y_axis;
}

//accessor
int TLF::get_z_axis(){
  return z_axis;
}

//mutator
void TLF::mutate_axese(int new_x_axis,int new_y_axis,int new_z_axis){
  x_axis=new_x_axis;
  y_axis=new_y_axis;
  z_axis=new_z_axis;
}

//***********************************************************************
//
// Function: reset_axese
//
// Purpose: Resets the x,y, and z axese to zero
//
//***********************************************************************
void TLF::reset_axese(){
  x_axis=ZERO;
  y_axis=ZERO;
  z_axis=ZERO;
}

//mutator
void TLF::mutate_rotation(int new_rotation){
  rotation=new_rotation;
}

//accessor
double TLF::get_x(){
  return x;
}

//accessor
double TLF::get_y(){
  return y;
}

//accessor
double TLF::get_z(){
  return z;
}

//accessor
int TLF::get_back(){
  return back;
}

//accessor
int TLF::get_front(){
  return front;
}

//accessor
int TLF::get_left(){
  return left;
}

//accessor
int TLF::get_right(){
  return right;
}

//accessor
int TLF::get_top(){
  return top;
}

//accessor
int TLF::get_bottom(){
  return bottom;
}

//***********************************************************************
//
// Function: polygon
//
// Purpose: Draw a face of a cube with the correct color via list of vertices
//
// Paramaters: int a - reference to a position in a vertex array
//             int b - reference to a position in a vertex array
//             int c - reference to a position in a vertex array
//             int d - reference to a position in a vertex array
//             int color - reference to a position in a color array
//
//***********************************************************************
void TLF::polygon(int a, int b, int c , int d, int color){
  glBegin(GL_POLYGON);
    glColor3fv(my_colors[color]);
    glNormal3fv(my_normals[a]);
    glVertex3fv(my_vertices[a]);
    glNormal3fv(my_normals[b]);
    glVertex3fv(my_vertices[b]);
    glNormal3fv(my_normals[c]);
    glVertex3fv(my_vertices[c]);
    glNormal3fv(my_normals[d]);
    glVertex3fv(my_vertices[d]);
  glEnd();
}

//***********************************************************************
//
// Function: build_cube
//
// Purpose: Draw a cube with correct position in space and correct 
//    colors for faces.
//
// Paramaters: int b - the color of the back face
//             int u - the color of the top face
//             int l - the color of the left face
//             int d - the color of the bottom face
//             int r - the color of the right face
//             int f - the color of the front face
//
// Calls: polygon
//
//***********************************************************************
void TLF::build_cube(int b,int f,int u,int d,int l,int r){ 
    polygon(1,0,3,2,b);
    polygon(3,7,6,2,u);
    polygon(7,3,0,4,l);
    polygon(0,4,5,1,d);
    polygon(2,6,5,1,r);
    polygon(4,5,6,7,f);
}  

//***********************************************************************
//
// Function: draw
//
// Purpose: Draw the cube with selection processes in mind. Allow the cube's
//    name to be loaded in the program so the user can click on it.
//
// Paramaters: GLenum mode - GL_RENDER or GL_SELECT
//             const int NAME - the ID of the object
//
// Calls: build_cube
//
//***********************************************************************
void TLF::draw(GLenum mode,const int NAME){
  if(mode==GL_SELECT){
    glLoadName(NAME);
  }
  build_cube(back,front,top,bottom,left,right);
}

//***********************************************************************
//
// Function: top_move_right
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a top face move right action
//
//***********************************************************************
void TLF::top_move_right(){ 
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    x=-x;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    z=-z;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    x=ZERO;
    z=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    x=-x;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    x=PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    z=-z;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    x=ZERO;
    z=-PLACEMENT;
  }

  temp=left;
  left=back;
  back=right;
  right=front;
  front=temp;
}

//***********************************************************************
//
// Function: top_move_left
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a top face move left action
//
//***********************************************************************
void TLF::top_move_left(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    z=-z;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    x=PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    x=-x;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    x=ZERO;
    z=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    z=-z;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    x=-x;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    x=ZERO;
    z=PLACEMENT;
  }

  temp=left;
  left=front;
  front=right;
  right=back;
  back=temp;
}

//***********************************************************************
//
// Function: middle_horizontal_move_left
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle horizontal move left action
//
//***********************************************************************
void TLF::middle_horizontal_move_left(){ 
  if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    z=-z;
  }else if((x==ZERO)&&(y==ZERO)&&(z==-PLACEMENT)){ //MMB
    x=PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    x=-x;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MLM
    x=ZERO;
    z=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    z=-z;
  }else if((x==ZERO)&&(y==ZERO)&&(z==PLACEMENT)){ //MMF
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    x=-x;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MRM
    x=ZERO;
    z=PLACEMENT;
  }

  temp=left;
  left=front;
  front=right;
  right=back;
  back=temp;
}

//***********************************************************************
//
// Function: middle_horizontal_move_right
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle horizontal move right action
//
//***********************************************************************
void TLF::middle_horizontal_move_right(){ 
  if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    x=-x;
  }else if((x==ZERO)&&(y==ZERO)&&(z==-PLACEMENT)){ //MMB
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    z=-z;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MLM
    x=ZERO;
    z=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    x=-x;
  }else if((x==ZERO)&&(y==ZERO)&&(z==PLACEMENT)){ //MMF
    x=PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    z=-z;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MRM
    x=ZERO;
    z=-PLACEMENT;
  }

  temp=left;
  left=back;
  back=right;
  right=front;
  front=temp;
}

//***********************************************************************
//
// Function: bottom_move_left
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a bottom move left action
//
//***********************************************************************
void TLF::bottom_move_left(){ 
  if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    z=-z;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    x=PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    x=-x;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    x=ZERO;
    z=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    z=-z;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    x=-x;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    x=ZERO;
    z=PLACEMENT;
  }

  temp=left;
  left=front;
  front=right;
  right=back;
  back=temp;
}

//***********************************************************************
//
// Function: bottom_move_right
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a bottom move right action
//
//***********************************************************************
void TLF::bottom_move_right(){ //originally BOTTOM MOVE LEFT
  if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    x=-x;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    x=-PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    z=-z;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    x=ZERO;
    z=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    x=-x;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    x=PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    z=-z;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    x=ZERO;
    z=-PLACEMENT;
  }

  temp=left;
  left=back;
  back=right;
  right=front;
  front=temp;
}


//***********************************************************************
//
// Function: left_move_down
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a left move down action
//
//***********************************************************************
void TLF::left_move_down(){
  if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    y=-y;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    y=ZERO;
    z=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    z=-z;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    y=PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    y=-y;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    y=ZERO;
    z=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    z=-z;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    y=-PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=back;
  back=bottom;
  bottom=front;
  front=temp;
}

//***********************************************************************
//
// Function: left_move_up
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a left move up action
//
//***********************************************************************
void TLF::left_move_up(){
  if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    z=-z;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    y=ZERO;
    z=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    y=-y;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    y=-PLACEMENT;
    z=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    z=-z;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    y=ZERO;
    z=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    y=-y;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    y=PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=front;
  front=bottom;
  bottom=back;
  back=temp;
}

//***********************************************************************
//
// Function: middle_vertical_move_down
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle vertical move down action
//
//***********************************************************************
void TLF::middle_vertical_move_down(){
  if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    y=-y;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==ZERO)){ //TMM
    y=ZERO;
    z=PLACEMENT;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    z=-z;
  }else if((x==ZERO)&&(y==ZERO)&&(z==-PLACEMENT)){ //MMB
    y=PLACEMENT;
    z=ZERO;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    y=-y;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==ZERO)){ //DMM
    y=ZERO;
    z=-PLACEMENT;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    z=-z;
  }else if((x==ZERO)&&(y==ZERO)&&(z==PLACEMENT)){ //MMF
    y=-PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=back;
  back=bottom;
  bottom=front;
  front=temp;
}

//***********************************************************************
//
// Function: middle_vertical_move_up
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle vertical move up action
//
//***********************************************************************
void TLF::middle_vertical_move_up(){
  if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    z=-z;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==ZERO)){ //TMM
    y=ZERO;
    z=-PLACEMENT;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    y=-y;
  }else if((x==ZERO)&&(y==ZERO)&&(z==-PLACEMENT)){ //MMB
    y=-PLACEMENT;
    z=ZERO;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    z=-z;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==ZERO)){ //DMM
    y=ZERO;
    z=PLACEMENT;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    y=-y;
  }else if((x==ZERO)&&(y==ZERO)&&(z==PLACEMENT)){ //MMF
    y=PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=front;
  front=bottom;
  bottom=back;
  back=temp;
}

//***********************************************************************
//
// Function: right_move_down
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a right move down action
//
//***********************************************************************
void TLF::right_move_down(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    y=-y;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    y=ZERO;
    z=PLACEMENT;
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    z=-z;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    y=PLACEMENT;
    z=ZERO;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    y=-y;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    y=ZERO;
    z=-PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    z=-z;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    y=-PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=back;
  back=bottom;
  bottom=front;
  front=temp;
}

//***********************************************************************
//
// Function: right_move_up
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a right move up action
//
//***********************************************************************
void TLF::right_move_up(){ 
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    z=-z; 
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    y=ZERO;
    z=-PLACEMENT; 
  }else if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    y=-y; 
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    y=-PLACEMENT;
    z=ZERO; 
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    z=-z; 
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    y=ZERO;
    z=PLACEMENT; 
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    y=-y;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    y=PLACEMENT;
    z=ZERO;
  }

  temp=top;
  top=front;
  front=bottom;
  bottom=back;
  back=temp;
}

//***********************************************************************
//
// Function: front_face_cw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a front face move clockwise action
//
//***********************************************************************
void TLF::front_face_cw(){ //TRF,MRF,DRF,DMF,DLF,MLF,TLF,TMF
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    y=-y;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    x=-x;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    x=-PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    y=-y;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    x=ZERO;
    y=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    x=-x;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    x=PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=left;
  left=bottom;
  bottom=right;
  right=temp;
}

//***********************************************************************
//
// Function: front_face_ccw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a front face move counter-clockwise action
//
//***********************************************************************
void TLF::front_face_ccw(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TRF
    x=-x;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MRF
    x=ZERO;
    y=PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DRF
    y=-y;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DMF
    x=PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==PLACEMENT)){ //DLF
    x=-x;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==PLACEMENT)){ //MLF
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TLF
    y=-y;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==PLACEMENT)){ //TMF
    x=-PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=right;
  right=bottom;
  bottom=left;
  left=temp;
}

//***********************************************************************
//
// Function: middle_face_cw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle face move clockwise action
//
//***********************************************************************
void TLF::middle_face_cw(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    y=-y;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MRM
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    x=-x;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==ZERO)){ //DMM
    x=-PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    y=-y;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MLM
    x=ZERO;
    y=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    x=-x;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==ZERO)){ //TMM
    x=PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=left;
  left=bottom;
  bottom=right;
  right=temp;
}


//***********************************************************************
//
// Function: middle_face_ccw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a middle face move counter-clockwise action
//
//***********************************************************************
void TLF::middle_face_ccw(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TRM
    x=-x;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MRM
    x=ZERO;
    y=PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DRM
    y=-y;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==ZERO)){ //DMM
    x=PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==ZERO)){ //DLM
    x=-x;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==ZERO)){ //MLM
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==ZERO)){ //TLM
    y=-y;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==ZERO)){ //TMM
    x=-PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=right;
  right=bottom;
  bottom=left;
  left=temp;
}

//***********************************************************************
//
// Function: back_face_cw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a back face move clockwise action
//
//***********************************************************************
void TLF::back_face_cw(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    y=-y;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    x=-x;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    x=-PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    y=-y;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    x=ZERO;
    y=PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    x=-x;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    x=PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=left;
  left=bottom;
  bottom=right;
  right=temp;
}


//***********************************************************************
//
// Function: back_face_ccw
//
// Purpose: Re-orient the cube's position and face colors when the cube
//    is part of a back face move counter-clockwise action
//
//***********************************************************************
void TLF::back_face_ccw(){
  if((x==PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TRB
    x=-x;
  }else if((x==PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MRB
    x=ZERO;
    y=PLACEMENT;
  }else if((x==PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DRB
    y=-y;
  }else if((x==ZERO)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DMB
    x=PLACEMENT;
    y=ZERO;
  }else if((x==-PLACEMENT)&&(y==-PLACEMENT)&&(z==-PLACEMENT)){ //DLB
    x=-x;
  }else if((x==-PLACEMENT)&&(y==ZERO)&&(z==-PLACEMENT)){ //MLB
    x=ZERO;
    y=-PLACEMENT;
  }else if((x==-PLACEMENT)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TLB
    y=-y;
  }else if((x==ZERO)&&(y==PLACEMENT)&&(z==-PLACEMENT)){ //TMB
    x=-PLACEMENT;
    y=ZERO;
  }

  temp=top;
  top=right;
  right=bottom;
  bottom=left;
  left=temp;
}


//***********************************************************************
//
// Function: Rubiks_Cube (constructor)
//
// Purpose: Sets pointers to their respective cubes, sets the initial 
//    animation speed for a move that is made, seeds the random number generator
//
//***********************************************************************
Rubiks_Cube::Rubiks_Cube(){
	temp_p=&tlf;
  tlfp=&tlf;
  tlmp=&tlm;
  tlbp=&tlb;
  tmfp=&tmf;
  tmmp=&tmm;
  tmbp=&tmb;
  trfp=&trf;
  trmp=&trm;
  trbp=&trb;
  mlfp=&mlf;
  mlmp=&mlm;
  mlbp=&mlb;
  mmfp=&mmf;
  mmmp=&mmm;
  mmbp=&mmb;
  mrfp=&mrf;
  mrmp=&mrm;
  mrbp=&mrb;
  dlfp=&dlf;
  dlmp=&dlm;
  dlbp=&dlb;
  dmfp=&dmf;
  dmmp=&dmm;
  dmbp=&dmb;
  drfp=&drf;
  drmp=&drm;
  drbp=&drb;
  front=back=left=right=top=bottom=move_rotation=x_axis=y_axis=z_axis=
	direction=x_rotation=y_rotation=ZERO;
  speed=MAX_SPEED;
  in_progress=false;
  srand(time(NULL));
}

//mutator
void Rubiks_Cube::mutate_x_rotation(int x){
  x_rotation=x;
}

//mutator
void Rubiks_Cube::mutate_y_rotation(int y){
  y_rotation=y;
}

//***********************************************************************
//
// Function: write_cube
//
// Purpose: Writes all of a cubes data to a file. The stream to do this will
//    be given by the parameter.
//
// Parameters: ostream& outs - the stream (method) in which to output data
//
//***********************************************************************
void TLF::write_cube(ostream& outs){
  outs << x_axis << endl;
  outs << y_axis << endl;
  outs << z_axis << endl;
  outs << rotation << endl;
  outs << x << endl;
  outs << y << endl;
  outs << z << endl;
  outs << back << endl;
  outs << front << endl;
  outs << top << endl;
  outs << bottom << endl;
  outs << left << endl;
  outs << right << endl << endl;
}

//***********************************************************************
//
// Function: load_cube
//
// Purpose: Loads all of a cubes data from a file. The stream to do this will
//    be given by the parameter. 
//
// Parameters: istream& ins - the stream (method) in which to input data
//
//***********************************************************************
void TLF::load_cube(istream& ins){
  ins >> x_axis;
  ins >> y_axis;
  ins >> z_axis;
  ins >> rotation;
  ins >> x;
  ins >> y;
  ins >> z;
  ins >> back;
  ins >> front;
  ins >> top;
  ins >> bottom;
  ins >> left;
  ins >> right;
}

//***********************************************************************
//
// Function: write_to_file
//
// Purpose: Write all of the Rubik's Cube's data to a file. The stream
//    to do this is given by the parameter.
//
// Parameters: ostream& outs - the stream (method) in which to output data
//
//***********************************************************************
void Rubiks_Cube::write_to_file(ostream& outs){
  outs << move_rotation << endl;
  outs << x_rotation << endl;
  outs << y_rotation << endl;
  tlfp->write_cube(outs);
  tlmp->write_cube(outs);
  tlbp->write_cube(outs);
  tmfp->write_cube(outs);
  tmmp->write_cube(outs);
  tmbp->write_cube(outs);
  trfp->write_cube(outs);
  trmp->write_cube(outs);
  trbp->write_cube(outs);
  mlfp->write_cube(outs);
  mlmp->write_cube(outs);
  mlbp->write_cube(outs);
  mmfp->write_cube(outs);
  mmmp->write_cube(outs);
  mmbp->write_cube(outs);
  mrfp->write_cube(outs);
  mrmp->write_cube(outs);
  mrbp->write_cube(outs);
  dlfp->write_cube(outs);
  dlmp->write_cube(outs);
  dlbp->write_cube(outs);
  dmfp->write_cube(outs);
  dmmp->write_cube(outs);
  dmbp->write_cube(outs);
  drfp->write_cube(outs);
  drmp->write_cube(outs);
  drbp->write_cube(outs);
}

//***********************************************************************
//
// Function: load_from_file
//
// Purpose: Loads all of the Rubik's Cube's data from a file. The stream 
//    to do this will be given by the parameter. 
//
// Parameters: istream& ins - the stream (method) in which to input data
//
//***********************************************************************
void Rubiks_Cube::load_from_file(istream& ins){
  ins >> move_rotation;
  ins >> x_rotation;
  ins >> y_rotation;
  tlfp->load_cube(ins);
  tlmp->load_cube(ins);
  tlbp->load_cube(ins);
  tmfp->load_cube(ins);
  tmmp->load_cube(ins);
  tmbp->load_cube(ins);
  trfp->load_cube(ins);
  trmp->load_cube(ins);
  trbp->load_cube(ins);
  mlfp->load_cube(ins);
  mlmp->load_cube(ins);
  mlbp->load_cube(ins);
  mmfp->load_cube(ins);
  mmmp->load_cube(ins);
  mmbp->load_cube(ins);
  mrfp->load_cube(ins);
  mrmp->load_cube(ins);
  mrbp->load_cube(ins);
  dlfp->load_cube(ins);
  dlmp->load_cube(ins);
  dlbp->load_cube(ins);
  dmfp->load_cube(ins);
  dmmp->load_cube(ins);
  dmbp->load_cube(ins);
  drfp->load_cube(ins);
  drmp->load_cube(ins);
  drbp->load_cube(ins);
}

//accessor
int Rubiks_Cube::get_x_rotation(){
  return x_rotation;
}

//accessor
int Rubiks_Cube::get_y_rotation(){
  return y_rotation;
}

//accessor
int Rubiks_Cube::get_direction(){
  return direction;
}

//mutator
void Rubiks_Cube::mutate_direction(int d){
  direction=d;
}

//accessor
int Rubiks_Cube::get_x_axis(){
  return x_axis;
}

//accessor
int Rubiks_Cube::get_y_axis(){
  return y_axis;
}

//accessor
int Rubiks_Cube::get_z_axis(){
  return z_axis;
}

//mutator
void Rubiks_Cube::mutate_in_progress(bool progress){
  in_progress=progress;
}

//accessor
int Rubiks_Cube::get_move_rotation(){
  return move_rotation;
}

//accessor
bool Rubiks_Cube::get_in_progress(){
  return in_progress;
}

//***********************************************************************
//
// Function: reset_move_rotation
//
// Purpose: reset the move animation angle to zero for future animations. 
//
//***********************************************************************
void Rubiks_Cube::reset_move_rotation(){
  move_rotation=ZERO;
}

//***********************************************************************
//
// Function: increase_move_rotation
//
// Purpose: Allow animation of a move by increasing the angle over a period
//    of time.
//
//***********************************************************************
void Rubiks_Cube::increase_move_rotation(){
  move_rotation+=speed;
}

//***********************************************************************
//
// Function: decrease_move_rotation
//
// Purpose: Allow animation of a move by decreasing the angle over a period
//    of time.
//
//***********************************************************************
void Rubiks_Cube::decrease_move_rotation(){
  move_rotation-=speed;
}

//***********************************************************************
//
// Function: increase_speed
//
// Purpose: Allows the user to increase the animation speed of a move
//    being done on the Rubik's Cube.
//
//***********************************************************************
void Rubiks_Cube::increase_speed(){
  speed+=ONE;
  if(speed>MAX_SPEED){
    speed=MAX_SPEED;
  }
}

//***********************************************************************
//
// Function: decrease_speed
//
// Purpose: Allows the user to decrease the animation speed of a move
//    being done on the Rubik's Cube.
//
//***********************************************************************
void Rubiks_Cube::decrease_speed(){
  speed-=ONE;
  if(speed<MIN_SPEED){
    speed=MIN_SPEED;
  }
}

//***********************************************************************
//
// Function: draw
//
// Purpose: Draws the Rubik's Cube. Translates and rotates each cube to
//    each cube's properties for proper orientation of the final Rubik's
//    Cube. 
//
// Parameters: GLenum mode - GL_RENDER or GL_SELECT
//
// Calls: TLF::get_rotation
//        TLF::get_x_axis
//        TLF::get_y_axis
//        TLF::get_z_axis
//        TLF::get_x
//        TLF::get_y
//        TLF::get_z
//
//***********************************************************************
void Rubiks_Cube::draw(GLenum mode){
  glPushMatrix();
  glRotatef(tlfp->get_rotation(),tlfp->get_x_axis(),tlfp->get_y_axis(),tlfp->get_z_axis());
  glTranslatef(tlfp->get_x(),tlfp->get_y(),tlfp->get_z()); 
  tlfp->draw(mode,ID_TLF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(tlmp->get_rotation(),tlmp->get_x_axis(),tlmp->get_y_axis(),tlmp->get_z_axis());
  glTranslatef(tlmp->get_x(),tlmp->get_y(),tlmp->get_z()); 
  tlmp->draw(mode,ID_TLM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(tlbp->get_rotation(),tlbp->get_x_axis(),tlbp->get_y_axis(),tlbp->get_z_axis());
  glTranslatef(tlbp->get_x(),tlbp->get_y(),tlbp->get_z()); 
  tlbp->draw(mode,ID_TLB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(tmfp->get_rotation(),tmfp->get_x_axis(),tmfp->get_y_axis(),tmfp->get_z_axis());
  glTranslatef(tmfp->get_x(),tmfp->get_y(),tmfp->get_z()); 
  tmfp->draw(mode,ID_TMF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(tmmp->get_rotation(),tmmp->get_x_axis(),tmmp->get_y_axis(),tmmp->get_z_axis());
  glTranslatef(tmmp->get_x(),tmmp->get_y(),tmmp->get_z()); 
  tmmp->draw(mode,ID_TMM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(tmbp->get_rotation(),tmbp->get_x_axis(),tmbp->get_y_axis(),tmbp->get_z_axis());
  glTranslatef(tmbp->get_x(),tmbp->get_y(),tmbp->get_z()); 
  tmbp->draw(mode,ID_TMB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(trfp->get_rotation(),trfp->get_x_axis(),trfp->get_y_axis(),trfp->get_z_axis());
  glTranslatef(trfp->get_x(),trfp->get_y(),trfp->get_z()); 
  trfp->draw(mode,ID_TRF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(trmp->get_rotation(),trmp->get_x_axis(),trmp->get_y_axis(),trmp->get_z_axis());
  glTranslatef(trmp->get_x(),trmp->get_y(),trmp->get_z()); 
  trmp->draw(mode,ID_TRM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(trbp->get_rotation(),trbp->get_x_axis(),trbp->get_y_axis(),trbp->get_z_axis());
  glTranslatef(trbp->get_x(),trbp->get_y(),trbp->get_z()); 
  trbp->draw(mode,ID_TRB); 
  glPopMatrix();

  glPushMatrix();
  glRotatef(mlfp->get_rotation(),mlfp->get_x_axis(),mlfp->get_y_axis(),mlfp->get_z_axis());
  glTranslatef(mlfp->get_x(),mlfp->get_y(),mlfp->get_z()); 
  mlfp->draw(mode,ID_MLF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mlmp->get_rotation(),mlmp->get_x_axis(),mlmp->get_y_axis(),mlmp->get_z_axis());
  glTranslatef(mlmp->get_x(),mlmp->get_y(),mlmp->get_z()); 
  mlmp->draw(mode,ID_MLM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mlbp->get_rotation(),mlbp->get_x_axis(),mlbp->get_y_axis(),mlbp->get_z_axis());
  glTranslatef(mlbp->get_x(),mlbp->get_y(),mlbp->get_z()); 
  mlbp->draw(mode,ID_MLB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mmfp->get_rotation(),mmfp->get_x_axis(),mmfp->get_y_axis(),mmfp->get_z_axis());
  glTranslatef(mmfp->get_x(),mmfp->get_y(),mmfp->get_z()); 
  mmfp->draw(mode,ID_MMF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mmmp->get_rotation(),mmmp->get_x_axis(),mmmp->get_y_axis(),mmmp->get_z_axis());
  glTranslatef(mmmp->get_x(),mmmp->get_y(),mmmp->get_z()); 
  mmmp->draw(mode,ID_MMM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mmbp->get_rotation(),mmbp->get_x_axis(),mmbp->get_y_axis(),mmbp->get_z_axis());
  glTranslatef(mmbp->get_x(),mmbp->get_y(),mmbp->get_z()); 
  mmbp->draw(mode,ID_MMB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mrfp->get_rotation(),mrfp->get_x_axis(),mrfp->get_y_axis(),mrfp->get_z_axis());
  glTranslatef(mrfp->get_x(),mrfp->get_y(),mrfp->get_z()); 
  mrfp->draw(mode,ID_MRF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mrmp->get_rotation(),mrmp->get_x_axis(),mrmp->get_y_axis(),mrmp->get_z_axis());
  glTranslatef(mrmp->get_x(),mrmp->get_y(),mrmp->get_z()); 
  mrmp->draw(mode,ID_MRM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(mrbp->get_rotation(),mrbp->get_x_axis(),mrbp->get_y_axis(),mrbp->get_z_axis());
  glTranslatef(mrbp->get_x(),mrbp->get_y(),mrbp->get_z()); 
  mrbp->draw(mode,ID_MRB); 
  glPopMatrix();

  glPushMatrix();
  glRotatef(dlfp->get_rotation(),dlfp->get_x_axis(),dlfp->get_y_axis(),dlfp->get_z_axis());
  glTranslatef(dlfp->get_x(),dlfp->get_y(),dlfp->get_z()); 
  dlfp->draw(mode,ID_DLF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(dlmp->get_rotation(),dlmp->get_x_axis(),dlmp->get_y_axis(),dlmp->get_z_axis());
  glTranslatef(dlmp->get_x(),dlmp->get_y(),dlmp->get_z()); 
  dlmp->draw(mode,ID_DLM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(dlbp->get_rotation(),dlbp->get_x_axis(),dlbp->get_y_axis(),dlbp->get_z_axis());
  glTranslatef(dlbp->get_x(),dlbp->get_y(),dlbp->get_z()); 
  dlbp->draw(mode,ID_DLB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(dmfp->get_rotation(),dmfp->get_x_axis(),dmfp->get_y_axis(),dmfp->get_z_axis());
  glTranslatef(dmfp->get_x(),dmfp->get_y(),dmfp->get_z()); 
  dmfp->draw(mode,ID_DMF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(dmmp->get_rotation(),dmmp->get_x_axis(),dmmp->get_y_axis(),dmmp->get_z_axis());
  glTranslatef(dmmp->get_x(),dmmp->get_y(),dmmp->get_z()); 
  dmmp->draw(mode,ID_DMM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(dmbp->get_rotation(),dmbp->get_x_axis(),dmbp->get_y_axis(),dmbp->get_z_axis());
  glTranslatef(dmbp->get_x(),dmbp->get_y(),dmbp->get_z()); 
  dmbp->draw(mode,ID_DMB); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(drfp->get_rotation(),drfp->get_x_axis(),drfp->get_y_axis(),drfp->get_z_axis());
  glTranslatef(drfp->get_x(),drfp->get_y(),drfp->get_z()); 
  drfp->draw(mode,ID_DRF); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(drmp->get_rotation(),drmp->get_x_axis(),drmp->get_y_axis(),drmp->get_z_axis());
  glTranslatef(drmp->get_x(),drmp->get_y(),drmp->get_z()); 
  drmp->draw(mode,ID_DRM); 
  glPopMatrix();
  glPushMatrix();
  glRotatef(drbp->get_rotation(),drbp->get_x_axis(),drbp->get_y_axis(),drbp->get_z_axis());
  glTranslatef(drbp->get_x(),drbp->get_y(),drbp->get_z()); 
  drbp->draw(mode,ID_DRB); 
  glPopMatrix();
}

//***********************************************************************
//
// Function: choose_cubes_top_left_right
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current top layered cubes that can be moved left and right
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_top_left_right(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=trfp;
  blocks[1]=trmp;
  blocks[2]=trbp;
  blocks[3]=tmbp;
  blocks[4]=tlbp;
  blocks[5]=tlmp;
  blocks[6]=tlfp;
  blocks[7]=tmfp;
  blocks[8]=tmmp;
}

//***********************************************************************
//
// Function: choose_cubes_MH_left_right
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current middle horizontal layered cubes that can be moved left and right
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_MH_left_right(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=mrfp;
  blocks[1]=mrmp;
  blocks[2]=mrbp;
  blocks[3]=mmbp;
  blocks[4]=mlbp;
  blocks[5]=mlmp;
  blocks[6]=mlfp;
  blocks[7]=mmfp;
  blocks[8]=mmmp;
}

//***********************************************************************
//
// Function: choose_cubes_bottom_left_right
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current bottom layered cubes that can be moved left and right
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_bottom_left_right(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=drfp;
  blocks[1]=drmp;
  blocks[2]=drbp;
  blocks[3]=dmbp;
  blocks[4]=dlbp;
  blocks[5]=dlmp;
  blocks[6]=dlfp;
  blocks[7]=dmfp;
  blocks[8]=dmmp;
}

//***********************************************************************
//
// Function: choose_cubes_left_up_down
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current left stacked cubes that can be moved up and down
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_left_up_down(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=tlfp;
  blocks[1]=tlmp;
  blocks[2]=tlbp;
  blocks[3]=mlbp;
  blocks[4]=dlbp;
  blocks[5]=dlmp;
  blocks[6]=dlfp;
  blocks[7]=mlfp;
  blocks[8]=mlmp;
}

//***********************************************************************
//
// Function: choose_cubes_MV_up_down
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current middle vertical stacked cubes that can be moved up and down
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_MV_up_down(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=tmfp;
  blocks[1]=tmmp;
  blocks[2]=tmbp;
  blocks[3]=mmbp;
  blocks[4]=dmbp;
  blocks[5]=dmmp;
  blocks[6]=dmfp;
  blocks[7]=mmfp;
  blocks[8]=mmmp;
}

//***********************************************************************
//
// Function: choose_cubes_right_up_down
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current right stacked cubes that can be moved up and down
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_right_up_down(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=trfp;
  blocks[1]=trmp;
  blocks[2]=trbp;
  blocks[3]=mrbp;
  blocks[4]=drbp;
  blocks[5]=drmp;
  blocks[6]=drfp;
  blocks[7]=mrfp;
  blocks[8]=mrmp;
}

//***********************************************************************
//
// Function: choose_cubes_front_cw_ccw
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current front faced cubes that can be moved clockwise and counter_clockwise
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_front_cw_ccw(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=trfp;
  blocks[1]=mrfp;
  blocks[2]=drfp;
  blocks[3]=dmfp;
  blocks[4]=dlfp;
  blocks[5]=mlfp;
  blocks[6]=tlfp;
  blocks[7]=tmfp;
  blocks[8]=mmfp;
}

//***********************************************************************
//
// Function: choose_cubes_MF_cw_ccw
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current middle faced cubes that can be moved clockwise and counter_clockwise
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_MF_cw_ccw(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=trmp;
  blocks[1]=mrmp;
  blocks[2]=drmp;
  blocks[3]=dmmp;
  blocks[4]=dlmp;
  blocks[5]=mlmp;
  blocks[6]=tlmp;
  blocks[7]=tmmp;
  blocks[8]=mmmp;
}

//***********************************************************************
//
// Function: choose_cubes_back_cw_ccw
//
// Purpose: Changes the array that is passed in to hold data for the 
//    current back faced cubes that can be moved clockwise and counter_clockwise
//
// Parameters: TLF* blocks - an array of cube pointers of size POSSIBLE_MOVES
//
//***********************************************************************
void Rubiks_Cube::choose_cubes_back_cw_ccw(TLF* blocks[POSSIBLE_MOVES]){
  blocks[0]=trbp;
  blocks[1]=mrbp;
  blocks[2]=drbp;
  blocks[3]=dmbp;
  blocks[4]=dlbp;
  blocks[5]=mlbp;
  blocks[6]=tlbp;
  blocks[7]=tmbp;
  blocks[8]=mmbp;
}

//***********************************************************************
//
// Function: top_move_left
//
// Purpose: Changes the orientation of all the top layered cubes so as to
//    implement a realistic move of moving the top layer of a Rubik's Cube
//    left
//
// Calls: TLF::top_move_left
//
//***********************************************************************
void Rubiks_Cube::top_move_left(){ 
  trfp->top_move_left();
  trmp->top_move_left();
  trbp->top_move_left();
  tmbp->top_move_left();
  tlbp->top_move_left();
  tlmp->top_move_left();
  tlfp->top_move_left();
  tmfp->top_move_left();
  tmmp->top_move_left();

  temp_p=trfp;
  trfp=trbp;
  trbp=tlbp;
  tlbp=tlfp;
  tlfp=temp_p;
  temp_p=tmfp;
  tmfp=trmp;
  trmp=tmbp;
  tmbp=tlmp;
  tlmp=temp_p;
}

//***********************************************************************
//
// Function: top_move_right
//
// Purpose: Changes the orientation of all the top layered cubes so as to
//    implement a realistic move of moving the top layer of a Rubik's Cube
//    right
//
// Calls: TLF::top_move_right
//
//***********************************************************************
void Rubiks_Cube::top_move_right(){ 
  trfp->top_move_right();
  trmp->top_move_right();
  trbp->top_move_right();
  tmbp->top_move_right();
  tlbp->top_move_right();
  tlmp->top_move_right();
  tlfp->top_move_right();
  tmfp->top_move_right();
  tmmp->top_move_right();
  
  temp_p=trfp;
  trfp=tlfp;
  tlfp=tlbp;
  tlbp=trbp;
  trbp=temp_p;
  temp_p=tmfp;
  tmfp=tlmp;
  tlmp=tmbp;
  tmbp=trmp;
  trmp=temp_p;
}

//***********************************************************************
//
// Function: middle_horizontal_move_left
//
// Purpose: Changes the orientation of all the middle layered cubes so as to
//    implement a realistic move of moving the middle layer of a Rubik's Cube
//    left
//
// Calls: TLF::middle_horizontal_move_left
//
//***********************************************************************
void Rubiks_Cube::middle_horizontal_move_left(){
  mrfp->middle_horizontal_move_left();
  mrmp->middle_horizontal_move_left();
  mrbp->middle_horizontal_move_left();
  mmbp->middle_horizontal_move_left();
  mlbp->middle_horizontal_move_left();
  mlmp->middle_horizontal_move_left();
  mlfp->middle_horizontal_move_left();
  mmfp->middle_horizontal_move_left();
  mmmp->middle_horizontal_move_left();

  temp_p=mrfp;
  mrfp=mrbp;
  mrbp=mlbp;
  mlbp=mlfp;
  mlfp=temp_p;
  temp_p=mmfp;
  mmfp=mrmp;
  mrmp=mmbp;
  mmbp=mlmp;
  mlmp=temp_p;
}

//***********************************************************************
//
// Function: middle_horizontal_move_right
//
// Purpose: Changes the orientation of all the middle layered cubes so as to
//    implement a realistic move of moving the middle layer of a Rubik's Cube
//    right
//
// Calls: TLF::middle_horizontal_move_right
//
//***********************************************************************
void Rubiks_Cube::middle_horizontal_move_right(){ //originally MH MOVE LEFT
  mrfp->middle_horizontal_move_right();
  mrmp->middle_horizontal_move_right();
  mrbp->middle_horizontal_move_right();
  mmbp->middle_horizontal_move_right();
  mlbp->middle_horizontal_move_right();
  mlmp->middle_horizontal_move_right();
  mlfp->middle_horizontal_move_right();
  mmfp->middle_horizontal_move_right();
  mmmp->middle_horizontal_move_right();
  
  temp_p=mrfp;
  mrfp=mlfp;
  mlfp=mlbp;
  mlbp=mrbp;
  mrbp=temp_p;
  temp_p=mmfp;
  mmfp=mlmp;
  mlmp=mmbp;
  mmbp=mrmp;
  mrmp=temp_p;
}

//***********************************************************************
//
// Function: bottom_move_left
//
// Purpose: Changes the orientation of all the bottom layered cubes so as to
//    implement a realistic move of moving the bottom layer of a Rubik's Cube
//    left
//
// Calls: TLF::bottom_move_left
//
//***********************************************************************
void Rubiks_Cube::bottom_move_left(){ //originally BOTTOM MOVE RIGHT
  drfp->bottom_move_left();
  drmp->bottom_move_left();
  drbp->bottom_move_left();
  dmbp->bottom_move_left();
  dlbp->bottom_move_left();
  dlmp->bottom_move_left();
  dlfp->bottom_move_left();
  dmfp->bottom_move_left();
  dmmp->bottom_move_left();

  temp_p=drfp;
  drfp=drbp;
  drbp=dlbp;
  dlbp=dlfp;
  dlfp=temp_p;
  temp_p=dmfp;
  dmfp=drmp;
  drmp=dmbp;
  dmbp=dlmp;
  dlmp=temp_p;
}

//***********************************************************************
//
// Function: bottom_move_right
//
// Purpose: Changes the orientation of all the bottom layered cubes so as to
//    implement a realistic move of moving the bottom layer of a Rubik's Cube
//    right
//
// Calls: TLF::bottom_move_right
//
//***********************************************************************
void Rubiks_Cube::bottom_move_right(){ //originally BOTTOM_MOVE_LEFT
  drfp->bottom_move_right();
  drmp->bottom_move_right();
  drbp->bottom_move_right();
  dmbp->bottom_move_right();
  dlbp->bottom_move_right();
  dlmp->bottom_move_right();
  dlfp->bottom_move_right();
  dmfp->bottom_move_right();
  dmmp->bottom_move_right();
  
  temp_p=drfp;
  drfp=dlfp;
  dlfp=dlbp;
  dlbp=drbp;
  drbp=temp_p;
  temp_p=dmfp;
  dmfp=dlmp;
  dlmp=dmbp;
  dmbp=drmp;
  drmp=temp_p;
}

//***********************************************************************
//
// Function: left_move_down
//
// Purpose: Changes the orientation of all the left stacked cubes so as to
//    implement a realistic move of moving the left stacks of a Rubik's Cube
//    down
//
// Calls: TLF::left_move_down
//
//***********************************************************************
void Rubiks_Cube::left_move_down(){
  tlfp->left_move_down();
  tlmp->left_move_down();
  tlbp->left_move_down();
  mlbp->left_move_down();
  dlbp->left_move_down();
  dlmp->left_move_down();
  dlfp->left_move_down();
  mlfp->left_move_down();
  mlmp->left_move_down();

  temp_p=tlfp;
  tlfp=tlbp;
  tlbp=dlbp;
  dlbp=dlfp;
  dlfp=temp_p;
  temp_p=tlmp;
  tlmp=mlbp;
  mlbp=dlmp;
  dlmp=mlfp;
  mlfp=temp_p;
}

//***********************************************************************
//
// Function: left_move_up
//
// Purpose: Changes the orientation of all the left stacked cubes so as to
//    implement a realistic move of moving the left stacks of a Rubik's Cube
//    up
//
// Calls: TLF::left_move_up
//
//***********************************************************************
void Rubiks_Cube::left_move_up(){
  tlfp->left_move_up();
  tlmp->left_move_up();
  tlbp->left_move_up();
  mlbp->left_move_up();
  dlbp->left_move_up();
  dlmp->left_move_up();
  dlfp->left_move_up();
  mlfp->left_move_up(); 
  mlmp->left_move_up();

  temp_p=tlfp;
  tlfp=dlfp;
  dlfp=dlbp;
  dlbp=tlbp;
  tlbp=temp_p;
  temp_p=tlmp;
  tlmp=mlfp;
  mlfp=dlmp;
  dlmp=mlbp;
  mlbp=temp_p;
}
  
//***********************************************************************
//
// Function: middle_vertical_move_down
//
// Purpose: Changes the orientation of all the middle vertical stacked cubes so as to
//    implement a realistic move of moving the middle vertical stacks of a Rubik's Cube
//    down
//
// Calls: TLF::middle_vertical_move_down
//
//***********************************************************************
void Rubiks_Cube::middle_vertical_move_down(){
  tmfp->middle_vertical_move_down();
  tmmp->middle_vertical_move_down();
  tmbp->middle_vertical_move_down();
  mmbp->middle_vertical_move_down();
  dmbp->middle_vertical_move_down();
  dmmp->middle_vertical_move_down();
  dmfp->middle_vertical_move_down();
  mmfp->middle_vertical_move_down(); 
  mmmp->middle_vertical_move_down();

  temp_p=tmfp;
  tmfp=tmbp;
  tmbp=dmbp;
  dmbp=dmfp;
  dmfp=temp_p;
  temp_p=tmmp;
  tmmp=mmbp;
  mmbp=dmmp;
  dmmp=mmfp;
  mmfp=temp_p;
}

//***********************************************************************
//
// Function: middle_vertical_move_up
//
// Purpose: Changes the orientation of all the middle vertical stacked cubes so as to
//    implement a realistic move of moving the middle vertical stacks of a Rubik's Cube
//    up
//
// Calls: TLF::middle_vertical_move_up
//
//***********************************************************************
void Rubiks_Cube::middle_vertical_move_up(){  
  tmfp->middle_vertical_move_up();
  tmmp->middle_vertical_move_up();
  tmbp->middle_vertical_move_up();
  mmbp->middle_vertical_move_up();
  dmbp->middle_vertical_move_up();
  dmmp->middle_vertical_move_up();
  dmfp->middle_vertical_move_up();
  mmfp->middle_vertical_move_up();
  mmmp->middle_vertical_move_up();

  temp_p=tmfp;
  tmfp=dmfp;
  dmfp=dmbp;
  dmbp=tmbp;
  tmbp=temp_p;
  temp_p=tmmp;
  tmmp=mmfp;
  mmfp=dmmp;
  dmmp=mmbp;
  mmbp=temp_p;
}

//***********************************************************************
//
// Function: right_move_down
//
// Purpose: Changes the orientation of all the right stacked cubes so as to
//    implement a realistic move of moving the right stacks of a Rubik's Cube
//    down
//
// Calls: TLF::right_move_down
//
//***********************************************************************
void Rubiks_Cube::right_move_down(){
  trfp->right_move_down();
  trmp->right_move_down();
  trbp->right_move_down();
  mrbp->right_move_down();
  drbp->right_move_down();
  drmp->right_move_down();
  drfp->right_move_down();
  mrfp->right_move_down();
  mrmp->right_move_down();

  temp_p=trfp;
  trfp=trbp;
  trbp=drbp;
  drbp=drfp;
  drfp=temp_p;
  temp_p=trmp;
  trmp=mrbp;
  mrbp=drmp;
  drmp=mrfp;
  mrfp=temp_p;
}

//***********************************************************************
//
// Function: right_move_up
//
// Purpose: Changes the orientation of all the right stacked cubes so as to
//    implement a realistic move of moving the right stacks of a Rubik's Cube
//    right
//
// Calls: TLF::right_move_up
//
//***********************************************************************
void Rubiks_Cube::right_move_up(){
  trfp->right_move_up();
  trmp->right_move_up();
  trbp->right_move_up();
  mrbp->right_move_up();
  drbp->right_move_up();
  drmp->right_move_up();
  drfp->right_move_up();
  mrfp->right_move_up();
  mrmp->right_move_up(); 

  temp_p=trfp;
  trfp=drfp;
  drfp=drbp;
  drbp=trbp;
  trbp=temp_p;
  temp_p=trmp;
  trmp=mrfp;
  mrfp=drmp;
  drmp=mrbp;
  mrbp=temp_p;
}

//***********************************************************************
//
// Function: front_face_cw
//
// Purpose: Changes the orientation of all the front faced cubes so as to
//    implement a realistic move of moving the front faced cubes of a Rubik's Cube
//    clockwise
//
// Calls: TLF::front_face_cw
//
//***********************************************************************
void Rubiks_Cube::front_face_cw(){
  trfp->front_face_cw();
  mrfp->front_face_cw();
  drfp->front_face_cw();
  dmfp->front_face_cw();
  dlfp->front_face_cw();
  mlfp->front_face_cw();
  tlfp->front_face_cw();
  tmfp->front_face_cw();
  mmfp->front_face_cw();

  temp_p=trfp;
  trfp=tlfp;
  tlfp=dlfp;
  dlfp=drfp;
  drfp=temp_p;
  temp_p=tmfp;
  tmfp=mlfp;
  mlfp=dmfp;
  dmfp=mrfp;
  mrfp=temp_p;
}

//***********************************************************************
//
// Function: front_face_ccw
//
// Purpose: Changes the orientation of all the front faced cubes so as to
//    implement a realistic move of moving the front faced cubes of a Rubik's Cube
//    counter-clockwise
//
// Calls: TLF::front_face_ccw
//
//***********************************************************************
void Rubiks_Cube::front_face_ccw(){
  trfp->front_face_ccw();
  mrfp->front_face_ccw();
  drfp->front_face_ccw();
  dmfp->front_face_ccw();
  dlfp->front_face_ccw();
  mlfp->front_face_ccw();
  tlfp->front_face_ccw();
  tmfp->front_face_ccw();
  mmfp->front_face_ccw();

  temp_p=trfp;
  trfp=drfp;
  drfp=dlfp;
  dlfp=tlfp;
  tlfp=temp_p;
  temp_p=tmfp;
  tmfp=mrfp;
  mrfp=dmfp;
  dmfp=mlfp;
  mlfp=temp_p;
}

//***********************************************************************
//
// Function: middle_face_cw
//
// Purpose: Changes the orientation of all the middle faced cubes so as to
//    implement a realistic move of moving the middle faced cubes of a Rubik's Cube
//    clockwise
//
// Calls: TLF::middle_face_cw
//
//***********************************************************************
void Rubiks_Cube::middle_face_cw(){
  trmp->middle_face_cw();
  mrmp->middle_face_cw();
  drmp->middle_face_cw();
  dmmp->middle_face_cw();
  dlmp->middle_face_cw();
  mlmp->middle_face_cw();
  tlmp->middle_face_cw();
  tmmp->middle_face_cw();
  mmmp->middle_face_cw();

  temp_p=trmp;
  trmp=tlmp;
  tlmp=dlmp;
  dlmp=drmp;
  drmp=temp_p;
  temp_p=tmmp;
  tmmp=mlmp;
  mlmp=dmmp;
  dmmp=mrmp;
  mrmp=temp_p;
}

//***********************************************************************
//
// Function: middle_face_ccw
//
// Purpose: Changes the orientation of all the middle faced cubes so as to
//    implement a realistic move of moving the middle faced cubes of a Rubik's Cube
//    counter-clockwise
//
// Calls: TLF::middle_face_ccw
//
//***********************************************************************
void Rubiks_Cube::middle_face_ccw(){
  trmp->middle_face_ccw();
  mrmp->middle_face_ccw();
  drmp->middle_face_ccw();
  dmmp->middle_face_ccw();
  dlmp->middle_face_ccw();
  mlmp->middle_face_ccw();
  tlmp->middle_face_ccw();
  tmmp->middle_face_ccw();
  mmmp->middle_face_ccw(); 

  temp_p=trmp;
  trmp=drmp;
  drmp=dlmp;
  dlmp=tlmp;
  tlmp=temp_p;
  temp_p=tmmp;
  tmmp=mrmp;
  mrmp=dmmp;
  dmmp=mlmp;
  mlmp=temp_p;
}

//***********************************************************************
//
// Function: back_face_cw
//
// Purpose: Changes the orientation of all the back faced cubes so as to
//    implement a realistic move of moving the back faced cubes of a Rubik's Cube
//    clockwise
//
// Calls: TLF::back_face_cw
//
//***********************************************************************
void Rubiks_Cube::back_face_cw(){
  trbp->back_face_cw();
  mrbp->back_face_cw();
  drbp->back_face_cw();
  dmbp->back_face_cw();
  dlbp->back_face_cw();
  mlbp->back_face_cw();
  tlbp->back_face_cw();
  tmbp->back_face_cw();
  mmbp->back_face_cw();

  temp_p=trbp;
  trbp=tlbp;
  tlbp=dlbp;
  dlbp=drbp;
  drbp=temp_p;
  temp_p=tmbp;
  tmbp=mlbp;
  mlbp=dmbp;
  dmbp=mrbp;
  mrbp=temp_p;
}

//***********************************************************************
//
// Function: back_face_ccw
//
// Purpose: Changes the orientation of all the back faced cubes so as to
//    implement a realistic move of moving the back faced cubes of a Rubik's Cube
//    counter-clockwise
//
// Calls: TLF::back_face_ccw
//
//***********************************************************************
void Rubiks_Cube::back_face_ccw(){
  trbp->back_face_ccw();
  mrbp->back_face_ccw();
  drbp->back_face_ccw();
  dmbp->back_face_ccw();
  dlbp->back_face_ccw();
  mlbp->back_face_ccw();
  tlbp->back_face_ccw();
  tmbp->back_face_ccw();
  mmbp->back_face_ccw();

  temp_p=trbp;
  trbp=drbp;
  drbp=dlbp;
  dlbp=tlbp;
  tlbp=temp_p;
  temp_p=tmbp;
  tmbp=mrbp;
  mrbp=dmbp;
  dmbp=mlbp;
  mlbp=temp_p;
}


//***********************************************************************
//
// Function: check_front
//
// Purpose: Check the front face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_front
//
//***********************************************************************
bool Rubiks_Cube::check_front(){
  front=mmfp->get_front();
  if((front==tlfp->get_front())&&(front==tmfp->get_front())&&(front==trfp->get_front())&&
	(front==mlfp->get_front())&&(front==mrfp->get_front())&&
	(front==dlfp->get_front())&&(front==dmfp->get_front())&&(front==drfp->get_front())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_back
//
// Purpose: Check the back face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_back
//
//***********************************************************************
bool Rubiks_Cube::check_back(){
  back=mmbp->get_back();
  if((back==tlbp->get_back())&&(back==tmbp->get_back())&&(back==trbp->get_back())&&
	(back==mlbp->get_back())&&(back==mrbp->get_back())&&
	(back==dlbp->get_back())&&(back==dmbp->get_back())&&(back==drbp->get_back())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_top
//
// Purpose: Check the top face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_top
//
//***********************************************************************
bool Rubiks_Cube::check_top(){
  top=tmmp->get_top();
  if((top==tlfp->get_top())&&(top==tmfp->get_top())&&(top==trfp->get_top())&&
	(top==tlmp->get_top())&&(top==trmp->get_top())&&
	(top==tlbp->get_top())&&(top==tmbp->get_top())&&(top==trbp->get_top())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_bottom
//
// Purpose: Check the bottom face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_bottom
//
//***********************************************************************
bool Rubiks_Cube::check_bottom(){
  bottom=dmmp->get_bottom();
  if((bottom==dlfp->get_bottom())&&(bottom==dmfp->get_bottom())&&(bottom==drfp->get_bottom())&&
	(bottom==dlmp->get_bottom())&&(bottom==drmp->get_bottom())&&
	(bottom==dlbp->get_bottom())&&(bottom==dmbp->get_bottom())&&(bottom==drbp->get_bottom())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_left
//
// Purpose: Check the left face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_left
//
//***********************************************************************
bool Rubiks_Cube::check_left(){
  left=mlmp->get_left();
  if((left==tlfp->get_left())&&(left==tlmp->get_left())&&(left==tlbp->get_left())&&
	(left==mlfp->get_left())&&(left==mlbp->get_left())&&
	(left==dlfp->get_left())&&(left==dlmp->get_left())&&(left==dlbp->get_left())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_right
//
// Purpose: Check the right face of the rubiks cube to see if all the faces
//    of the individual cubes are the same color
//
// Calls: TLF::get_right
//
//***********************************************************************
bool Rubiks_Cube::check_right(){
  right=mrmp->get_right();
  if((right==trfp->get_right())&&(right==trmp->get_right())&&(right==trbp->get_right())&&
	(right==mrfp->get_right())&&(right==mrbp->get_right())&&
	(right==drfp->get_right())&&(right==drmp->get_right())&&(right==drbp->get_right())){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: check_win
//
// Purpose: Check every face of the Rubik' Cube to see if all the faces 
//    of the individual cubes are the same color to check if the user has
//    won the game.
//
// Calls: check_front
//        check_back
//        check_top
//        check_bottom
//        check_left
//        check_right
//
//***********************************************************************
bool Rubiks_Cube::check_win(){
  if(check_front()&&check_back()&&check_top()&&check_bottom()&&check_left()&&check_right()){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function:scramble_cube
//
// Purpose: Jumble up the cube positions in a way that is always possible
//    to solve. Takes a solved Rubiks cube and applies randomly chosen moves
//    to achieve this. Can also take a jumbled cube and further scramble it.
//
// Calls: TLF::top_move_right
//        TLF::top_move_left
//        TLF::middle_horizontal_move_right
//        TLF::middle_horizontal_move_left
//        TLF::bottom_move_right
//        TLF::bottom_move_left
//        TLF::left_move_up
//        TLF::left_move_down
//        TLF::middle_vertical_move_up
//        TLF::middle_vertical_move_down
//        TLF::right_move_up
//        TLF::right_move_down
//        TLF::front_face_cw
//        TLF::front_face_ccw
//        TLF::middle_face_cw
//        TLF::middle_face_ccw
//        TLF::back_face_cw
//        TLF::back_face_ccw
//
//***********************************************************************
void Rubiks_Cube::scramble_cube(){
  move_rotation=ZERO;
  x_rotation=ZERO;
  y_rotation=ZERO;
  int moves[SCRAMBLE];
  for(int i=ZERO;i<SCRAMBLE;i++){
    moves[i]=rand()%TOTAL_MOVES; //random() doesn't work with windows eclipse??
  }
  for(int i=ZERO;i<SCRAMBLE;i++){
    if(moves[i]==MOVE_TMR){
      top_move_right();
    }else if(moves[i]==MOVE_MHMR){
      middle_horizontal_move_right();
    }else if(moves[i]==MOVE_BMR){
      bottom_move_right();
    }else if(moves[i]==MOVE_LMU){
      left_move_up();
    }else if(moves[i]==MOVE_MVMU){
      middle_vertical_move_up();
    }else if(moves[i]==MOVE_RMU){
      right_move_up();
    }else if(moves[i]==MOVE_TML){
      top_move_left();
    }else if(moves[i]==MOVE_MHML){
      middle_horizontal_move_left();
    }else if(moves[i]==MOVE_BML){
      bottom_move_left();
    }else if(moves[i]==MOVE_LMD){
      left_move_down();
    }else if(moves[i]==MOVE_MVMD){
      middle_vertical_move_down();
    }else if(moves[i]==MOVE_RMD){
      right_move_down();
    }else if(moves[i]==MOVE_FCCW){
      front_face_ccw();
    }else if(moves[i]==MOVE_MCCW){
      middle_face_ccw();
    }else if(moves[i]==MOVE_BCCW){
      back_face_ccw();
    }else if(moves[i]==MOVE_FCW){
      front_face_cw();
    }else if(moves[i]==MOVE_MCW){
      middle_face_cw();
    }else if(moves[i]==MOVE_BCW){
      back_face_cw();
    }
  }
}
