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

#ifndef TYPES_H
#define TYPES_H

/// \define The global definitions used in most of the classes
#define NAO_MODEL
#define SER_VER_9
#define MAX_HING 22
#define MAX_UNIVERSAL 0

#include <map>
#include <string>

/// \define The global enumerations used in most of the classes
enum Direction {
  BesideLeft, BesideRight
};

enum BONEDID {
  head = 0, rLowerArm = 1, lLowerArm = 2, rFoot = 3, lFoot = 4
};

enum PlayMode {
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

enum Side {
  SIDE_UNKNOWN, SIDE_LEFT, //1
  SIDE_RIGHT, //2
  SIDE_CENTER, //3
  SIDE_OUR, //4
  SIDE_OPP //5
};

enum DOFID {
  //Head
  DOF_HEAD_PAN = 0,
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

enum DOF_MAP {
  hj1 = 0,
  hj2 = 1,
  raj1 = 2,
  raj2 = 3,
  raj3 = 4,
  raj4 = 5,
  laj1 = 6,
  laj2 = 7,
  laj3 = 8,
  laj4 = 9,
  rlj1 = 10,
  rlj2 = 11,
  rlj3 = 12,
  rlj4 = 13,
  rlj5 = 14,
  rlj6 = 15,
  llj1 = 16,
  llj2 = 17,
  llj3 = 18,
  llj4 = 19,
  llj5 = 20,
  llj6 = 21,
};

#endif

