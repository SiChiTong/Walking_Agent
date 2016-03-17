
///===================================
#ifndef COMMANDCREATOR_H
#define COMMANDCREATOR_H
///===================================
#include "../etc/CommonHeaders.h"
#include "../worldModel/WorldModel.h"
#include "../etc/types.h"
///===================================
class CommandCreator{

private:

  static  CommandCreator *uniqueInstance;
  char*   commandString;
  char*   command;
  WorldModel *WM;

public:

  CommandCreator();
  ~CommandCreator();

  static CommandCreator* getUniqueInstance();
  // ============ Nao Commands ==============

  // Heads'command
  void     moveHeadAx1(float);
  void     moveHeadAx2(float);

  // Hands'command
  void     moveLShoulderAx1(float);   // move left hand on axis X (move backward/forward)
  void     moveRShoulderAx1(float);
  void     moveLShoulderAx2(float);   // move left hand on axis Y (side moving)
  void     moveRShoulderAx2(float);
  void     rotateLShoulder(float);
  void     rotateRShoulder(float);
  void     moveLElbow(float);
  void     moveRElbow(float);

  // Legs'command
  void    rotateLLeg(float);
  void    rotateRLeg(float);
  void    moveLLegAx1(float);   // move left leg on axis X (move backward/forward)
  void    moveRLegAx1(float);
  void    moveLLegAx2(float);   // move left leg on axis Y (side moving)
  void    moveRLegAx2(float);
  void    moveLKnee(float);
  void    moveRKnee(float);
  void    moveLAnkleAx1(float);
  void    moveRAnkleAx1(float);
  void    moveLAnkleAx2(float);
  void    moveRAnkleAx2(float);

  void    moveHingJoint(int, float);
  void    stopAllJoints	        (void		  );
  void    reset                  (void             );
  void    beam                   (float,float,float);
  void	  beam			( Point		  );
  void 	  say			(char*		  );
  void    init                   (int,char*        );
  char*   getPreparedCommand     (void	          );
  void    pushCmd		(const char *cmd  );


  string SetLegsAngle(double lleg, double rleg, double lknee, double rknee, double lfoot, double rfoot, double leleg, double releg, double lefoot, double refoot);
  bool SetArmsAngle(double lshoulderx, double rshoulderx, double lshouldery, double rshouldery, double lelbowx, double relbowx);

};
///===================================
#endif
///===================================


