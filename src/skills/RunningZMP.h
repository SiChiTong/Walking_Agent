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

#ifndef RUNNINGZMP_H_
#define RUNNINGZMP_H_

#include <time.h>
#include "../geometry/Point.h"
#include "../geometry/Geometry.h"
#include "../geometry/Bezier.h"
#include "../utils/CommandCreator.h"
#include "../worldModel/WorldModel.h"
#include "InverseKinematics.h"

#define 	RIGHTFOOT 	0
#define 	LEFTFOOT 	1

/// \define The structure contains the foot useful information
/// \param Position The foot position in CoM coordinates
/// \param Support Defines if it is the support foot or swing foot
/// \param Right Defines if it is right foot or left foot
/// \param theta Defines the Yaw of foot related in CoM frame
struct Foot {
  Point Position;
  bool support;
  bool Right;
  double time;
  double theta;
};

/// \define The structure contains the Zero Momentum Point (ZMP) information for creating
/// ZMP trajectory.
/// \param  Contains the ZMP position and the time in the ZMP trajectory
struct ZMP {
  Point Position;
  double time;
};

/// \define The structure contains Center of Mass (CoM) information for creating
/// horizontal CoM trajectory.
/// \param the CoM position in X and Y dimension and its time in the trajectory
struct CoM {
  Point PositionX;
  Point PositionY;
  double time;
};

/// \define The structure contains Center of Mass (CoM) height for creating
/// vertical CoM trajectory.
/// \param the CoM position in Z dimension and its time in the trajectory
struct HeightTrajectory {
  double z;
  double ddz;
};

/// \define The class implements a ZMP based walking approach which has been presented in paper
/// with the title of "Learning to Walk Fast: Optimized Hip Height Movement for Simulated
/// and Real Humanoid Robots".
/// In this approach the stable omnidirectional walking is modeled using inverted pendulum dynamics.
/// To do that, first the ZMP trajectory is designed using the desired foot positions and vertical CoM
/// trajectory is generated using a fourier series. Then, using these two trajectories, the
/// the differential equations of an inverted pendulum model has been solved to generate horzontal
/// CoM trajectory.
/// Finally, the CoM trajectory and foot positions are used to generate an stable walking. Since
/// this approach can generate a walking motion witch has the variable CoM height, it can
/// be used to generate an stable running motion.
class RunningZMP {

public:
  /// \define the input parameters to the walking engine
  /// \param Swing foot trajectory height from the ground (meter)
  double swingHeight;

  /// \param the walk step size in forward direction (meter)
  double stepSizeX;

  /// \param the walk step size in side direction (meter)
  double stepSizeY;

  /// \param the duration of a walk step (seconds)
  double stepTime;

  /// \param the maximum leg extention during walking (seconds)
  double legExtention;

  /// \param the duration of a walk step (seconds)
  double thetaStep;

  /// \param the parameters of the active balance (see the paper)
  double constantInclination;
  double kpXActiveBalance;
  double kpYActiveBalance;
  double increasingDX;

  /// \param The internal walk parameters from the last step of the walk
  double lastStepTime;
  double lastDX;
  double lastDY;
  double lastTheta;

  /// \param The parameters of a fourier series used to generate the CoM height trajectory
  double offset;
  double amplitude;
  double amplitude2;

  /// \param They true if the walk is in its first step
  bool initPos;
  bool initWalk;

  /// \param It is true if the current walk step is finalized
  bool isStepFinished;

  /// \param It is true if the walk is stopped
  bool stop;

  /// \define The constructor of the walk and its internal variables
  RunningZMP();

  /// \define The thomas algorithm to solve the inverted pendulum differential equations
  /// numerically. It also solve the issue of the initial and lasting condition.
  /// (see boundary condition presented in the paper).
  /// param[in] _com0 and _com0y initial horizontal CoM position in beginning of the step
  /// param[in] _com1 and _com1y the last horizontal CoM position with considering the preview time
  /// param[in] _length the size of the CoM trajectory
  void thomasAlgorithm(double com0, double com1, double com0y, double com1y,
      int legth);

  /// \define modeling an stable omnidirectional walking based on the dynamics of
  /// an inverted pendulum model. (see the paper)
  /// \param[in] _zmpInit the initial ZMP position in walking
  /// \param[in] _zmpInit the input ZMP trajectory
  /// \param[in] _lenght the size of the ZMP and CoM trajectories
  /// \param[in] _dt The resolution of the time in the trajecotry
  /// \param[in] _comZ The input vertical trajecotry of the CoM
  CoM* fastDynamicSolverWithSlideWindow(Point zmpInit, ZMP* zmpTrajector,
      int length, double dt, std::vector<HeightTrajectory> comZ);

  /// \define Generate vertical CoM trajectory using a fourier series
  /// \param[in] _size The size of the trajectory
  void createHeightTrajectory(double size);

  /// \define Set the walk engine parameters to generate walking in increasing
  /// and decreasing manner for reducing the role of inertia and have more stable walk
  /// \param[in] _size The size of the trajectory
  void setWalkParameter(double period, double dX, double dY, double theta,
      bool presure = true);

  /// \define Get the CoM position of the walk
  Point getCoM(double time);

  /// \define Set the foot pose and state
  Foot setFoot(Point Position, bool isSupport, bool isRight, double time,
      double theta);

  /// \define Implementation of the foot planner using the input walk parameters
  /// (see the foot planner section of the paper)
  void footGenerator(double stepX, double stepY, double stepTheta,
      int stepNumber, double timeStep, Foot inicialLeftLeg,
      Foot inicialRightLeg);

  /// \define Implementation of the ZMP trajectory generator using the support
  /// foot postion (see the paper)
  ZMP* zmpGenerator(int stepNumber, double dt, double doubleSupportPercent,
      int &size);

  /// \define The interface to call the Inverse Kinematics.
  vector<float> legInvKin(const int foot, const Point targetPos,
      const Point targetOri);

  /// \define Computing the joints angles based on IK.
  void computePose(const Point lFootPos, const Point rFootPos,
      Point orientationRithFoot, Point orientationLeftFoot);

  /// \define Update the joints angles
  void updatePose();

  /// \define Control the joint effector using a PD controller ,
  /// a Servo motor implementation.
  double predictEffector(int joint, double current, double setpoint);

  /// \define Execute the walk engine using all above methods
  void execute();

  /// \define Initializing the walk engine state and parameters
  void init();

  /// \define The distructor of the class
  virtual ~RunningZMP();

private:

  /// \param The internal parameters to be used in the walk engine
  CoM initCom;
  Point transitionError;
  CoM transitionCom;
  Foot transitionLeftFoot;
  Foot transitionRightFoot;
  Foot previousLeftFoot;
  Foot previousRightFoot;
  double dp;
  double dpY;
  int oneStepSize;
  double legSeperation;
  Foot planedLeftFoot[25];
  Foot planedRightFoot[25];
  CoM* planedCoM;
  bool activeBalace;
  int maxPrevIter;
  double cl;
  double initTime;
  double deltaT;
  Foot inicialLeftLeg;
  Foot inicialRightLeg;
  float pose[22];
  float lastAngle[22];
  float lastError[22];
  std::vector<HeightTrajectory> comZTrajecotry;

  /// \param The internal needed objects
  CommandCreator *CC;
  WorldModel *WM;
  Bezier bzqdRotateSwing;
  Bezier bzqdRotateSupport;
  Bezier bzqdSwing;
  InverseKinematics ik;

};

#endif
