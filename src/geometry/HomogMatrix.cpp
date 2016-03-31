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

#include "HomogMatrix.h"
#include <iomanip>

//====================================
HomogMatrix::HomogMatrix() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      elem[i][j] = 0;

  for (int i = 0; i < 4; i++)
    elem[i][i] = 1;

}

//====================================
HomogMatrix::HomogMatrix(const RotationMatrix& rot, const Point& trans) {
  elem[0][0] = rot.l0.x_Ro;
  elem[0][1] = rot.l0.y_Phi;
  elem[0][2] = rot.l0.z_Yaw;
  elem[1][0] = rot.l1.x_Ro;
  elem[1][1] = rot.l1.y_Phi;
  elem[1][2] = rot.l1.z_Yaw;
  elem[2][0] = rot.l2.x_Ro;
  elem[2][1] = rot.l2.y_Phi;
  elem[2][2] = rot.l2.z_Yaw;

  elem[0][3] = trans.x_Ro;
  elem[1][3] = trans.y_Phi;
  elem[2][3] = trans.z_Yaw;

  elem[3][0] = elem[3][1] = elem[3][2] = 0;
  elem[3][3] = 1;
}

//====================================
HomogMatrix::HomogMatrix(const Point& trans) {
  elem[0][0] = 1;
  elem[0][1] = 0;
  elem[0][2] = 0;
  elem[1][0] = 0;
  elem[1][1] = 1;
  elem[1][2] = 0;
  elem[2][0] = 0;
  elem[2][1] = 0;
  elem[2][2] = 1;

  elem[0][3] = trans.x_Ro;
  elem[1][3] = trans.y_Phi;
  elem[2][3] = trans.z_Yaw;

  elem[3][0] = elem[3][1] = elem[3][2] = 0;
  elem[3][3] = 1;
}

//====================================
HomogMatrix::HomogMatrix(const RotationMatrix& rot) {
  elem[0][0] = rot.l0.x_Ro;
  elem[0][1] = rot.l0.y_Phi;
  elem[0][2] = rot.l0.z_Yaw;
  elem[1][0] = rot.l1.x_Ro;
  elem[1][1] = rot.l1.y_Phi;
  elem[1][2] = rot.l1.z_Yaw;
  elem[2][0] = rot.l2.x_Ro;
  elem[2][1] = rot.l2.y_Phi;
  elem[2][2] = rot.l2.z_Yaw;

  elem[0][3] = 0;
  elem[1][3] = 0;
  elem[2][3] = 0;

  elem[3][0] = elem[3][1] = elem[3][2] = 0;
  elem[3][3] = 1;
}

//====================================
RotationMatrix HomogMatrix::getRotation() {
  RotationMatrix result;
  result.l0.x_Ro = elem[0][0];
  result.l0.y_Phi = elem[0][1];
  result.l0.z_Yaw = elem[0][2];
  result.l1.x_Ro = elem[1][0];
  result.l1.y_Phi = elem[1][1];
  result.l1.z_Yaw = elem[1][2];
  result.l2.x_Ro = elem[2][0];
  result.l2.y_Phi = elem[2][1];
  result.l2.z_Yaw = elem[2][2];
  return result;
}

//====================================
Point HomogMatrix::getTranslation() {
  return Point(elem[0][3], elem[1][3], elem[2][3]);
}

//====================================
ostream& operator<<(ostream& os, const HomogMatrix& h) {
  os << setiosflags(ios::fixed) << setprecision(3);
  os << h.elem[0][0] << ", " << h.elem[0][1] << ", " << h.elem[0][2] << ", "
      << h.elem[0][3] << endl;
  os << h.elem[1][0] << ", " << h.elem[1][1] << ", " << h.elem[1][2] << ", "
      << h.elem[1][3] << endl;
  os << h.elem[2][0] << ", " << h.elem[2][1] << ", " << h.elem[2][2] << ", "
      << h.elem[2][3] << endl;
  os << h.elem[3][0] << ", " << h.elem[3][1] << ", " << h.elem[3][2] << ", "
      << h.elem[3][3];
  return os;
}

//====================================
HomogMatrix HomogMatrix::operator*(const HomogMatrix& other) const {
  HomogMatrix result;

  result.elem[0][0] = elem[0][0] * other.elem[0][0]
      + elem[0][1] * other.elem[1][0] + elem[0][2] * other.elem[2][0]
      + elem[0][3] * other.elem[3][0];
  result.elem[0][1] = elem[0][0] * other.elem[0][1]
      + elem[0][1] * other.elem[1][1] + elem[0][2] * other.elem[2][1]
      + elem[0][3] * other.elem[3][1];
  result.elem[0][2] = elem[0][0] * other.elem[0][2]
      + elem[0][1] * other.elem[1][2] + elem[0][2] * other.elem[2][2]
      + elem[0][3] * other.elem[3][2];
  result.elem[0][3] = elem[0][0] * other.elem[0][3]
      + elem[0][1] * other.elem[1][3] + elem[0][2] * other.elem[2][3]
      + elem[0][3] * other.elem[3][3];

  result.elem[1][0] = elem[1][0] * other.elem[0][0]
      + elem[1][1] * other.elem[1][0] + elem[1][2] * other.elem[2][0]
      + elem[1][3] * other.elem[3][0];
  result.elem[1][1] = elem[1][0] * other.elem[0][1]
      + elem[1][1] * other.elem[1][1] + elem[1][2] * other.elem[2][1]
      + elem[1][3] * other.elem[3][1];
  result.elem[1][2] = elem[1][0] * other.elem[0][2]
      + elem[1][1] * other.elem[1][2] + elem[1][2] * other.elem[2][2]
      + elem[1][3] * other.elem[3][2];
  result.elem[1][3] = elem[1][0] * other.elem[0][3]
      + elem[1][1] * other.elem[1][3] + elem[1][2] * other.elem[2][3]
      + elem[1][3] * other.elem[3][3];

  result.elem[2][0] = elem[2][0] * other.elem[0][0]
      + elem[2][1] * other.elem[1][0] + elem[2][2] * other.elem[2][0]
      + elem[2][3] * other.elem[3][0];
  result.elem[2][1] = elem[2][0] * other.elem[0][1]
      + elem[2][1] * other.elem[1][1] + elem[2][2] * other.elem[2][1]
      + elem[2][3] * other.elem[3][1];
  result.elem[2][2] = elem[2][0] * other.elem[0][2]
      + elem[2][1] * other.elem[1][2] + elem[2][2] * other.elem[2][2]
      + elem[2][3] * other.elem[3][2];
  result.elem[2][3] = elem[2][0] * other.elem[0][3]
      + elem[2][1] * other.elem[1][3] + elem[2][2] * other.elem[2][3]
      + elem[2][3] * other.elem[3][3];

  result.elem[3][0] = elem[3][0] * other.elem[0][0]
      + elem[3][1] * other.elem[1][0] + elem[3][2] * other.elem[2][0]
      + elem[3][3] * other.elem[3][0];
  result.elem[3][1] = elem[3][0] * other.elem[0][1]
      + elem[3][1] * other.elem[1][1] + elem[3][2] * other.elem[2][1]
      + elem[3][3] * other.elem[3][1];
  result.elem[3][2] = elem[3][0] * other.elem[0][2]
      + elem[3][1] * other.elem[1][2] + elem[3][2] * other.elem[2][2]
      + elem[3][3] * other.elem[3][2];
  result.elem[3][3] = elem[3][0] * other.elem[0][3]
      + elem[3][1] * other.elem[1][3] + elem[3][2] * other.elem[2][3]
      + elem[3][3] * other.elem[3][3];

  return result;
}

//====================================
void HomogMatrix::setTranslation(const Point& trans) {
  elem[0][3] = trans.x_Ro;
  elem[1][3] = trans.y_Phi;
  elem[2][3] = trans.z_Yaw;
}

//====================================
void HomogMatrix::translate(const float& x, const float& y, const float& z) {
  elem[0][3] += x;
  elem[1][3] += y;
  elem[2][3] += z;
}

//====================================
void HomogMatrix::translate(const Point& trans) {
  elem[0][3] += trans.x_Ro;
  elem[1][3] += trans.y_Phi;
  elem[2][3] += trans.z_Yaw;
}

//====================================
void HomogMatrix::setRotation(const RotationMatrix& rot) {
  elem[0][0] = rot.l0.x_Ro;
  elem[0][1] = rot.l0.y_Phi;
  elem[0][2] = rot.l0.z_Yaw;
  elem[1][0] = rot.l1.x_Ro;
  elem[1][1] = rot.l1.y_Phi;
  elem[1][2] = rot.l1.z_Yaw;
  elem[2][0] = rot.l2.x_Ro;
  elem[2][1] = rot.l2.y_Phi;
  elem[2][2] = rot.l2.z_Yaw;
}

//====================================
HomogMatrix HomogMatrix::getInverse() {
  HomogMatrix result;

  RotationMatrix rot = RotationMatrix(getRotation());
  Point trans = Point(getTranslation());

  result.setRotation(rot.getInverse());
  result.setTranslation(
      result.getRotation() * Point(-trans.x_Ro, -trans.y_Phi, -trans.z_Yaw));
  return result;
}
