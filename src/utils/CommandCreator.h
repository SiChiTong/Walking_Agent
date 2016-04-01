/*
 * Copyright (C) 2016 nima@ua.pt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef COMMANDCREATOR_H
#define COMMANDCREATOR_H

#include "../etc/CommonHeaders.h"
#include "../worldModel/WorldModel.h"
#include "../etc/types.h"

/// \define This class creates agents effector messages in the format
/// that can be accepted by RoboCup simulator. The RoboCup simulator
/// Accepts s-expresion messages for the details please check
/// the effector messages section of the Simspark wiki.
class CommandCreator {

public:

  CommandCreator();

  ~CommandCreator();

  static CommandCreator* getUniqueInstance();

  /// \define Heads'command
  void moveHeadAx1(float);
  void moveHeadAx2(float);

  /// \define Hands'command, move left and right hand on axis X (move backward/forward)
  void moveLShoulderAx1(float);
  void moveRShoulderAx1(float);
  void moveLShoulderAx2(float);
  void moveRShoulderAx2(float);
  void rotateLShoulder(float);
  void rotateRShoulder(float);
  void moveLElbow(float);
  void moveRElbow(float);

  /// \define Legs'command
  void rotateLLeg(float);
  void rotateRLeg(float);

  /// \define move left leg on axis X (move backward/forward)
  void moveLLegAx1(float);
  void moveRLegAx1(float);

  /// \define move left leg on axis Y (side moving)
  void moveLLegAx2(float);
  void moveRLegAx2(float);
  void moveLKnee(float);
  void moveRKnee(float);
  void moveLAnkleAx1(float);
  void moveRAnkleAx1(float);
  void moveLAnkleAx2(float);
  void moveRAnkleAx2(float);

  void moveHingJoint(int, float);
  void stopAllJoints(void);
  void reset(void);
  void beam(float, float, float);
  void beam(Point);
  void say(char*);
  void init(int, char*);
  char* getPreparedCommand(void);
  void pushCmd(const char *cmd);

  string SetLegsAngle(double lleg, double rleg, double lknee, double rknee,
      double lfoot, double rfoot, double leleg, double releg, double lefoot,
      double refoot);
  bool SetArmsAngle(double lshoulderx, double rshoulderx, double lshouldery,
      double rshouldery, double lelbowx, double relbowx);

private:

  static CommandCreator *uniqueInstance;
  char* commandString;
  char* command;
  WorldModel *WM;

};
///===================================
#endif
///===================================

