//*********************************************************************
//
//  File: objects.h
//  Program: final
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the header file to the object class. This explains 
//    the significance and functionality of each class and how they are 
//    derived. Cubes are all derived from the parent cube which is TLF
//    which stands for the top left front cube in the orientation of a 
//    rubiks cube. The only thing different about each cube is the constructor
//    which is necessary for proper placement of faces and positions and to create
//    a properly working rubiks cube. The Rubiks Cube class is also included here.
//
//  Last Updated: 11/16/2011
//
//*********************************************************************

#ifndef OBJECTS_H
#define OBJECTS_H

//#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <GL/glut.h>
using std::ostream;
using std::istream;
using std::endl;
using std::cout;
using std::srand;

#define PLACEMENT 2.1 //placement of cubes away from the origin
#define ZERO 0.0 //zero
#define ONE 1 //one
#define RED 2 //color reference to red in array
#define WHITE 1 //color reference to white in array
#define BLUE 4 //color reference to blue in array
#define YELLOW 5 //color reference to yellow in array
#define GREEN 3 //color reference to green in array
#define ORANGE 6 //color reference to orange in array
#define BLACK 0 //color reference to black in array
#define SCRAMBLE 50 //number of moves to scramble the cube
#define POSSIBLE_MOVES 9 //# of cubes to manipulate during a move animation/move
#define MAX_SPEED 15 //max speed cube animations will appear
#define MIN_SPEED 5 //min speed cube animations will appear
#define TOTAL_MOVES 18 //total amount of possible moves used to manipulate the cube

/*enumerate all the moves for readability*/
enum Moves {MOVE_TMR=0,MOVE_MHMR,MOVE_BMR,MOVE_LMU,MOVE_MVMU,MOVE_RMU,MOVE_TML,MOVE_MHML,
		MOVE_BML,MOVE_LMD,MOVE_MVMD,MOVE_RMD,MOVE_FCCW,MOVE_MCCW,MOVE_BCCW,MOVE_FCW,
		MOVE_MCW,MOVE_BCW};

/*enumerate all the cubes for readability*/
enum Object {ID_TLF=1,ID_TMF,ID_TRF,ID_TLM,ID_TMM,ID_TRM,ID_TLB,ID_TMB,ID_TRB,
	     ID_MLF,ID_MMF,ID_MRF,ID_MLM,ID_MMM,ID_MRM,ID_MLB,ID_MMB,ID_MRB,
	     ID_DLF,ID_DMF,ID_DRF,ID_DLM,ID_DMM,ID_DRM,ID_DLB,ID_DMB,ID_DRB,NOTHING};

class TLF{ //TOP LEFT FRONT CUBE - parent class for other cubes 
  public:
    TLF();
    void polygon(int a, int b, int c , int d, int color); //build a face of a cube
    void build_cube(int b,int f,int u,int d,int l,int r); //build a cube
    void draw(GLenum mode,const int NAME); //draw the cube
    double get_x(); //get position on cube
    double get_y(); //get position on cube
    double get_z(); //get position on cube
    int get_back(); //get color of back face
    int get_front(); //get color of front face
    int get_left(); //get color of left face
    int get_right(); //get color of right face
    int get_top(); //get color of top face
    int get_bottom(); //get color of bottom face
    int get_rotation(); //get the rotation for animation
    int get_x_axis(); //get x axis for animation
    int get_y_axis(); //get y axis for animation
    int get_z_axis(); //get z axis for animation
    void mutate_rotation(int new_rotation); //change rotation
    void mutate_axese(int new_x_axis,int new_y_axis,int new_z_axis); //change all axese
    void reset_axese(); //reset all axese to zero    
    void write_cube(ostream& outs); //write cube data to file
    void load_cube(istream& ins); //load cube data from file
    /*moves to manipulate orientation of cube*/
    void top_move_right(); 
    void top_move_left();
    void middle_horizontal_move_right();
    void middle_horizontal_move_left();
    void bottom_move_right();
    void bottom_move_left();
    void left_move_down();
    void left_move_up();
    void middle_vertical_move_down();
    void middle_vertical_move_up();
    void right_move_down();
    void right_move_up();
    void front_face_cw();
    void front_face_ccw();
    void middle_face_cw();
    void middle_face_ccw();
    void back_face_cw();
    void back_face_ccw();
  protected:
    double x,y,z;
    int back,front,left,right,top,bottom,temp,rotation,x_axis,y_axis,z_axis;
};

class TLM:public TLF{ //TOP LEFT MIDDLE CUBE
  public:
    TLM();
};

class TLB:public TLF{ //TOP LEFT BACK CUBE
  public:
    TLB();
};

class TMF:public TLF{ //TOP MIDDLE FRONT CUBE
  public:
    TMF();
};

class TMM:public TLF{ //TOP MIDDLE MIDDLE CUBE
  public:
    TMM();
};

class TMB:public TLF{ //TOP MIDDLE BACK CUBE
  public:
    TMB();
};

class TRF:public TLF{ //TOP RIGHT FRONT CUBE
  public:
    TRF();
};

class TRM:public TLF{ //TOP RIGHT MIDDLE CUBE
  public:
    TRM();
};

class TRB:public TLF{ //TOP RIGHT BACK CUBE
  public:
    TRB();
};

class MLF:public TLF{ //MIDDLE LEFT FRONT CUBE
  public:
    MLF();
};

class MLM:public TLF{ //MIDDLE LEFT MIDDLE CUBE
  public:
    MLM();
};

class MLB:public TLF{ //MIDDLE LEFT BACK CUBE
  public:
    MLB();
};

class MMF:public TLF{ //MIDDLE MIDDLE FRONT CUBE
  public:
    MMF();
};

class MMM:public TLF{ //CENTER CUBE
  public:
    MMM();
};

class MMB:public TLF{ //MIDDLE MIDDLE BACK CUBE
  public:
    MMB();
};

class MRF:public TLF{ //MIDDLE RIGHT FRONT CUBE
  public:
    MRF();
};

class MRM:public TLF{ //MIDDLE RIGHT MIDDLE CUBE
  public:
    MRM();
};

class MRB:public TLF{ //MIDDLE RIGHT BACK CUBE
  public:
    MRB();
};

class DLF:public TLF{ //BOTTOM LEFT FRONT CUBE
  public:
    DLF();
};

class DLM:public TLF{ //BOTTOM LEFT MIDDLE CUBE
  public:
    DLM();
};

class DLB:public TLF{ //BOTTOM LEFT BACK CUBE
  public:
    DLB();
};

class DMF:public TLF{ //BOTTOM MIDDLE FRONT CUBE
  public:
    DMF();
};

class DMM:public TLF{ //BOTTOM MIDDLE MIDDLE CUBE
  public:
    DMM();
};

class DMB:public TLF{ //BOTTOM MIDDLE BACK CUBE
  public:
    DMB();
};

class DRF:public TLF{ //BOTTOM RIGHT FRONT CUBE
  public:
    DRF();
};

class DRM:public TLF{ //BOTTOM RIGHT MIDDLE CUBE
  public:
    DRM();
};

class DRB:public TLF{ //BOTTOM RIGHT BACK CUBE
  public:
    DRB();
};

class Rubiks_Cube{
  public:
    Rubiks_Cube();
    void draw(GLenum mode); //draw all elements of rubiks cube
    bool check_win(); //check all faces for same color to check if game is won
    bool check_front(); //check front face for all same color
    bool check_back(); //check back face for all same color
    bool check_top(); //check top face for all same color
    bool check_bottom(); //check bottom face for all same color
    bool check_left(); //check left face for all same color
    bool check_right(); //check right face for all same color
    bool get_in_progress(); //get status of in_progress
    int get_move_rotation(); //get animation rotation
    int get_x_rotation(); //get x rotation
    int get_y_rotation(); //get y rotation
    void mutate_x_rotation(int x); //change x rotation view angle
    void mutate_y_rotation(int y); //change y rotation view angle
    int get_x_axis(); //get x axis
    int get_y_axis(); //get y axis
    int get_z_axis(); //get z axis
    int get_direction(); //get the direction of animation
    void increase_speed(); //raise animation speed
    void decrease_speed(); //lower animation speed
    void mutate_direction(int d); //change the direction of the animation
    void mutate_in_progress(bool progress); //change status of move_in_progress
    void increase_move_rotation(); //increase animation rotation
    void decrease_move_rotation(); //decrease animation rotation
    void reset_move_rotation(); //reset animation rotation to zero
    void scramble_cube(); //jumble up the cube for a new game
    void write_to_file(ostream& outs); //write all rubik cube data to file
    void load_from_file(istream& ins); //load all rubik cube data from file
    /*choose the cubes to manipulate*/
    void choose_cubes_top_left_right(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_MH_left_right(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_bottom_left_right(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_left_up_down(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_MV_up_down(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_right_up_down(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_front_cw_ccw(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_MF_cw_ccw(TLF* blocks[POSSIBLE_MOVES]);
    void choose_cubes_back_cw_ccw(TLF* blocks[POSSIBLE_MOVES]);
    /*moves to manipulate orientation of cube*/
    void top_move_right();
    void top_move_left();
    void middle_horizontal_move_right();
    void middle_horizontal_move_left();
    void bottom_move_right();
    void bottom_move_left();
    void left_move_down();
    void left_move_up();
    void middle_vertical_move_down();
    void middle_vertical_move_up();
    void right_move_down();
    void right_move_up();
    void front_face_cw();
    void front_face_ccw();
    void middle_face_cw();
    void middle_face_ccw();
    void back_face_cw();
    void back_face_ccw();
  private:
    int front,back,top,bottom,left,right,move_rotation,x_axis,y_axis,z_axis,
	direction,speed,x_rotation,y_rotation;
    bool in_progress;
    /*pointers to individual cubes*/
    TLF* tlfp;
    TLF* tlmp;
    TLF* tlbp;
    TLF* tmfp;
    TLF* tmmp;
    TLF* tmbp;
    TLF* trfp;
    TLF* trmp;
    TLF* trbp;
    TLF* mlfp;
    TLF* mlmp;
    TLF* mlbp;
    TLF* mmfp;
    TLF* mmmp;
    TLF* mmbp;
    TLF* mrfp;
    TLF* mrmp;
    TLF* mrbp;
    TLF* dlfp;
    TLF* dlmp;
    TLF* dlbp;
    TLF* dmfp;
    TLF* dmmp;
    TLF* dmbp;
    TLF* drfp;
    TLF* drmp;
    TLF* drbp;
    TLF* temp_p;
    /*all of the individual cubes*/
    TLF tlf;
    TLM tlm;
    TLB tlb;
    TMF tmf;
    TMM tmm;
    TMB tmb;
    TRF trf;
    TRM trm;
    TRB trb;
    MLF mlf;
    MLM mlm;
    MLB mlb;
    MMF mmf;
    MMM mmm;
    MMB mmb;
    MRF mrf;
    MRM mrm;
    MRB mrb;
    DLF dlf;
    DLM dlm;
    DLB dlb;
    DMF dmf;
    DMM dmm;
    DMB dmb;
    DRF drf;
    DRM drm;
    DRB drb;
};

#endif
