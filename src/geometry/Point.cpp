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
#include "Point.h"

///=====================================
Point::Point(double _x, double _y, double _z) {
  x_Ro = _x;
  y_Phi = _y;
  z_Yaw = _z;
}

///=====================================
void Point::setX(double _x) {
  x_Ro = _x;
}

///=====================================
void Point::setRo(double _roll) {
  x_Ro = _roll;
}

///=====================================
void Point::setPhi(double _phi) {
  y_Phi = _phi;
}

///=====================================
void Point::setYaw(double _theta) {
  z_Yaw = _theta;
}

///=====================================
void Point::setY(double _y) {
  y_Phi = _y;
}

///=====================================
void Point::setZ(double _z) {
  z_Yaw = _z;
}

///=====================================
double Point::getX() {
  return x_Ro;
}

///=====================================
double Point::getRo() {

  return x_Ro;
}

///=====================================
double Point::getPhi() {

  return y_Phi;
}

///=====================================
double Point::getYaw() {
  return z_Yaw;
}

///=====================================
double Point::getY() {
  return y_Phi;
}

///=====================================
double Point::getZ() {
  return z_Yaw;
}

///=====================================
ostream &operator <<(ostream &outPut, const Point &p) {

  outPut << "X= " << p.x_Ro << "\t\tY= " << p.y_Phi << "\t\tZ= " << p.z_Yaw
      << "\t\t";

  return outPut;
}

///=====================================
Point Point::operator +=(Point _p) {

  this->x_Ro = this->x_Ro + _p.x_Ro;
  this->y_Phi = this->y_Phi + _p.y_Phi;
  this->z_Yaw = this->z_Yaw + _p.z_Yaw;

  return (*this);
}

///======================================
Point Point::operator -=(Point _p) {

  this->x_Ro = this->x_Ro - _p.x_Ro;
  this->y_Phi = this->y_Phi - _p.y_Phi;
  this->z_Yaw = this->z_Yaw - _p.z_Yaw;

  return (*this);
}

///======================================
Point Point::operator +(Point _p) {

  Point temp;

  temp.x_Ro = this->x_Ro + _p.x_Ro;
  temp.y_Phi = this->y_Phi + _p.y_Phi;
  temp.z_Yaw = this->z_Yaw + _p.z_Yaw;

  return (temp);
}

///====================================
Point Point::operator -(Point _p) {

  Point temp;

  temp.x_Ro = this->x_Ro - _p.x_Ro;
  temp.y_Phi = this->y_Phi - _p.y_Phi;
  temp.z_Yaw = this->z_Yaw - _p.z_Yaw;

  return (temp);
}

///=====================================
bool Point::operator ==(Point _p) {

  return ((_p.x_Ro - 0.0000000001 < this->x_Ro)
      && (this->x_Ro < _p.x_Ro + 0.0000000001)
      && (_p.y_Phi - 0.0000000001 < this->y_Phi)
      && (this->y_Phi < _p.y_Phi + 0.0000000001)
      && (_p.z_Yaw - 0.0000000001 < this->z_Yaw)
      && (this->z_Yaw < _p.z_Yaw + 0.0000000001));
}

///=====================================
bool Point::operator !=(Point _p) {

  return (!(*this == _p));
}

///=====================================
Point Point::operator /=(double _d) {

  if (_d == 0)
    cerr << "!!!Divided By Zero!!!" << (*this) << endl;

  this->x_Ro = this->x_Ro / _d;
  this->y_Phi = this->y_Phi / _d;
  this->z_Yaw = this->z_Yaw / _d;

  return (*this);
}

///=====================================
Point Point::operator /(double _d) {

  if (_d == 0)
    cerr << "!!!Divided By Zero!!!" << (*this) << endl;

  Point temp;

  temp.x_Ro = this->x_Ro / _d;
  temp.y_Phi = this->y_Phi / _d;
  temp.z_Yaw = this->z_Yaw / _d;

  return (temp);
}

///====================================
Point Point::operator *=(double _d) {

  this->x_Ro = this->x_Ro * _d;
  this->y_Phi = this->y_Phi * _d;
  this->z_Yaw = this->z_Yaw * _d;

  return (*this);
}

///=====================================
Point Point::operator *(double _d) {

  Point temp;

  temp.x_Ro = this->x_Ro * _d;
  temp.y_Phi = this->y_Phi * _d;
  temp.z_Yaw = this->z_Yaw * _d;

  return (temp);
}

///=====================================
double Point::getMagnitude() {

  return (sqrt(
      (this->x_Ro * this->x_Ro) + (this->y_Phi * this->y_Phi)
          + (this->z_Yaw * this->z_Yaw)));
}

///=====================================
double Point::getDistanceTo(Point _p) {

  return ((*this - _p).getMagnitude());
}

///=====================================
Point Point::getNorm() {
  double mag = getMagnitude();
  if (mag < 0.001)
    return Point(0.0, 0.0, 0.0);

  return *this / mag;
}

///=====================================
void Point::printOnScreen() {
  cout << "point: (" << x_Ro << " , " << y_Phi << " , " << z_Yaw << "  )"
      << endl;

}

///=====================================
Point Point::rotate(float _angle) {
  float dMag = this->getMagnitude();
  // add rotation angle to phi
  float dNewDir = this->getDirection() + _angle;
  return Point(dMag * Geometry::Cos(dNewDir), dMag * Geometry::Sin(dNewDir));
}

///=====================================
float Point::getDirection() {
  return (Geometry::ATan2(this->y_Phi, this->x_Ro));
}
