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

#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <vector>
#include "../geometry/Point.h"
#include "../geometry/HomogMatrix.h"

/// \define Definition of some needed variables and operands
#define PI		3.14159265358979323846f
#define DEGTORAD(A)	((A * PI) / 180.0f)
#define RADTODEG(A)	((A * 180.0f) / PI)

/// \define This class prepares the functionalities to solve the Inverse Kinematics (IK) problem of
/// the Simspark NAO robot (Type_Zero). A geometric approach in solving the inverse kinematics
/// is implemented to calculate the joints angle of feet. The pose of the feet will be given as
/// a homogeneous matrix then feet joints angles are calculated. This class is mainly used
/// by the walk engine.
class InverseKinematics {

public:

  /// \define The constructor of Inverse Kinematics
  InverseKinematics();

  /// \define The main function which calculats the joints angular position for a given
  /// feet pose
  /// \param[in] _position The pose including the position and orientation of the foot
  /// \param[in] _left The boolean represents left or right foot
  /// \param[out] _joints The vector of the calculated joints angles in degrees
  /// \param[out] If the IK problem can be solved and the target feet position is reachable,
  /// returns true,  otherwise returns false.
  bool calcLegJoints(const HomogMatrix& position, vector<float> &joints,
      bool left);

private:

  /// \define The variables present the size of the legs' segments
  float LENGTHBETWEENLEGS;
  float UPPERLEGLENGTH;
  float LOWERLEGLENGTH;

};

#endif
