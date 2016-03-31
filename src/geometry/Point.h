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

#include "../etc/CommonHeaders.h"
#include "Geometry.h"

#ifndef POINT_H
#define POINT_H

/// \define this is the point class. This class is developed the needed data structure and
/// operators to work with 2D and 3D point both in polar and Cartesian coordinate.
class Point {

public:

  /// \define The global variables used in data structures
  double x_Ro;
  double y_Phi;
  double z_Yaw;

  /// \define The Constructor of the class
  Point() {
  }

  /// \define The Constructor of the class
  /// \param[in] x, y and z positions, for 2D points z is zero by default
  Point(double _x, double _y, double _z = 0);

  /// \define The Setter for the X parameter
  void setX(double);

  /// \define The Setter for the Y parameter
  void setY(double);

  /// \define The Setter for the Z parameter
  void setZ(double);

  /// \define The Setter for the Roll parameter
  void setRo(double);

  /// \define The Setter for the Pitch parameter
  void setPhi(double);

  /// \define The Setter for the Yaw parameter
  void setYaw(double);

  /// \define The getter for the X parameter
  double getX();

  /// \define The getter for the Y parameter
  double getY();

  /// \define The getter for the Z parameter
  double getZ();

  /// \define The getter for the Roll parameter
  double getRo();

  /// \define The getter for the Pitch parameter
  double getPhi();

  /// \define The getter for the Yaw parameter
  double getYaw();

  /// \define A function for calculating Yaw angle of a Cartesian point
  float getDirection();

  /// \define A function for calculating Euqlidican distance between two Cartesian points
  double getDistanceTo(Point);

  /// \define A function for calculating the magnitude of a point by the Euqlidican distance
  /// of a Cartesian point to origin
  double getMagnitude();

  /// \define A function to rotate a point using the input Yaw angle
  Point rotate(float);

  /// \define the summation operator of a point with another point
  Point operator +(Point);

  /// \define the subtraction of a point with another point
  Point operator -(Point);

  /// \define The devision operator of a point with another point
  Point operator /(double);

  /// \define The multiply operator of a point with another point
  Point operator *(double);

  /// \define The (+=) operator of a point with another point
  Point operator +=(Point);

  /// \define The (-=) operator of a point with another point
  Point operator -=(Point);

  /// \define The (/=) operator of a point with another point
  Point operator /=(double);

  /// \define The (*=) operator of a point with another point
  Point operator *=(double);

  /// \define The boolean operator for the equality between two point
  /// this operator handle the floating issue.
  bool operator ==(Point);

  /// \define The boolean operator for inequality between two point
  /// this operator handle the floating issue.
  bool operator !=(Point);

  /// \define The function for normalizing the point
  Point getNorm();

  /// \define Print in the information contains in the point on the screen
  void printOnScreen();

  /// \define Operator to print the point
  friend ostream &operator <<(ostream&, const Point &);

};

#endif
