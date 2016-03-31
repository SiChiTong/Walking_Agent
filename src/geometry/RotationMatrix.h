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
#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include <cmath>
#include <iomanip>
#include "Point.h"

/// \define This class presents the functionalities to use rotation matrix
/// The rotation matrix is mainly used to create homogeneous matrix
class RotationMatrix {

public:

  /// \define The vectors represents each line of the rotation matrix
  Point l0, l1, l2;

  /// \define The constructor of the rotation matrix
  RotationMatrix();

  /// \define The constructor of the rotation matrix based on the given
  /// the three lines of the Matrix
  RotationMatrix(const Point& lin0, const Point& lin1, const Point& lin2);

  /// \define The multiplication operator for multiplying two matrixes
  RotationMatrix operator*(const RotationMatrix& other) const;

  /// \define The multiplication operator for multiplying two vectors
  Point operator*(const Point& vector) const;

  /// \define Calculate the rotation matrix representing the rotation
  /// around X axis
  /// \param[in] _angle degrees
  RotationMatrix& rotateX(const float angle);

  /// \define Calculate the rotation matrix representing the rotation
  /// around Y axis
  /// \param[in] _angle degrees
  RotationMatrix& rotateY(const float angle);

  /// \define Calculate the rotation matrix representing the rotation
  /// around Z axis
  /// \param[in] _angle degrees
  RotationMatrix& rotateZ(const float angle);

  /// \define Calculate the inverse of the rotation matrix
  RotationMatrix getInverse() const;

  /// \define print the rotation matrix on the screen
  friend std::ostream& operator<<(std::ostream& os, const RotationMatrix& r);

private:

  /// \define Calculate the rotation matrix for the rotation around X axis
  RotationMatrix GetRotationMatrixX(const float& angle);

  /// \define Calculate the rotation matrix for the rotation around Y axis
  RotationMatrix GetRotationMatrixY(const float& angle);

  /// \define Calculate the rotation matrix for the rotation around Z axis
  RotationMatrix GetRotationMatrixZ(const float& angle);

};

#endif
