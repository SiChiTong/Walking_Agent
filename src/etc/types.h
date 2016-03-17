#ifndef TYPES_H
#define TYPES_H

#define NAO_MODEL

#define SER_VER_9

#define MAX_HING 22
#define MAX_UNIVERSAL 0

#include <map>
#include <string>
//======================================
enum Direction { BesideLeft , BesideRight };
//======================================
enum BONEDID
{
	head=0,
	rLowerArm=1,
	lLowerArm=2,
	rFoot=3,
	lFoot=4
};
//======================================
enum PlayMode
{
    PM_UNKNOWN,
    PM_BEFORE_KICK_OFF,
    PM_PLAY_ON,
    PM_KICKOFF_LEFT,
    PM_KICKOFF_RIGHT,
    PM_GOAL_KICK_LEFT,
    PM_GOAL_KICK_RIGHT,
    PM_KICKIN_LEFT,
    PM_KICKIN_RIGHT,
    PM_FREE_KICK_LEFT,
    PM_FREE_KICK_RIGHT,
    PM_GOAL_LEFT,
    PM_GOAL_RIGHT,
    PM_CORNER_KICK_LEFT,
    PM_CORNER_KICK_RIGHT,
    PM_GAME_OVER
};

//======================================
enum Side{
    SIDE_UNKNOWN,
    SIDE_LEFT, //1
    SIDE_RIGHT,//2
    SIDE_CENTER, //3
    SIDE_OUR,
    SIDE_OPP,
};

//======================================
enum DOFID{
    //Head
    DOF_HEAD_PAN  = 0,
    DOF_HEAD_TILT = 1,
    
    //Right Hand
    DOF_SHOULDER_RX = 2,
    DOF_SHOULDER_RY = 3,
    DOF_SHOULDER_RT = 4,
    DOF_ELBOW_R = 5,
    
    //Left Hand
    DOF_SHOULDER_LX = 6,
    DOF_SHOULDER_LY = 7,
    DOF_SHOULDER_LT = 8,
    DOF_ELBOW_L = 9,

    //Right Leg
    DOF_LEG_RT = 10,            
    DOF_LEG_RX = 12,
    DOF_LEG_RY = 11,
    DOF_KNEE_R = 13,
    DOF_ANKLE_RX = 14,
    DOF_ANKLE_RY = 15,
    
    //Left Leg
    DOF_LEG_LT = 16,
    DOF_LEG_LX = 18,    
    DOF_LEG_LY = 17,
    DOF_KNEE_L = 19,
    DOF_ANKLE_LX = 20,
    DOF_ANKLE_LY = 21,
    
    DOF_COUNT = 22,
};
//======================================
enum DOF_MAP{
  hj1= 0,
  hj2= 1,
  raj1= 2,
  raj2= 3,
  raj3= 4,
  raj4= 5,
  laj1= 6,
  laj2= 7,
  laj3= 8,
  laj4= 9,
  rlj1= 10,
  rlj2= 11,
  rlj3= 12,
  rlj4= 13,
  rlj5= 14,
  rlj6= 15,
  llj1= 16,
  llj2= 17,
  llj3= 18,
  llj4= 19,
  llj5= 20,
  llj6= 21,
};
//======================================
//======================================

#endif

