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

#include "RunningZMP.h"

RunningZMP::RunningZMP()
{
  CC = CommandCreator::getUniqueInstance();
  WM = WorldModel::getUniqueInstance();
  planedCoM = new CoM[2000];
  init();
}

//===============================================
CoM* RunningZMP::fastDynamicSolverWithSlideWindow(Point comInit,
    ZMP* zmpTrajector, int length, double dt,
    std::vector<HeightTrajectory> comZ) {

  CoM *com = new CoM[length + 1000];
  double a[length + 1000];
  double b[length + 1000];
  double c[length + 1000];
  double d[length + 1000];
  double dy[length + 1000];
  double x[length];
  double y[length];

  // Discretize the inverted pendulum differential equation
  for (int i = 0; i < length; ++i) {
    double g = 9.8;
    double aTemp = (-1 * comZ[i].z) / ((dt * dt) * (comZ[i].ddz + g));
    double bTemp = 1 - (2 * aTemp);

    // Handle the boundary condition for the end of trajectory
    if (i == length - 1)
      bTemp = bTemp + aTemp;

    a[i] = aTemp;
    b[i] = bTemp;
    c[i] = aTemp;
  }

  // Handle the boundary condition for the beginning of trajectory.
  for (int i = 0; i < length; i++) {

    double ZMP_X = zmpTrajector[i].Position.x_Ro;
    double ZMP_Y = zmpTrajector[i].Position.y_Phi;

    if (i == 0) {
      ZMP_X = ZMP_X - (a[0] * comInit.x_Ro);
      ZMP_Y = ZMP_Y - (a[0] * comInit.y_Phi);
    }

    d[i] = ZMP_X;
    dy[i] = ZMP_Y;

  }

  // TDMA solver explanation can be found in wikipedia
  // Here Thomas Algorithm is used to solve Inverted pendulum dynamics
  c[0] = c[0] / b[0];
  d[0] = d[0] / b[0];
  dy[0] = dy[0] / b[0];


  for (int i = 1; i < length - 1; i++) {
    double temp = b[i] - a[i] * c[i - 1];
    c[i] = c[i] / temp;
    d[i] = (d[i] - a[i] * d[i - 1]) / temp;
    dy[i] = (dy[i] - a[i] * dy[i - 1]) / temp;
  }

  d[length - 1] = (d[length - 1] - a[length - 1] * d[length - 2])
      / (b[length - 1] - a[length - 1] * c[length - 2]);
  dy[length - 1] = (dy[length - 1] - a[length - 1] * dy[length - 2])
      / (b[length - 1] - a[length - 1] * c[length - 2]);

  x[length - 1] = d[length - 1];
  y[length - 1] = dy[length - 1];
  for (int i = length - 2; i >= 0; i--) {
    x[i] = d[i] - c[i] * x[i + 1];
    y[i] = dy[i] - c[i] * y[i + 1];
  }

  // After generation of CoM on horizontal plane fill the CoM Container.
  for (int i = 0; i < length; ++i) {
    com[i].PositionX.x_Ro = x[i];
    com[i].PositionY.x_Ro = y[i];
  }

  comZ.clear();

  return com;

}

//=============================================================
void RunningZMP::createHeightTrajectory(double size) {

  comZTrajecotry.clear();
  double period = stepTime;

  // Generate CoM on vertical plane or height trajectory
  for (int i = 0; i < size; i++) {
    HeightTrajectory comZ;
    double t = i * deltaT;

    if (stop || (planedLeftFoot[0].support && planedRightFoot[0].support))
      t = 0;
    comZ.z = offset + amplitude * cos((2 * PI * t / period))
        + amplitude2 * cos((4 * PI * t / period));
    comZ.ddz = amplitude * (-4 * PI * PI / (period * period))
        * cos((2 * PI * t / period))
        + amplitude2 * (-4 * 4 * PI * PI / (period * period))
            * cos((4 * PI * t / period));

    if (stop || (planedLeftFoot[0].support && planedRightFoot[0].support))
      comZ.ddz = 0;
    comZTrajecotry.push_back(comZ);
  }

}

//=============================================================
void RunningZMP::execute() {
  clock_t startTime = clock();

  double timeCurrent = WM->getTime() - initTime;

  isStepFinished = false;

  if (timeCurrent > (stepTime - 0.00005)) {
    transitionLeftFoot = inicialLeftLeg;
    transitionRightFoot = inicialRightLeg;
    transitionError = Point(dp, dpY);
    isStepFinished = true;
  }

  // Initial the walk for beginning of each walk step or walk
  if (timeCurrent > (stepTime - 0.00005) || initWalk) {

    initWalk = false;
    initTime = WM->getTime();
    timeCurrent = WM->getTime() - initTime;

    // This is used when the foot is swing to know the previous position of the the foot
    previousLeftFoot = planedLeftFoot[0];
    previousRightFoot = planedRightFoot[0];

    // plan the next 6 foot with considering the next foot as the initial of the plan
    inicialLeftLeg = planedLeftFoot[1];
    inicialRightLeg = planedRightFoot[1];

    double previewTime = 2.5;
    int previewStep = int(previewTime / stepTime);
    footGenerator(stepSizeX, stepSizeY, 0, previewStep, stepTime,
        inicialLeftLeg, inicialRightLeg);

    int sizeZMP;
    ZMP* zmp = zmpGenerator(previewStep, deltaT, 0, sizeZMP);
    lastTheta = thetaStep;
    oneStepSize = int(stepTime / deltaT);

    createHeightTrajectory(max(sizeZMP, oneStepSize));

    CoM* com = fastDynamicSolverWithSlideWindow(
        Point(initCom.PositionX.x_Ro, initCom.PositionY.x_Ro), zmp, sizeZMP,
        deltaT, comZTrajecotry);

    for (int i = 0; i < oneStepSize; i++) {

      planedCoM[i].PositionY = com[i].PositionY;
      planedCoM[i].PositionX = com[i].PositionX;
      planedCoM[i].PositionY = com[i].PositionY;

    }
    initCom = planedCoM[oneStepSize - 1];

    delete[] zmp;
    delete[] com;
  }

  // After calculating the horizontal CoM from here is the execution of the walk
  Point comPos = getCoM(timeCurrent);

  Point leftFootPos, rightFootPos;

  // if you want to have double support phase, dsp_min and dsp_max should be changes
  float dsp_min = 0;
  float dsp_max = stepTime;

  Point targLeftFPos;
  Point targRightFPos;

  // The active balance, here it is the constant not adaptive, in paper the paper it
  // it is adaptive using the current state of the robot.
  double degRotationTunk = -constantInclination;
  double degRotationTunkY = 0;

  if (planedLeftFoot[0].support && planedRightFoot[0].support) {
    leftFootPos = Point(planedLeftFoot[0].Position.x_Ro,
        planedLeftFoot[0].Position.y_Phi, 0);
    rightFootPos = Point(planedRightFoot[0].Position.x_Ro,
        planedRightFoot[0].Position.y_Phi, 0);
    targLeftFPos = leftFootPos - comPos;
    targRightFPos = rightFootPos - comPos;
    computePose(targLeftFPos, targRightFPos, Point(0, 0, 0), Point(0, 0, 0));
  } else if (planedLeftFoot[0].support) {

    leftFootPos = Point(planedLeftFoot[0].Position.x_Ro,
        planedLeftFoot[0].Position.y_Phi, 0);

    Point p0 = Point(previousRightFoot.Position.x_Ro,
        previousRightFoot.Position.y_Phi, 0);
    Point p2 = Point(planedRightFoot[0].Position.x_Ro,
        planedRightFoot[0].Position.y_Phi, 0);
    Point p1 = Geometry::determineMidpoint(p0, p2);
    p1.z_Yaw = swingHeight;

    if (thetaStep < 0) {
      bzqdRotateSupport.setLinear(Point(-thetaStep, 0, 0), Point(0, 0, 0),
          dsp_max - dsp_min);
      bzqdRotateSwing.setLinear(Point(thetaStep, 0, 0), Point(0, 0, 0),
          dsp_max - dsp_min);
    } else {
      bzqdRotateSupport.setLinear(Point(0, 0, 0), Point(thetaStep, 0, 0),
          dsp_max - dsp_min);
      bzqdRotateSwing.setLinear(Point(0, 0, 0), Point(-thetaStep, 0, 0),
          dsp_max - dsp_min);
    }
    bzqdSwing.setQuadratic(p0, p1, p2, dsp_max - dsp_min);

    targLeftFPos = leftFootPos - comPos;
    targRightFPos = bzqdSwing.getQuadraticPosition(timeCurrent) - comPos;

    Point rotateSwing = bzqdRotateSwing.getLinearPosition(timeCurrent);
    Point rotateSupport = bzqdRotateSupport.getLinearPosition(timeCurrent);

    // rotation around X axis of CoM can be used in Active Balance
    targLeftFPos.x_Ro = targLeftFPos.x_Ro * Geometry::Cos(degRotationTunk)
        + targLeftFPos.z_Yaw * Geometry::Sin(degRotationTunk);
    targLeftFPos.z_Yaw = -targLeftFPos.x_Ro * Geometry::Sin(degRotationTunk)
        + targLeftFPos.z_Yaw * Geometry::Cos(degRotationTunk);
    targRightFPos.x_Ro = targRightFPos.x_Ro * Geometry::Cos(degRotationTunk)
        + targRightFPos.z_Yaw * Geometry::Sin(degRotationTunk);
    targRightFPos.z_Yaw = -targRightFPos.x_Ro * Geometry::Sin(degRotationTunk)
        + targRightFPos.z_Yaw * Geometry::Cos(degRotationTunk);

    // rotation around Y axis of CoM can be used in Active Balance
    targLeftFPos.y_Phi = targLeftFPos.y_Phi * Geometry::Cos(degRotationTunkY)
        - targLeftFPos.z_Yaw * Geometry::Sin(degRotationTunkY);
    targLeftFPos.z_Yaw = targLeftFPos.y_Phi * Geometry::Sin(degRotationTunkY)
        + targLeftFPos.z_Yaw * Geometry::Cos(degRotationTunkY);
    targRightFPos.y_Phi = targRightFPos.y_Phi * Geometry::Cos(degRotationTunkY)
        - targRightFPos.z_Yaw * Geometry::Sin(degRotationTunkY);
    targRightFPos.z_Yaw = targRightFPos.y_Phi * Geometry::Sin(degRotationTunkY)
        + targRightFPos.z_Yaw * Geometry::Cos(degRotationTunkY);

    computePose(targLeftFPos, targRightFPos,
        Point(degRotationTunk, degRotationTunkY, rotateSwing.x_Ro),
        Point(degRotationTunk, degRotationTunkY, rotateSupport.x_Ro));

  }

  else if (planedRightFoot[0].support) {
    rightFootPos = Point(planedRightFoot[0].Position.x_Ro,
        planedRightFoot[0].Position.y_Phi, 0);
    Point p0 = Point(previousLeftFoot.Position.x_Ro,
        previousLeftFoot.Position.y_Phi, 0);
    Point p2 = Point(planedLeftFoot[0].Position.x_Ro,
        planedLeftFoot[0].Position.y_Phi, 0);
    Point p1 = Geometry::determineMidpoint(p0, p2);
    p1.z_Yaw = swingHeight;

    bzqdSwing.setQuadratic(p0, p1, p2, dsp_max - dsp_min);
    if (thetaStep < 0) {
      bzqdRotateSupport.setLinear(Point(0, 0, 0), Point(thetaStep, 0, 0),
          dsp_max - dsp_min);
      bzqdRotateSwing.setLinear(Point(0, 0, 0), Point(-thetaStep, 0, 0),
          dsp_max - dsp_min);
    } else {
      bzqdRotateSupport.setLinear(Point(-thetaStep, 0, 0), Point(0, 0, 0),
          dsp_max - dsp_min);
      bzqdRotateSwing.setLinear(Point(thetaStep, 0, 0), Point(0, 0, 0),
          dsp_max - dsp_min);
    }

    targLeftFPos = bzqdSwing.getQuadraticPosition(timeCurrent) - comPos;
    targRightFPos = rightFootPos - comPos;
    Point rotateSwing = bzqdRotateSwing.getLinearPosition(timeCurrent);
    Point rotateSupport = bzqdRotateSupport.getLinearPosition(timeCurrent);

    // The active balance rotation in sagittal plane
    targLeftFPos.x_Ro = targLeftFPos.x_Ro * Geometry::Cos(degRotationTunk)
        + targLeftFPos.z_Yaw * Geometry::Sin(degRotationTunk);
    targLeftFPos.z_Yaw = -targLeftFPos.x_Ro * Geometry::Sin(degRotationTunk)
        + targLeftFPos.z_Yaw * Geometry::Cos(degRotationTunk);

    targRightFPos.x_Ro = targRightFPos.x_Ro * Geometry::Cos(degRotationTunk)
        + targRightFPos.z_Yaw * Geometry::Sin(degRotationTunk);
    targRightFPos.z_Yaw = -targRightFPos.x_Ro * Geometry::Sin(degRotationTunk)
        + targRightFPos.z_Yaw * Geometry::Cos(degRotationTunk);

    // The active balance rotation in coronal plane
    targLeftFPos.y_Phi = targLeftFPos.y_Phi * Geometry::Cos(degRotationTunkY)
        - targLeftFPos.z_Yaw * Geometry::Sin(degRotationTunkY);
    targLeftFPos.z_Yaw = targLeftFPos.y_Phi * Geometry::Sin(degRotationTunkY)
        + targLeftFPos.z_Yaw * Geometry::Cos(degRotationTunkY);
    targRightFPos.y_Phi = targRightFPos.y_Phi * Geometry::Cos(degRotationTunkY)
        - targRightFPos.z_Yaw * Geometry::Sin(degRotationTunkY);
    targRightFPos.z_Yaw = targRightFPos.y_Phi * Geometry::Sin(degRotationTunkY)
        + targRightFPos.z_Yaw * Geometry::Cos(degRotationTunkY);

    // Call the inverse kinematics
    computePose(targLeftFPos, targRightFPos,
        Point(degRotationTunk, degRotationTunkY, rotateSupport.x_Ro),
        Point(degRotationTunk, degRotationTunkY, rotateSwing.x_Ro));

  }

  updatePose();

  // Update the time
  startTime = clock() - startTime;

  return;

}

//===========================================
void RunningZMP::init() {
  initPos = true;
  offset = 0.195;
  amplitude = -0.02;
  amplitude2 = 0;

  initTime = WM->getTime();
  thetaStep = 0;
  deltaT = 0.002;
  initCom.PositionX = Point(0, 0, 0);
  initCom.PositionY = Point(0, 0, 0);
  legExtention = 0.20;

  swingHeight = 0.06;

  constantInclination = 3.5;
  kpXActiveBalance = 2;
  kpYActiveBalance = 2;
  increasingDX = 0.02;

  legSeperation = 0.11;
  inicialLeftLeg = setFoot(Point(0, legSeperation / 2), true, false, 0, 0);
  inicialRightLeg = setFoot(Point(0, -legSeperation / 2), true, true, 0, 0);

  planedLeftFoot[0] = inicialLeftLeg;
  planedRightFoot[0] = inicialRightLeg;
  planedLeftFoot[1] = inicialLeftLeg;
  planedRightFoot[1] = inicialRightLeg;

  stepTime = 0.8;
  stepSizeX = 0.0;
  stepSizeY = 0.0;
  initWalk = true;
  isStepFinished = false;
  stop = false;

  lastStepTime = 0;
  lastDX = 0;
  lastDY = 0;
  lastTheta = 0;

}

//===========================================
Point RunningZMP::getCoM(double time) {
  int comIter = floor(time / deltaT);
  if (comIter > oneStepSize - 1) {
    cerr << "bug On CoM Iter, CoM Iter is: " << comIter << endl;
  }

  double height = comZTrajecotry[comIter].z;    // hack must be CoM iter
  Point result(planedCoM[comIter].PositionX.x_Ro,
      planedCoM[comIter].PositionY.x_Ro, height);
  return result;
}

//===========================================
Foot RunningZMP::setFoot(Point Position, bool isSupport, bool isRight,
    double time, double theta) {
  Foot foot;
  foot.Position = Position;
  foot.support = isSupport;
  foot.Right = isRight;
  foot.time = time;
  foot.theta = theta;
  return foot;
}

//===========================================
void RunningZMP::setWalkParameter(double period, double dX, double dY,
    double theta, bool presure) {

  double inputDX = lastDX + max(min(dX - lastDX, increasingDX), -increasingDX);
  double inputDY = lastDY + max(min(dY - lastDY, 0.02), -0.02);

  double thetaIncreasingStep = 12;
  double thetaRelationToSpeed = 21;

  if (!presure) {
    thetaIncreasingStep = 7;
    thetaRelationToSpeed = 17;
  }

  double inputTheta = lastTheta
      + max(min(theta - lastTheta, thetaIncreasingStep), -thetaIncreasingStep); //was 13

  double thetaBound = -50 * min(max(fabs(inputDX), fabs(inputDY)), 0.2)
      + thetaRelationToSpeed;    // was 22

  if (inputTheta > 0) {
    inputTheta = min(inputTheta, thetaBound);
  } else {
    inputTheta = max(inputTheta, -1 * thetaBound);
  }

  stepTime = period;
  stepSizeX = inputDX;
  stepSizeY = inputDY;
  thetaStep = inputTheta;
  return;
}

//===========================================
void RunningZMP::footGenerator(double stepX, double stepY, double stepTheta,
    int stepNumber, double timeStep, Foot inicialLeftLeg,
    Foot inicialRightLeg) {

  if (stop) {
    planedLeftFoot[0] = setFoot(inicialLeftLeg.Position, true,
        inicialLeftLeg.Right, inicialLeftLeg.time, inicialLeftLeg.theta);

    planedRightFoot[0] = setFoot(inicialRightLeg.Position, true,
        inicialRightLeg.Right, inicialRightLeg.time, inicialRightLeg.theta);

    for (int i = 1; i <= stepNumber; i++) {
      planedRightFoot[i] = planedRightFoot[0];
      planedLeftFoot[i] = planedLeftFoot[0];
    }
    return;
  }
  planedLeftFoot[0] = setFoot(inicialLeftLeg.Position, inicialLeftLeg.support,
      inicialLeftLeg.Right, inicialLeftLeg.time, inicialLeftLeg.theta);

  planedRightFoot[0] = setFoot(inicialRightLeg.Position,
      inicialRightLeg.support, inicialRightLeg.Right, inicialRightLeg.time,
      inicialRightLeg.theta);

  Point hl(0, legSeperation / 2);
  Point hr(0, -legSeperation / 2);
  Point d(stepX, stepY);
  Point x;

  Point com;
  hl.rotate(planedLeftFoot[0].theta);
  hr.rotate(planedRightFoot[0].theta);
  d.rotate(planedLeftFoot[0].theta);
  if (planedLeftFoot[0].support && planedRightFoot[0].support) {
    x = planedLeftFoot[0].Position - hl;
    planedLeftFoot[0].support = false;
  }
  if (!planedLeftFoot[0].support) {
    x = planedLeftFoot[0].Position - hl;

  }
  if (!planedRightFoot[0].support) {
    x = planedRightFoot[0].Position - hr;
  }

  for (int i = 1; i <= stepNumber; i++) {
    d.rotate(stepTheta);
    com = d + x;
    x = ((com - x) * 2) + x;
    hl.rotate(stepTheta);
    hr.rotate(stepTheta);

    if (planedLeftFoot[i - 1].support) {
      float newTheta = planedLeftFoot[i - 1].theta + stepTheta;
      Point pos = x + hl;
      planedLeftFoot[i] = setFoot(pos, false, planedLeftFoot[i - 1].Right,
          planedLeftFoot[i - 1].time + timeStep, newTheta);
    } else {
      float newTheta = planedLeftFoot[i - 1].theta + stepTheta;
      Point pos = Point(planedLeftFoot[i - 1].Position.x_Ro,
          planedLeftFoot[i - 1].Position.y_Phi);
      planedLeftFoot[i] = setFoot(pos, true, planedLeftFoot[i - 1].Right,
          planedLeftFoot[i - 1].time + timeStep, newTheta);
    }

    if (planedRightFoot[i - 1].support) {
      float newTheta = planedRightFoot[i - 1].theta + stepTheta;
      ;
      Point pos = x + hr;
      planedRightFoot[i] = setFoot(pos, false, planedRightFoot[i - 1].Right,
          planedRightFoot[i - 1].time + timeStep, newTheta);
    } else {
      float newTheta = planedRightFoot[i - 1].theta + stepTheta;
      ;
      Point pos = Point(planedRightFoot[i - 1].Position.x_Ro,
          planedRightFoot[i - 1].Position.y_Phi);
      planedRightFoot[i] = setFoot(pos, true, planedRightFoot[i - 1].Right,
          planedRightFoot[i - 1].time + timeStep, newTheta);
    }

    double minLegSperationY = 0.08;
    double maxLegSeperationX = 0.20;
    double maxLegSeperationY = 0.20;
    if (planedRightFoot[i].support == false) {
      Point leftToRight = planedRightFoot[i].Position
          - planedLeftFoot[i].Position;
      double maxX = max(leftToRight.x_Ro, -maxLegSeperationX);
      leftToRight.x_Ro = min(maxX, maxLegSeperationX);
      double maxY = max(leftToRight.y_Phi, -maxLegSeperationY);
      leftToRight.y_Phi = min(maxY, -minLegSperationY);

      planedRightFoot[i].Position = planedLeftFoot[i].Position + leftToRight;

    }

    if (planedLeftFoot[i].support == false) {
      Point rightToLeft = planedLeftFoot[i].Position
          - planedRightFoot[i].Position;
      double maxX = max(rightToLeft.x_Ro, -maxLegSeperationX);
      rightToLeft.x_Ro = min(maxX, maxLegSeperationX);
      double maxY = max(rightToLeft.y_Phi, minLegSperationY);
      rightToLeft.y_Phi = min(maxY, maxLegSeperationY);

      planedLeftFoot[i].Position = planedRightFoot[i].Position + rightToLeft;

    }

  }

  planedLeftFoot[0] = setFoot(inicialLeftLeg.Position, inicialLeftLeg.support,
      inicialLeftLeg.Right, inicialLeftLeg.time, inicialLeftLeg.theta);

  planedRightFoot[0] = setFoot(inicialRightLeg.Position,
      inicialRightLeg.support, inicialRightLeg.Right, inicialRightLeg.time,
      inicialRightLeg.theta);

  lastStepTime = timeStep;
  lastDX = stepX;
  lastDY = stepY;

  return;

}

//==============================================================
ZMP* RunningZMP::zmpGenerator(int stepNumber, double dt,
    double doubleSupportPercent, int &size) {
  double timeStep = planedRightFoot[1].time - planedRightFoot[0].time;
  int initSize = int((stepNumber + 1) * (timeStep) / dt);
  ZMP *zmp = new ZMP[initSize + 1000];
  size = 0;

  for (int j = 0; j < stepNumber; j++) {
    if (planedRightFoot[j].support && planedLeftFoot[j].support) {
      int sizeStep = int(timeStep / dt);
      for (int i = 0; i < sizeStep; i++) {
        zmp[(j * sizeStep) + i].Position = Point(
            (planedRightFoot[j].Position.x_Ro + planedLeftFoot[j].Position.x_Ro)
                / 2, 0); //(planedRightFoot[j].Position.y_Phi+planedLeftFoot[j].Position.y_Phi)/2);
        zmp[(j * sizeStep) + i].time = (j * timeStep) + (i * dt);
        size++;
      }
    } else if (planedRightFoot[j].support) {
      int sizeStep = int(timeStep / dt);
      for (int i = 0; i < sizeStep; i++) {
        zmp[(j * sizeStep) + i].Position = Point(
            planedRightFoot[j].Position.x_Ro,
            planedRightFoot[j].Position.y_Phi);
        zmp[(j * sizeStep) + i].time = (j * timeStep) + (i * dt);
        size++;
      }

    } else if (planedLeftFoot[j].support) {
      int sizeStep = int(timeStep / dt);
      for (int i = 0; i < sizeStep; i++) {
        zmp[(j * sizeStep) + i].Position = Point(
            planedLeftFoot[j].Position.x_Ro, planedLeftFoot[j].Position.y_Phi);
        zmp[(j * sizeStep) + i].time = (j * timeStep) + (i * dt);
        size++;
      }

    } else {
      int sizeStep = int(timeStep / dt);
      for (int i = 0; i < sizeStep; i++) {
        zmp[(j * sizeStep) + i].Position = Point(
            (planedRightFoot[j].Position.x_Ro + planedLeftFoot[j].Position.x_Ro)
                / 2,
            (planedRightFoot[j].Position.y_Phi
                + planedLeftFoot[j].Position.y_Phi) / 2);
        zmp[(j * sizeStep) + i].time = (j * timeStep) + (i * dt);
      }

    }
  }
  return zmp;
}

//===========================================
void RunningZMP::computePose(const Point lFootPos, const Point rFootPos,
    Point orientationRithFoot, Point orientationLeftFoot) {
  vector<float> jLeftLegDeg, jRightLegDeg;

  jLeftLegDeg.clear();
  jRightLegDeg.clear();

  jLeftLegDeg = legInvKin(LEFTFOOT, lFootPos, orientationLeftFoot);
  jRightLegDeg = legInvKin(RIGHTFOOT, rFootPos, orientationRithFoot);

  pose[DOF_LEG_LT] = jLeftLegDeg[0];
  pose[DOF_LEG_LY] = jLeftLegDeg[1];
  pose[DOF_LEG_LX] = jLeftLegDeg[2];
  pose[DOF_KNEE_L] = jLeftLegDeg[3];
  pose[DOF_ANKLE_LX] = jLeftLegDeg[4];
  pose[DOF_ANKLE_LY] = jLeftLegDeg[5];

  pose[DOF_LEG_RT] = jRightLegDeg[0];
  pose[DOF_LEG_RY] = jRightLegDeg[1];
  pose[DOF_LEG_RX] = jRightLegDeg[2];
  pose[DOF_KNEE_R] = jRightLegDeg[3];
  pose[DOF_ANKLE_RX] = jRightLegDeg[4];
  pose[DOF_ANKLE_RY] = jRightLegDeg[5];

}

//===========================================
vector<float> RunningZMP::legInvKin(const int foot, const Point targetPos,
    const Point targetOri) {
  vector<float> jLegDeg;
  jLegDeg.clear();

  RotationMatrix targetRot, targetRotX, targetRotZ, targetRotY;

  Point targetTrans = targetPos;
  targetRotZ = RotationMatrix(
      Point(Geometry::Cos(targetOri.z_Yaw), -Geometry::Sin(targetOri.z_Yaw),
          0),
      Point(Geometry::Sin(targetOri.z_Yaw), Geometry::Cos(targetOri.z_Yaw),
          0), Point(0, 0, 1));

  targetRotX = RotationMatrix(Point(1, 0, 0),
      Point(0, Geometry::Cos(targetOri.y_Phi), -Geometry::Sin(targetOri.y_Phi)),
      Point(0, Geometry::Sin(targetOri.y_Phi), Geometry::Cos(targetOri.y_Phi)));

  targetRotY = RotationMatrix(
      Point(Geometry::Cos(targetOri.x_Ro), 0, Geometry::Sin(targetOri.x_Ro)),
      Point(0, 1, 0),
      Point(-Geometry::Sin(targetOri.x_Ro), 0, Geometry::Cos(targetOri.x_Ro)));

  targetRot = targetRotY * targetRotX * targetRotZ;

  HomogMatrix target = HomogMatrix(targetRot, targetTrans);

  ik.calcLegJoints(target, jLegDeg, foot);

  if (foot == LEFTFOOT) {
    jLegDeg[1] *= -1;
    jLegDeg[5] *= -1;
  }

  jLegDeg[2] *= -1;
  jLegDeg[3] *= -1;
  jLegDeg[4] *= -1;

  return jLegDeg;
}

//===========================================
void RunningZMP::updatePose() {

  // Control angular Position of Left Leg joints
  float lHipDegT = pose[DOF_LEG_LT];
  float lHipEffT = predictEffector(DOF_LEG_LT,
      WM->getAHingeJoint(DOF_LEG_LT).getAxis(), lHipDegT);
  CC->moveHingJoint(DOF_LEG_LT, lHipEffT);
  float lHipDegX = pose[DOF_LEG_LX];
  float lHipEffX = predictEffector(DOF_LEG_LX,
      WM->getAHingeJoint(DOF_LEG_LX).getAxis(), lHipDegX);
  CC->moveHingJoint(DOF_LEG_LX, lHipEffX);
  float lHipDegY = pose[DOF_LEG_LY];
  float lHipEffY = predictEffector(DOF_LEG_LY,
      WM->getAHingeJoint(DOF_LEG_LY).getAxis(), lHipDegY);
  CC->moveHingJoint(DOF_LEG_LY, lHipEffY);
  float lKneeDeg = pose[DOF_KNEE_L];
  float lKneeEff = predictEffector(DOF_KNEE_L,
      WM->getAHingeJoint(DOF_KNEE_L).getAxis(), lKneeDeg);
  CC->moveHingJoint(DOF_KNEE_L, lKneeEff);
  float lAnkleDegY = pose[DOF_ANKLE_LY];
  float lAnkleEffY = predictEffector(DOF_ANKLE_LY,
      WM->getAHingeJoint(DOF_ANKLE_LY).getAxis(), lAnkleDegY);
  CC->moveHingJoint(DOF_ANKLE_LY, lAnkleEffY);
  float lAnkleDegX = pose[DOF_ANKLE_LX];
  float lAnkleEffX = predictEffector(DOF_ANKLE_LX,
      WM->getAHingeJoint(DOF_ANKLE_LX).getAxis(), lAnkleDegX);
  CC->moveHingJoint(DOF_ANKLE_LX, lAnkleEffX);

  // Control angular Position of Right leg joints
  float rHipDegT = pose[DOF_LEG_RT];
  float rHipEffT = predictEffector(DOF_LEG_RT,
      WM->getAHingeJoint(DOF_LEG_RT).getAxis(), rHipDegT);
  CC->moveHingJoint(DOF_LEG_RT, rHipEffT);
  float rHipDegX = pose[DOF_LEG_RX];
  float rHipEffX = predictEffector(DOF_LEG_RX,
      WM->getAHingeJoint(DOF_LEG_RX).getAxis(), rHipDegX);
  CC->moveHingJoint(DOF_LEG_RX, rHipEffX);
  float rHipDegY = pose[DOF_LEG_RY];
  float rHipEffY = predictEffector(DOF_LEG_RY,
      WM->getAHingeJoint(DOF_LEG_RY).getAxis(), rHipDegY);
  CC->moveHingJoint(DOF_LEG_RY, rHipEffY);
  float rKneeDeg = pose[DOF_KNEE_R];
  float rKneeEff = predictEffector(DOF_KNEE_R,
      WM->getAHingeJoint(DOF_KNEE_R).getAxis(), rKneeDeg);
  CC->moveHingJoint(DOF_KNEE_R, rKneeEff);
  float rAnkleDegY = pose[DOF_ANKLE_RY];
  float rAnkleEffY = predictEffector(DOF_ANKLE_RY,
      WM->getAHingeJoint(DOF_ANKLE_RY).getAxis(), rAnkleDegY);
  CC->moveHingJoint(DOF_ANKLE_RY, rAnkleEffY);
  float rAnkleDegX = pose[DOF_ANKLE_RX];
  float rAnkleEffX = predictEffector(DOF_ANKLE_RX,
      WM->getAHingeJoint(DOF_ANKLE_RX).getAxis(), rAnkleDegX);
  CC->moveHingJoint(DOF_ANKLE_RX, rAnkleEffX);

  // Control angular Position of Left Arm
  float lShoulderDegY = -90;
  float lShoulderEffY = predictEffector(DOF_SHOULDER_LX,
      WM->getAHingeJoint(DOF_SHOULDER_LX).getAxis(), lShoulderDegY);
  CC->moveHingJoint(DOF_SHOULDER_LX, lShoulderEffY);

  float lShoulderDegX = 15;
  float lShoulderEffX = predictEffector(DOF_SHOULDER_LY,
      WM->getAHingeJoint(DOF_SHOULDER_LY).getAxis(), lShoulderDegX);
  CC->moveHingJoint(DOF_SHOULDER_LY, lShoulderEffX);

  float lElbowYaw = predictEffector(DOF_SHOULDER_LT,
      WM->getAHingeJoint(DOF_SHOULDER_LT).getAxis(), -90);
  CC->moveHingJoint(DOF_SHOULDER_LT, lElbowYaw);

  float lElbowPitch = predictEffector(DOF_ELBOW_L,
      WM->getAHingeJoint(DOF_ELBOW_L).getAxis(), -30);
  CC->moveHingJoint(DOF_ELBOW_L, lElbowPitch);

  // Control angular Position of Right Arm
  float rShoulderDegY = -90;
  float rShoulderEffY = predictEffector(DOF_SHOULDER_RX,
      WM->getAHingeJoint(DOF_SHOULDER_RX).getAxis(), rShoulderDegY);
  CC->moveHingJoint(DOF_SHOULDER_RX, rShoulderEffY);

  float rShoulderDegX = -15;
  float rShoulderEffX = predictEffector(DOF_SHOULDER_RY,
      WM->getAHingeJoint(DOF_SHOULDER_RY).getAxis(), rShoulderDegX);
  CC->moveHingJoint(DOF_SHOULDER_RY, rShoulderEffX);

  float rElbowYaw = predictEffector(DOF_SHOULDER_RT,
      WM->getAHingeJoint(DOF_SHOULDER_RT).getAxis(), 90);
  CC->moveHingJoint(DOF_SHOULDER_RT, rElbowYaw);

  float rElbowPitch = predictEffector(DOF_ELBOW_R,
      WM->getAHingeJoint(DOF_ELBOW_R).getAxis(), 30);
  CC->moveHingJoint(DOF_ELBOW_R, rElbowPitch);

}

//===========================================
double RunningZMP::predictEffector(int joint, double current, double setpoint) {

  double err = setpoint - current;

  // Initial the error
  if (lastError[joint] == -1000)
    lastError[joint] = 0;

  // Initial the angle
  if (lastAngle[joint] == -1000)
    lastAngle[joint] = current;

  // P Controller
  double pCoeficient = 0.25;
  double eff = err * pCoeficient;

  // Simulator accepts the Effectors only in these range
  if (eff > 6.1395447)
    eff = 6.1395447;

  if (eff < -6.1395447)
    eff = -6.1395447;

  lastError[joint] = eff;
  lastAngle[joint] = current;
  return eff;
}

//===========================================
RunningZMP::~RunningZMP() {

}

//===========================================
