//*********************************************************************
//
//  Program: final - a Rubik's Cube 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is a Rubik's Cube that displays the use of light.
//    It also incorporates sound. Loading and saving capabilities are 
//    present. Sound defaults to being off and lighting defaults to being on.
//    The user has a large degree of freedom to manipulate the 
//    cube in the way that he/she sees fit. This allows the user to solve
//    the Rubik's Cube as easily as possible. This is the best that I could 
//    make it. 
//
//  Last Updated: 11/16/2011
//
//*********************************************************************

#include <windows.h>
#include <GL/glut.h>	// GLUT toolkit
#include "objects.h"
using std::ofstream;
using std::ifstream;
using std::system;
using std::exit;

#define SIZE 512 //size for selection buffer
#define ONESECOND 1000 //used with fps (frames per second) to get amount of redraws per second
#define DISPLACEMENT_X 0.0 //x value to place camera and ship away from origin
#define DISPLACEMENT_Y 0.5 //y value to place camera and ship away from origin
#define DISPLACEMENT_Z 15.0 //z value to place camera and ship away from origin
#define VIEW_NEAR 1.0 //near side clipping plane distance for perspective view
#define VIEW_FAR 40.0 //far side clipping plane distance for perspective view
#define FOVYINCREMENT 5 //increment to increase/decrease field of view in gluPerspective
#define MAX_FOVY 110 //max field of view in gluPerspective
#define MIN_FOVY 65 //min field of view in gluPerspective
#define INIT_FOVY 75 //initial field of view for gluPerspective
#define NON_METALIC 20 //inital shine value of objects in program to make it not shiny
#define METALIC 120 //shine value to give metalic look to objects in program.
#define FPS 15 //frames per second
#define WINDOW_SIZE 500 //initial window size x and y
#define INIT_WINDOW_POSITION 100 //initial window position x and y
#define CIRCLE 360 //degrees in a circle
#define FOURTH_CIRCLE 90 //degrees in a fourth of a circle
#define EIGHTH_CIRCLE 45 //degrees in an eighth of a circle
#define THREE_EIGHTHS_CIRCLE 135 //degrees in three eighths of a circle
#define FIVE_EIGHTHS_CIRCLE 225 //degrees in five eighths of a circle
#define SEVEN_EIGHTHS_CIRCLE 315 //degrees in seven eighths of a circle
#define VIEWPORT_SIZE 4 //size of viewport buffer
#define MOUSEBOX 0.005 //very small square around mouse for picking. (small to minimize choosing two 
			//corresponding squares.

int choice=ZERO; //current move choice
GLuint nearest; //final closest selected object during picking process with mouse
ofstream outs; //output stream (method) for writing to file
ifstream ins; //input stream (method) for reading from file
TLF* cubes[POSSIBLE_MOVES]; //array of cube pointers to manipulate the correct cubes during
				//certain moves
int win_h=WINDOW_SIZE; //window height
int win_w=WINDOW_SIZE; //window width
int mouse_x;	// mouse's x position on screen
int mouse_y;	// mouse's y position on screen
int fps=FPS; //frames per second
GLfloat ratio=win_w/win_h; //ratio of screen for gluPerspective view
GLdouble fovy=INIT_FOVY; //the view angle for the screen in gluPerspective
GLubyte shine =	NON_METALIC; //shine value for objects in program
bool play_sound=false; //play the sound?
bool over_ride_play=true; //if play_sound is true, override and cancel out sound?
bool win=false; //is the game won?

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //values for ambient light
GLfloat DiffuseLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //values for diffuse light
GLfloat SpecularLight[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //values for specular light
GLfloat MaterialSpecular[] = {0.1f,0.1f,0.1f,1.0f}; //values for object specularity
GLfloat MaterialEmission[] = {0.05, 0.05, 0.05, 1.0}; //values for object emissions
GLfloat LightPos[] = {0.0f,0.0f,0.0f,0.0f}; //values for the position of the light source

Rubiks_Cube rc; //our Rubik's Cube


//***********************************************************************
//
// Function: draw_rubiks_cube
//
// Purpose: draw the Rubik's Cube with necessary rotation in order to allow
//    changing the way the user can look at the cube.
//
// Parameters: GLenum mode - GL_RENDER or GL_SELECT
//
// Calls: Rubiks_Cube::get_x_rotation
//        Rubiks_Cube::get_y_rotation
//
//***********************************************************************
void draw_rubiks_cube(GLenum mode){
  glPushMatrix();
  glRotatef(rc.get_x_rotation(), 1.0f, 0.0f, 0.0f);
  glRotatef(rc.get_y_rotation(), 0.0f, 1.0f, 0.0f);
  rc.draw(mode);
  glPopMatrix();
}

//***********************************************************************
//
// Function: unzoom_camera
//
// Purpose: change the field of view to zoom the camera (zoom out)
//
//***********************************************************************
void unzoom_camera(){
  fovy+=FOVYINCREMENT;
  if(fovy>MAX_FOVY){
    fovy=MAX_FOVY;
  }
}

//***********************************************************************
//
// Function: zoom_camera
//
// Purpose: change the field of view to zoom the camera (zoom in)
//
//***********************************************************************
void zoom_camera(){
  fovy-=FOVYINCREMENT;
  if(fovy<MIN_FOVY){
    fovy=MIN_FOVY;
  }
}

//***********************************************************************
//
// Function: processHits - code from mrl.nyu.edu/~elif/CG/lec9_4pp.pdf
//
// Purpose: Allows the user to pick the closest object above the mouse
//
// Paramaters: GLint hits - the number of different objects the user has clicked
//    on at a certain moment in time. 
//             GLuint buffer[] - the identification data that distinguishes which 
//    object is being processed
//
//***********************************************************************
void processHits (GLint hits, GLuint buffer[],int x,int y){

  unsigned int i, j;
  GLuint names,nameStackDepth,zmin,zmax,nearestZ,currname, *ptr;
  ptr = (GLuint *) buffer; 
  if(hits!=ZERO){//I ADDED THIS LINE
    nameStackDepth = *ptr++;
    zmin=*ptr++;
    zmax=*ptr++;
    nearestZ=zmin;
    for(j=ZERO;j<nameStackDepth;j++){
      currname=*ptr++;
    }
    nearest=currname;
  }

  //if more than 1 hit
  for(i=ONE;i<hits;i++){
    nameStackDepth=*ptr++;
    zmin=*ptr++;
    zmax=*ptr++;
    for(j=ZERO;j<nameStackDepth;j++){
      currname=*ptr++;
    }
    if(zmin<nearestZ){
      nearestZ=zmin;
      nearest=currname;
    }
  }
}

//***********************************************************************
//
// Function: mouse_move - code pulled from lec11 and modified by me
//    for use in this program
//
// Purpose: Allow the user to move the view of the cube with the mouse
//
// Paramaters: int x - the x position of the mouse on the screen
//             int y - the y position of the mouse on the screen
//
// Calls: Rubiks_Cube::mutate_x_rotation
//        Rubiks_Cube::mutate_y_rotation
//        Rubiks_Cube::get_x_rotation
//        Rubiks_Cube::get_y_rotation
//
//***********************************************************************
void mouse_move(int x, int y)
{
    // the x and y values affect the opposite axis values
    // because each is rotation "about an axis", not in a direction
    rc.mutate_x_rotation((rc.get_x_rotation()+(y-mouse_y)));
    mouse_y = y;					// refresh our x value
	
    rc.mutate_y_rotation((rc.get_y_rotation()+(x-mouse_x)));
    mouse_x = x;					// refresh our y value
	
    // Check x,y rotation values to keep 0-355
    if (rc.get_x_rotation() > CIRCLE)
      rc.mutate_x_rotation(rc.get_x_rotation()-CIRCLE);
	
    if (rc.get_x_rotation() < ZERO)
      rc.mutate_x_rotation(rc.get_x_rotation()+CIRCLE);

    if (rc.get_y_rotation() > CIRCLE)
      rc.mutate_y_rotation(rc.get_y_rotation()-CIRCLE);
	
    if (rc.get_y_rotation() < ZERO)
      rc.mutate_y_rotation(rc.get_y_rotation()+CIRCLE);

  glutPostRedisplay();
}

//***********************************************************************
//
// Function: mouse_press
//
// Purpose: gives the user mouse interactivity with the program. Allows for the 
//    user to click on specific objects and manipulate them.
//
// Paramaters: int btn - the button pressed with the mouse.
//             int state - the current state of the button being pressed by the 
//		   mouse (up or down).
//             int x - the x coordinate of the mouse on the screen
//             int y - the y coordinate of the mouse on the screen
//
// Calls: processHits
//        draw_rubiks_cube
//
//***********************************************************************
void mouse_press(int button, int state, int x, int y)
{
  GLuint selectBuf[SIZE];
  GLint hits;
  GLint viewport[VIEWPORT_SIZE];

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    mouse_x=x;
    mouse_y=y;
    glGetIntegerv (GL_VIEWPORT, viewport);

    // Must do the following BEFORE glInitNames()!
    glSelectBuffer (SIZE, selectBuf);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(ZERO);// Dummy first name on stack

    glMatrixMode (GL_PROJECTION);
    glPushMatrix ();
    glLoadIdentity ();

    /*  create 5x5 pixel picking region near cursor location	*/
    gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[VIEWPORT_SIZE-1] - y), 
		   MOUSEBOX, MOUSEBOX, viewport);
    gluPerspective( fovy, ratio, VIEW_NEAR, VIEW_FAR );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    draw_rubiks_cube(GL_SELECT);

    glPopMatrix();
    
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);

    hits = glRenderMode (GL_RENDER);
    processHits (hits, selectBuf,x,y);
  }
  glutPostRedisplay();
}

//***********************************************************************
//
// Function: my_timer
//
// Purpose: Slow the program down so the objects will move at a desired pace
//
// Paramaters: int extra - extra time 
//
//***********************************************************************
void my_timer(int extra){
  glutPostRedisplay();
  glutTimerFunc(ONESECOND/fps,my_timer,ZERO);
}

//***********************************************************************
//
// Function: load_file
//
// Purpose: load view angle and orientation of the Rubik's Cube from file
//
// Calls: Rubiks_Cube:: load_from_file
//
//***********************************************************************
void load_file(){
  ins.open("data.txt");
  if(ins){
    cout << "Loading from file" << endl;
    rc.load_from_file(ins);
  }else{
    cout << "Error loading file" << endl;
  }
  ins.close();
}

//***********************************************************************
//
// Function: save_file
//
// Purpose: save view angle and orientation of the Rubik's Cube to a file
//
// Calls: Rubiks_Cube:: write_to_file
//
//***********************************************************************
void save_file(){
  outs.open("data.txt");
  if(outs){
    cout << "Writing to file" << endl;
    rc.write_to_file(outs);
  }else{
    cout << "Error saving file" << endl;
  }
  outs.close();
}

//***********************************************************************
//
// Function: my_keyboard_fund
//
// Purpose: Process keyboard input to toggle sound, zoom/unzoom camera,
//	scramble the cube, save/load the game, enable/disable lighting, 
//	toggle metalic look, or quit the program.
//
// Paramaters: unsigned char key - the key that was pressed.
//             int x - the x coordinate of where the mouse is on the screen?
//             int y - the y coordinate of where the mouse is on the screen?
//
// Calls: unzoom_camera
//        zoom_camera
//        Rubiks_Cube::scramble_cube
//        load_file
//        save_file
//
//***********************************************************************
void my_keyboard_func(unsigned char key, int x, int y){
  switch (key)  {
    case 'o':
    case 'O':
      over_ride_play=!over_ride_play;
      break;
    case 'c':
      unzoom_camera();
      break;
    case 'C':
      zoom_camera();
      break;
    case 'n':
    case 'N':
      rc.scramble_cube();
      break;
    case 'l':
    case 'L':
      load_file();
      break;
    case 's':
    case 'S':
      save_file();
      break;
    case 't':
    case 'T':
      if(glIsEnabled(GL_LIGHTING)){
        glDisable(GL_LIGHTING);
      }else{
        glEnable(GL_LIGHTING);
      }
      break;
    case 'm':
    case 'M':
      if(shine==NON_METALIC){
        shine=METALIC;
      }else{
        shine=NON_METALIC;
      }
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
// Function: top_cubes
//
// Purpose: check if one of the top cubes can be manipulated
//
//***********************************************************************
bool top_cubes(){
  if((nearest==ID_TLF)||(nearest==ID_TMF)||(nearest==ID_TRF)||(nearest==ID_TLM)||(nearest==ID_TMM)||
	(nearest==ID_TRM)||(nearest==ID_TLB)||(nearest==ID_TMB)||(nearest==ID_TRB)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: middle_horizontal_cubes
//
// Purpose: check if one of the middle horizontal cubes can be manipulated
//
//***********************************************************************
bool middle_horizontal_cubes(){
  if((nearest==ID_MLF)||(nearest==ID_MMF)||(nearest==ID_MRF)||(nearest==ID_MLM)||(nearest==ID_MMM)||
	(nearest==ID_MRM)||(nearest==ID_MLB)||(nearest==ID_MMB)||(nearest==ID_MRB)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: bottom_cubes
//
// Purpose: check if one of the bottom cubes can be manipulated
//
//***********************************************************************
bool bottom_cubes(){
  if((nearest==ID_DLF)||(nearest==ID_DMF)||(nearest==ID_DRF)||(nearest==ID_DLM)||(nearest==ID_DMM)||
	(nearest==ID_DRM)||(nearest==ID_DLB)||(nearest==ID_DMB)||(nearest==ID_DRB)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: left_cubes
//
// Purpose: check if one of the left cubes can be manipulated
//
//***********************************************************************
bool left_cubes(){
  if((nearest==ID_TLF)||(nearest==ID_MLF)||(nearest==ID_DLF)||(nearest==ID_DLM)||(nearest==ID_DLB)||
	(nearest==ID_MLB)||(nearest==ID_TLB)||(nearest==ID_TLM)||(nearest==ID_MLM)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: middle_vertical_cubes
//
// Purpose: check if one of the middle vertical cubes can be manipulated
//
//***********************************************************************
bool middle_vertical_cubes(){
  if((nearest==ID_TMF)||(nearest==ID_MMF)||(nearest==ID_DMF)||(nearest==ID_DMM)||(nearest==ID_DMB)||
	(nearest==ID_MMB)||(nearest==ID_TMB)||(nearest==ID_TMM)||(nearest==ID_MMM)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: right_cubes
//
// Purpose: check if one of the right cubes can be manipulated
//
//***********************************************************************
bool right_cubes(){
  if((nearest==ID_TRF)||(nearest==ID_MRF)||(nearest==ID_DRF)||(nearest==ID_DRM)||(nearest==ID_DRB)||
	(nearest==ID_MRB)||(nearest==ID_TRB)||(nearest==ID_TRM)||(nearest==ID_MRM)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: front_cubes
//
// Purpose: check if one of the front cubes can be manipulated
//
//***********************************************************************
bool front_cubes(){
  if((nearest==ID_TLF)||(nearest==ID_TMF)||(nearest==ID_TRF)||(nearest==ID_MRF)||(nearest==ID_MMF)||
	(nearest==ID_MLF)||(nearest==ID_DLF)||(nearest==ID_DMF)||(nearest==ID_DRF)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: middle_face_cubes
//
// Purpose: check if one of the middle_face cubes can be manipulated
//
//***********************************************************************
bool middle_face_cubes(){
  if((nearest==ID_TLM)||(nearest==ID_TMM)||(nearest==ID_TRM)||(nearest==ID_MRM)||(nearest==ID_MMM)||
	(nearest==ID_MLM)||(nearest==ID_DLM)||(nearest==ID_DMM)||(nearest==ID_DRM)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: back_cubes
//
// Purpose: check if one of the back cubes can be manipulated
//
//***********************************************************************
bool back_cubes(){
  if((nearest==ID_TLB)||(nearest==ID_TMB)||(nearest==ID_TRB)||(nearest==ID_MRB)||(nearest==ID_MMB)||
	(nearest==ID_MLB)||(nearest==ID_DLB)||(nearest==ID_DMB)||(nearest==ID_DRB)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: choose_move_TMR
//
// Purpose: set the top move right move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_top_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_TMR(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_top_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_TMR;
}

//***********************************************************************
//
// Function: choose_move_MHMR
//
// Purpose: set the middle horizontal move right move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MH_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MHMR(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_MH_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_MHMR;
}

//***********************************************************************
//
// Function: choose_move_BMR
//
// Purpose: set the bottom move right move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_bottom_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_BMR(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_bottom_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_BMR;
}

//***********************************************************************
//
// Function: choose_move_LMU
//
// Purpose: set the left move up move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_left_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_LMU(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_left_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_LMU;
}


//***********************************************************************
//
// Function: choose_move_MVMU
//
// Purpose: set the middle vertical move up move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MV_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MVMU(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_MV_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_MVMU;
}

//***********************************************************************
//
// Function: choose_move_RMU
//
// Purpose: set the middle vertical move up move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_right_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_RMU(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_right_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_RMU;
}

//***********************************************************************
//
// Function: choose_move_TML
//
// Purpose: set the top move left move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_top_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_TML(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_top_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_TML;
}

//***********************************************************************
//
// Function: choose_move_MHML
//
// Purpose: set the middle horizontal move left move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MH_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MHML(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_MH_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_MHML;
}

//***********************************************************************
//
// Function: choose_move_BML
//
// Purpose: set the bottom move left move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_bottom_left_right
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_BML(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_bottom_left_right(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ONE,ZERO);
  }
  choice=MOVE_BML;
}

//***********************************************************************
//
// Function: choose_move_LMD
//
// Purpose: set the left move down move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_left_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_LMD(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_left_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_LMD;
}

//***********************************************************************
//
// Function: choose_move_MVMD
//
// Purpose: set the middle vertical move down move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MV_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MVMD(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_MV_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_MVMD;
}

//***********************************************************************
//
// Function: choose_move_RMD
//
// Purpose: set the right move down move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_right_up_down
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_RMD(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_right_up_down(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ONE,ZERO,ZERO);
  }
  choice=MOVE_RMD;
}

//***********************************************************************
//
// Function: choose_move_FCCW
//
// Purpose: set the front move counter_clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_front_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_FCCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_front_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_FCCW;
}

//***********************************************************************
//
// Function: choose_move_MCCW
//
// Purpose: set the middle face move counter_clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MF_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MCCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_MF_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_MCCW;
}

//***********************************************************************
//
// Function: choose_move_BCCW
//
// Purpose: set the back move counter_clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_back_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_BCCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ONE);
  rc.choose_cubes_back_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_BCCW;
}

//***********************************************************************
//
// Function: choose_move_FCW
//
// Purpose: set the front move clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_front_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_FCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_front_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_FCW;
}

//***********************************************************************
//
// Function: choose_move_MCW
//
// Purpose: set the middle face move clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_MF_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_MCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_MF_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_MCW;
}

//***********************************************************************
//
// Function: choose_move_BCW
//
// Purpose: set the back move clockwise move into animation and allows the 
//    inidivual cubes in the action to be set for this movement. Also makes
//    sure that other moves cannot be made while the animation is taking place.
//
// Calls: Rubiks_Cube::mutate_in_progress
//        Rubiks_Cube::mutate_direction
//        Rubiks_Cube::choose_cubes_back_cw_ccw
//        Rubiks_Cube::mutate_axese
//
//***********************************************************************
void choose_move_BCW(){
  rc.mutate_in_progress(true);
  rc.mutate_direction(ZERO);
  rc.choose_cubes_back_cw_ccw(cubes);
  for(int i=ZERO;i<POSSIBLE_MOVES;i++){
    cubes[i]->mutate_axese(ZERO,ZERO,ONE);
  }
  choice=MOVE_BCW;
}

//***********************************************************************
//
// Function: animate_horizontal_cubes_right
//
// Purpose: Covers more cases to clean up code. Animates cubes moving right.
//
// Calls: Rubiks_Cube::top_cubes
//        Rubiks_Cube::choose_move_TMR
//        Rubiks_Cube::middle_horizontal_cubes
//        Rubiks_Cube::choose_move_MHMR
//        Rubiks_Cube::bottom_cubes
//        Rubiks_Cube::choose_move_BMR
//
//***********************************************************************
void animate_horizontal_cubes_right(){
  if(top_cubes()){
    choose_move_TMR();
  }else if(middle_horizontal_cubes()){
    choose_move_MHMR();
  }else if(bottom_cubes()){
    choose_move_BMR();
  }
}

//***********************************************************************
//
// Function: animate_horizontal_cubes_left
//
// Purpose: Covers more cases to clean up code. Animates cubes moving left.
//
// Calls: Rubiks_Cube::top_cubes
//        Rubiks_Cube::choose_move_TML
//        Rubiks_Cube::middle_horizontal_cubes
//        Rubiks_Cube::choose_move_MHML
//        Rubiks_Cube::bottom_cubes
//        Rubiks_Cube::choose_move_BML
//
//***********************************************************************
void animate_horizontal_cubes_left(){
  if(top_cubes()){
    choose_move_TML();
  }else if(middle_horizontal_cubes()){
    choose_move_MHML();
  }else if(bottom_cubes()){
    choose_move_BML();
  }
}

//***********************************************************************
//
// Function: animate_vertical_cubes_up
//
// Purpose: Covers more cases to clean up code. Animates cubes moving up.
//
// Calls: Rubiks_Cube::left_cubes
//        Rubiks_Cube::choose_move_LMU
//        Rubiks_Cube::middle_vertical_cubes
//        Rubiks_Cube::choose_move_MVMU
//        Rubiks_Cube::right_cubes
//        Rubiks_Cube::choose_move_RMU
//
//***********************************************************************
void animate_vertical_cubes_up(){
  if(left_cubes()){
    choose_move_LMU();
  }else if(middle_vertical_cubes()){
    choose_move_MVMU();
  }else if(right_cubes()){
    choose_move_RMU();
  }
}

//***********************************************************************
//
// Function: animate_vertical_cubes_down
//
// Purpose: Covers more cases to clean up code. Animates cubes moving down.
//
// Calls: Rubiks_Cube::left_cubes
//        Rubiks_Cube::choose_move_LMD
//        Rubiks_Cube::middle_vertical_cubes
//        Rubiks_Cube::choose_move_MVMD
//        Rubiks_Cube::right_cubes
//        Rubiks_Cube::choose_move_RMD
//
//***********************************************************************
void animate_vertical_cubes_down(){
  if(left_cubes()){
    choose_move_LMD();
  }else if(middle_vertical_cubes()){
    choose_move_MVMD();
  }else if(right_cubes()){
    choose_move_RMD();
  }
}

//***********************************************************************
//
// Function: animate_faces_ccw
//
// Purpose: Covers more cases to clean up code. Animates cubes moving 
//		counter_clockwise.
//
// Calls: Rubiks_Cube::front_cubes
//        Rubiks_Cube::choose_move_FCCW
//        Rubiks_Cube::middle_face_cubes
//        Rubiks_Cube::choose_move_MCCW
//        Rubiks_Cube::back_cubes
//        Rubiks_Cube::choose_move_BCCW
//
//***********************************************************************
void animate_faces_ccw(){
  if(front_cubes()){
    choose_move_FCCW();
  }else if(middle_face_cubes()){
    choose_move_MCCW();
  }else if(back_cubes()){
    choose_move_BCCW();
  }
}

//***********************************************************************
//
// Function: animate_faces_cw
//
// Purpose: Covers more cases to clean up code. Animates cubes moving 
//		clockwise.
//
// Calls: Rubiks_Cube::front_cubes
//        Rubiks_Cube::choose_move_FCW
//        Rubiks_Cube::middle_face_cubes
//        Rubiks_Cube::choose_move_MCW
//        Rubiks_Cube::back_cubes
//        Rubiks_Cube::choose_move_BCW
//
//***********************************************************************
void animate_faces_cw(){
  if(front_cubes()){
    choose_move_FCW();
  }else if(middle_face_cubes()){
    choose_move_MCW();
  }else if(back_cubes()){
    choose_move_BCW();
  }
}


//***********************************************************************
//
// Function: quadrant_1
//
// Purpose: if the view of the Rubiks Cube is is quadrant 1, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_1(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_faces_cw();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_2
//
// Purpose: if the view of the Rubiks Cube is is quadrant 2, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_2(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_vertical_cubes_down();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_3
//
// Purpose: if the view of the Rubiks Cube is is quadrant 3, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_3(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_faces_ccw();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_4
//
// Purpose: if the view of the Rubiks Cube is is quadrant 4, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_4(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_vertical_cubes_up();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_5
//
// Purpose: if the view of the Rubiks Cube is is quadrant 5, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_5(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_faces_cw();
      break;
    case GLUT_KEY_LEFT:
      animate_faces_ccw();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_left();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_6
//
// Purpose: if the view of the Rubiks Cube is is quadrant 6, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_6(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_LEFT:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_left();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_7
//
// Purpose: if the view of the Rubiks Cube is is quadrant 7, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_7(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_faces_ccw();
      break;
    case GLUT_KEY_LEFT:
      animate_faces_cw();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_left();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_8
//
// Purpose: if the view of the Rubiks Cube is is quadrant 8, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_8(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_LEFT:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_left();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_9
//
// Purpose: if the view of the Rubiks Cube is is quadrant 9, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_9(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_faces_ccw();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_10
//
// Purpose: if the view of the Rubiks Cube is is quadrant 10, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_10(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_vertical_cubes_up();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_11
//
// Purpose: if the view of the Rubiks Cube is is quadrant 11, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_11(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_faces_cw();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_12
//
// Purpose: if the view of the Rubiks Cube is is quadrant 12, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_12(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_LEFT:
      animate_horizontal_cubes_right();
      break;
    case GLUT_KEY_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_vertical_cubes_down();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_13
//
// Purpose: if the view of the Rubiks Cube is is quadrant 13, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_13(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_faces_ccw();
      break;
    case GLUT_KEY_LEFT:
      animate_faces_cw();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_right();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_14
//
// Purpose: if the view of the Rubiks Cube is is quadrant 14, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_14(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_LEFT:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_UP:
      animate_faces_cw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_ccw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_right();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_15
//
// Purpose: if the view of the Rubiks Cube is is quadrant 15, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_15(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_faces_cw();
      break;
    case GLUT_KEY_LEFT:
      animate_faces_ccw();
      break;
    case GLUT_KEY_UP:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_DOWN:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_right();
      break;
  }
}

//***********************************************************************
//
// Function: quadrant_16
//
// Purpose: if the view of the Rubiks Cube is is quadrant 16, correctly
//    allow proper selection of moves to make when pressing up,down,left,right,
//    page up, and page down while in this view of the cube.
//
// Calls: Rubiks_Cube::animate_horizontal_cubes_left
//        Rubiks_Cube::animate_horizontal_cubes_right
//        Rubiks_Cube::animate_vertical_cubes_up
//        Rubiks_Cube::animate_vertical_cubes_down
//        Rubiks_Cube::animate_faces_ccw
//        Rubiks_Cube::animate_faces_cw
//
//***********************************************************************
void quadrant_16(int key){
  switch (key) {
    case GLUT_KEY_RIGHT:
      animate_vertical_cubes_down();
      break;
    case GLUT_KEY_LEFT:
      animate_vertical_cubes_up();
      break;
    case GLUT_KEY_UP:
      animate_faces_ccw();
      break;
    case GLUT_KEY_DOWN:
      animate_faces_cw();
      break;
    case GLUT_KEY_PAGE_UP:
      animate_horizontal_cubes_left();
      break;
    case GLUT_KEY_PAGE_DOWN:
      animate_horizontal_cubes_right();
      break;
  }
}

//***********************************************************************
//
// Function: if_quadrant_1
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 1.
//	(315<x<45) and (315<y<45)
//
//***********************************************************************
bool if_quadrant_1(int x,int y){
  if((((x>=SEVEN_EIGHTHS_CIRCLE)&&(x<=CIRCLE))||((x>=ZERO)&&(x<=EIGHTH_CIRCLE)))&&
	(((y>=SEVEN_EIGHTHS_CIRCLE)&&(y<=CIRCLE))||((y>=ZERO)&&(y<=EIGHTH_CIRCLE)))){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_2
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 2.
//	(315<x<45) and (45<y<135)
//
//***********************************************************************
bool if_quadrant_2(int x,int y){
  if((((x>=SEVEN_EIGHTHS_CIRCLE)&&(x<=CIRCLE))||((x>=ZERO)&&(x<=EIGHTH_CIRCLE)))&&
	(y>=EIGHTH_CIRCLE)&&(y<=THREE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_3
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 3.
//	(315<x<45) and (135<y<225)
//
//***********************************************************************
bool if_quadrant_3(int x,int y){
  if((((x>=SEVEN_EIGHTHS_CIRCLE)&&(x<=CIRCLE))||((x>=ZERO)&&(x<=EIGHTH_CIRCLE)))
	&&(y>=THREE_EIGHTHS_CIRCLE)&&(y<=FIVE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_4
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 4.
//	(315<x<45) and (225<y<315)
//
//***********************************************************************
bool if_quadrant_4(int x,int y){
  if((((x>=SEVEN_EIGHTHS_CIRCLE)&&(x<=CIRCLE))||((x>=ZERO)&&(x<=EIGHTH_CIRCLE)))&&
	(y>=FIVE_EIGHTHS_CIRCLE)&&(y<=SEVEN_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_5
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 5.
//	(45<x<135) and (315<y<45)
//
//***********************************************************************
bool if_quadrant_5(int x,int y){
  if((x>=EIGHTH_CIRCLE)&&(x<=THREE_EIGHTHS_CIRCLE)&&(((y>=SEVEN_EIGHTHS_CIRCLE)&&(y<=CIRCLE))||
	((y>=ZERO)&&(y<=EIGHTH_CIRCLE)))){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_6
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 6.
//	(45<x<135) and (45<y<135)
//
//***********************************************************************
bool if_quadrant_6(int x,int y){
  if((x>=EIGHTH_CIRCLE)&&(x<=THREE_EIGHTHS_CIRCLE)&&(y>=EIGHTH_CIRCLE)&&(y<=THREE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_7
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 7.
//	(45<x<135) and (135<y<225)
//
//***********************************************************************
bool if_quadrant_7(int x,int y){
  if((x>=EIGHTH_CIRCLE)&&(x<=THREE_EIGHTHS_CIRCLE)&&(y>=THREE_EIGHTHS_CIRCLE)&&(y<=FIVE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_8
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 8.
//	(45<x<135) and (225<y<315)
//
//***********************************************************************
bool if_quadrant_8(int x,int y){
  if((x>=EIGHTH_CIRCLE)&&(x<=THREE_EIGHTHS_CIRCLE)&&(y>=FIVE_EIGHTHS_CIRCLE)&&(y<=SEVEN_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_9
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 9.
//	(135<x<225) and (315<y<45)
//
//***********************************************************************
bool if_quadrant_9(int x,int y){
  if((x>=THREE_EIGHTHS_CIRCLE)&&(x<=FIVE_EIGHTHS_CIRCLE)&&(((y>=SEVEN_EIGHTHS_CIRCLE)&&(y<=CIRCLE))||
	((y>=ZERO)&&(y<=EIGHTH_CIRCLE)))){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_10
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 10.
//	(135<x<225) and (45<y<135)
//
//***********************************************************************
bool if_quadrant_10(int x,int y){
  if((x>=THREE_EIGHTHS_CIRCLE)&&(x<=FIVE_EIGHTHS_CIRCLE)&&(y>=EIGHTH_CIRCLE)&&(y<=THREE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_11
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant11.
//	(135<x<225) and (135<y<225)
//
//***********************************************************************
bool if_quadrant_11(int x,int y){
  if((x>=THREE_EIGHTHS_CIRCLE)&&(x<=FIVE_EIGHTHS_CIRCLE)&&(y>=THREE_EIGHTHS_CIRCLE)&&(y<=FIVE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_12
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 9.
//	(135<x<225) and (225<y<315)
//
//***********************************************************************
bool if_quadrant_12(int x,int y){
  if((x>=THREE_EIGHTHS_CIRCLE)&&(x<=FIVE_EIGHTHS_CIRCLE)&&(y>=FIVE_EIGHTHS_CIRCLE)&&(y<=SEVEN_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_13
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 13.
//	(225<x<315) and (315<y<45)
//
//***********************************************************************
bool if_quadrant_13(int x,int y){
  if((x>=FIVE_EIGHTHS_CIRCLE)&&(x<=SEVEN_EIGHTHS_CIRCLE)&&(((y>=SEVEN_EIGHTHS_CIRCLE)&&(y<=CIRCLE))||
	((y>=ZERO)&&(y<=EIGHTH_CIRCLE)))){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_14
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 14.
//	(225<x<315) and (45<y<135)
//
//***********************************************************************
bool if_quadrant_14(int x,int y){
  if((x>=FIVE_EIGHTHS_CIRCLE)&&(x<=SEVEN_EIGHTHS_CIRCLE)&&(y>=EIGHTH_CIRCLE)&&(y<=THREE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_15
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 15.
//	(225<x<315) and (135<y<225)
//
//***********************************************************************
bool if_quadrant_15(int x,int y){
  if((x>=FIVE_EIGHTHS_CIRCLE)&&(x<=SEVEN_EIGHTHS_CIRCLE)&&(y>=THREE_EIGHTHS_CIRCLE)&&(y<=FIVE_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: if_quadrant_16
//
// Purpose: decide if the view of the Rubik's Cube is in quadrant 16.
//	(225<x<315) and (225<y<315)
//
//***********************************************************************
bool if_quadrant_16(int x,int y){
  if((x>=FIVE_EIGHTHS_CIRCLE)&&(x<=SEVEN_EIGHTHS_CIRCLE)&&(y>=FIVE_EIGHTHS_CIRCLE)&&(y<=SEVEN_EIGHTHS_CIRCLE)){
    return true;
  }else{
    return false;
  }
}

//***********************************************************************
//
// Function: my_special_key_func
//
// Purpose: Process keyboard input to allow the user to increase/decrease
//    the move animation speed, or make a move on the Rubik's Cube
//
// Paramaters: int key - the key that was pressed.
//             int x - the x coordinate of where the mouse is on the screen?
//             int y - the y coordinate of where the mouse is on the screen?
//
// Calls: Rubiks_Cube::increase_speed
//        Rubiks_Cube::decrease_speed
//        Rubiks_Cube::get_x_rotation
//        Rubiks_Cube::get_y_rotation
//        Rubiks_Cube::if_quadrant_(1 through 16)
//        Rubiks_Cube::quadrant_(1 through 16)
//
//***********************************************************************
void my_special_key_func( int Key, int x, int y )
{
  if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(Key==GLUT_KEY_UP)){
    rc.increase_speed();
    nearest=NOTHING;
  }
  if((glutGetModifiers()==GLUT_ACTIVE_SHIFT)&&(Key==GLUT_KEY_DOWN)){
    rc.decrease_speed();
    nearest=NOTHING;
  }
  if(rc.get_in_progress()==false){
    if(if_quadrant_1(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_1(Key);
    }else if(if_quadrant_2(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_2(Key);
    }else if(if_quadrant_3(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_3(Key);
    }else if(if_quadrant_4(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_4(Key);
    }else if(if_quadrant_5(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_5(Key);
    }else if(if_quadrant_6(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_6(Key);
    }else if(if_quadrant_7(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_7(Key);
    }else if(if_quadrant_8(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_8(Key);
    }else if(if_quadrant_9(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_9(Key);
    }else if(if_quadrant_10(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_10(Key);
    }else if(if_quadrant_11(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_11(Key);
    }else if(if_quadrant_12(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_12(Key);
    }else if(if_quadrant_13(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_13(Key);
    }else if(if_quadrant_14(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_14(Key);
    }else if(if_quadrant_15(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_15(Key);
    }else if(if_quadrant_16(rc.get_x_rotation(),rc.get_y_rotation())){
      quadrant_16(Key);
    }
  }
}

//***********************************************************************
//
// Function: make_move
//
// Purpose: actually change the orientation of the cubes involved in a move.
//
// Calls: Rubiks_Cube::(moves)
//
//***********************************************************************
void make_move(){
  if(choice==MOVE_TMR){
    rc.top_move_right();
  }else if(choice==MOVE_MHMR){
    rc.middle_horizontal_move_right();
  }else if(choice==MOVE_BMR){
    rc.bottom_move_right();
  }else if(choice==MOVE_LMU){
    rc.left_move_up();
  }else if(choice==MOVE_MVMU){
    rc.middle_vertical_move_up();
  }else if(choice==MOVE_RMU){
    rc.right_move_up();
  }else if(choice==MOVE_TML){
    rc.top_move_left();
  }else if(choice==MOVE_MHML){
    rc.middle_horizontal_move_left();
  }else if(choice==MOVE_BML){
    rc.bottom_move_left();
  }else if(choice==MOVE_LMD){
    rc.left_move_down();
  }else if(choice==MOVE_MVMD){
    rc.middle_vertical_move_down();
  }else if(choice==MOVE_RMD){
    rc.right_move_down();
  }else if(choice==MOVE_FCCW){
    rc.front_face_ccw();
  }else if(choice==MOVE_MCCW){
    rc.middle_face_ccw();
  }else if(choice==MOVE_BCCW){
    rc.back_face_ccw();
  }else if(choice==MOVE_FCW){
    rc.front_face_cw();
  }else if(choice==MOVE_MCW){
    rc.middle_face_cw();
  }else if(choice==MOVE_BCW){
    rc.back_face_cw();
  }
}

//***********************************************************************
//
// Function: display
//
// Purpose: Provides the mechanisms to animate moves and play sounds when
//    necessary. Draws the Rubik's Cube.
//
// Calls: Rubiks_Cube::get_in_progress
//        Rubiks_Cube::increase_move_rotation
//        Rubiks_Cube::decrease_move_rotation
//        Rubiks_Cube::get_move_rotation
//        Rubiks_Cube::reset_move_rotation
//        Rubiks_Cube::mutate_in_progress
//        TLF::reset_axese
//        Rubiks_Cube::get_direction
//        draw_rubiks_cube
//        Rubiks_Cube::scramble_cube
//        Rubiks_Cube::check_win
//
//***********************************************************************
void display(void) 
{
  // Clear the window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset coordinate system
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
	
  // Set the viewing perspective
  gluPerspective(fovy, ratio, VIEW_NEAR, VIEW_FAR);
	
  // Set viewing translation
  glMatrixMode( GL_MODELVIEW );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMateriali(GL_FRONT, GL_SHININESS, shine);

  if(rc.get_in_progress()){
    if(rc.get_direction()==ONE){
      rc.increase_move_rotation();
      if(rc.get_move_rotation()>=FOURTH_CIRCLE){
        rc.reset_move_rotation();
        rc.mutate_in_progress(false);
        make_move();
        for(int i=ZERO;i<POSSIBLE_MOVES;i++){
          cubes[i]->reset_axese();
        }
        play_sound=true;
      }
    }else if(rc.get_direction()==ZERO){
      rc.decrease_move_rotation();
      if(rc.get_move_rotation()<=-FOURTH_CIRCLE){
        rc.reset_move_rotation();
        rc.mutate_in_progress(false);
        make_move();
        for(int i=ZERO;i<POSSIBLE_MOVES;i++){
          cubes[i]->reset_axese();
        }
        play_sound=true;
      }
    }
    for(int i=ZERO;i<POSSIBLE_MOVES;i++){
      cubes[i]->mutate_rotation(rc.get_move_rotation());
    }
  }

  draw_rubiks_cube(GL_RENDER);

  if(rc.check_win()){
    win=true;
  }

  glutSwapBuffers();
  if(play_sound==true){
    if(over_ride_play==false){
      //system("aplay BUILD1.wav");
      //system("aplay arrow_hit.wav");
      system("aplay ARROW.wav");
      //system("aplay AXE.wav");
    }
    play_sound=false;
  }
  if(win==true){
    system("aplay SCHOOL.wav");
    rc.scramble_cube();
    win=false;
  }
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
  win_w=w;
  win_h=h;
  ratio=win_w/win_h;
  glViewport(ZERO, ZERO, win_w, win_h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, ratio, VIEW_NEAR, VIEW_FAR);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

//***********************************************************************
//
// Function: my_init
//
// Purpose: Set up the program. Scrambles the cube or loads it from file.
//    sets up the lighting and sets up the material properties for the 
//    cube. Translates the cube away from the camera. Displays keyboard
//    options to the terminal.
//
// Calls: Rubiks_Cube::scramble_cube
//        load_file
//
//***********************************************************************
void my_init(){
	
  // Set background to black
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  rc.scramble_cube(); 
  
  load_file();

  // Enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
	
  // Enable expensive lighting computations with actual position of
  // light source. 
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  // Set up and enable light zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);

  // Enable color tracking
  glEnable(GL_COLOR_MATERIAL);
  glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	
  // Set material to folow glColor values
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
  // Set specular reflectivity and shine
  glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
  glMaterialfv(GL_FRONT, GL_EMISSION, MaterialEmission);

  glTranslatef( DISPLACEMENT_X, DISPLACEMENT_Y, -DISPLACEMENT_Z );

  cout << "Press 'o' to override sound and play sound upon making moves" << endl;
  cout << "	(The default is to not play sound)" << endl;
  cout << "Press 'c' to zoom out" << endl;
  cout << "Press 'C' to zoom in" << endl;
  cout << "Press 'n' to scramble the cube" << endl;
  cout << "Press 'l' to load a previously saved state of the cube" << endl;
  cout << "Press 's' to save a state of the cube to file" << endl;
  cout << "Press 't' to toggle lighting of the cube on and off" << endl;
  cout << "Press 'm' to toggle metalic look off and on" << endl;
  cout << "Press 'q' to quit" << endl;
  cout << "Click on cubes and press arrow keys or page up/down to" << endl;
  cout << "	make a move" << endl;
  cout << "Click and drag to change the view of the cube" << endl;
}


//***********************************************************************
//
// Function: main
//
// Purpose: Set up and run the program!
//
//***********************************************************************
int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (win_w, win_h);
  glutInitWindowPosition (INIT_WINDOW_POSITION, INIT_WINDOW_POSITION);
  glutCreateWindow("Rubiks Cube"); //initialize the name of the window to be "Rubiks Cube"

  my_init();
  glutReshapeFunc (my_reshape);	// Set function for resizing window
  glutMouseFunc (mouse_press);		// Detect mouse button press
  glutMotionFunc (mouse_move);		// Detect mouse movement with button pressed
  glutKeyboardFunc (my_keyboard_func);	// Set function for key command processing
  glutSpecialFunc (my_special_key_func);	// Set function for special keys (rotation)
  glutDisplayFunc (display);	// Set function for redisplaying
  glutTimerFunc(ZERO,my_timer,ZERO);

  glutMainLoop(); //necessary for proper display

  return(EXIT_SUCCESS);
}
