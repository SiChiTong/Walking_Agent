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
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Point.h"
#include "../etc/CommonHeaders.h"

/// \define An static class for performing needed geometric operations.
class Geometry {

public:

  /// \define Calculate the correspondent Cartesian 3D point from a given point in
  /// Spherical coordinate system
  static Point convertPolToCart(Point);

  /// \define Calculate the correspondent point in Spherical coordinate system from
  /// a given point in Cartesian coordinate system
  static Point convertCartToPol(Point);

  /// \define Calculate the point which is in the middle of the line connects
  /// two other points _a and _b
  static Point determineMidpoint(Point _a, Point _b);

  /// \define The Degrees to Radian Conversion
  static float convertDegToRad(float);

  /// \define The Radian to degree Conversion
  static float convertRadToDeg(float);

  /// \define The getter for PI value
  static double getPI();

  /// \define Normalizing an angle to +/-180 degrees
  /// \param[in] _angle degrees
  /// \param[out] The normalized angle
  static double normalizeAngle(double _angle);

  /// \define Cosine of an angle in degrees
  /// \param[in] _x an degree angle
  static float Cos(float _x);

  /// \define Sin of an angle in degrees
  /// \param[in] _x degree angle
  static float Sin(float _x);

  /// \define tangent of an angle in degrees
  /// \param[in] _x degree angle
  static float Tan(float _x);

  /// \define Calculating the arc tangent of y/x, The return value is in degrees
  /// \param[out] arc tangent in degree
  static float ATan2(float _x, float _y);

  /// \define Calculating the arc the sign of _x with considering the floating point issue
  /// \param[out] 1 for positive, -1 for negative, 0 for the 0.
  static int signX(double _x);


private:

  /// \define The Pi number, 3.141592653589793
  static double PI;

};
///=====================================
#endif
///=====================================
