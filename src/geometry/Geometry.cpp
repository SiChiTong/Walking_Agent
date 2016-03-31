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
#include "Geometry.h"

double Geometry::PI = 3.141592653589793;

///=====================================
float Geometry::convertDegToRad(float _ang) {
  return _ang * PI / 180.0;
}

///=====================================
float Geometry::convertRadToDeg(float _ang) {
  return _ang * 180.0 / PI;
}

///=====================================
Point Geometry::convertPolToCart(Point p) {
  Point pRes;

  p.setY(convertDegToRad(90 - p.getPhi()));
  p.setZ(convertDegToRad(p.getYaw()));

  pRes.setX(p.getRo() * sin(p.getPhi()) * cos(p.getYaw()));
  pRes.setY(p.getRo() * sin(p.getPhi()) * sin(p.getYaw()));
  pRes.setZ(p.getRo() * cos(p.getPhi()));

  return pRes;
}

///=====================================
Point Geometry::convertCartToPol(Point p) {
  Point pRes;

  pRes.setRo(
      sqrt(
          (p.getX() * p.getX()) + (p.getY() * p.getY())
              + (p.getZ() * p.getZ())));
  pRes.setPhi(90 - convertRadToDeg(acos(p.getZ() / pRes.getX())));

  if (p.getX() == 0)
    pRes.setYaw(0);
  else
    pRes.setYaw(convertRadToDeg(atan(p.getY() / p.getX())));

  if (p.getX() < 0 && p.getY() > 0)
    pRes.setYaw(pRes.getZ() + 180);
  else if (p.getX() < 0 && p.getY() < 0)
    pRes.setYaw(pRes.getZ() - 180);

  return pRes;
}

///=====================================
double Geometry::getPI() {
  return PI;
}

///=====================================
double Geometry::normalizeAngle(double _angle) {
  while (_angle > 180.0)
    _angle -= 360.0;
  while (_angle < -180.0)
    _angle += 360.0;
  return _angle;
}

///=====================================
int Geometry::signX(double _x) {
  if (_x > 0) {
    return 1;
  } else if (_x < 0) {
    return -1;
  } else {
    return 0;
  }
}

///=====================================
float Geometry::Cos(float _x) {
  return (cos(convertDegToRad(_x)));
}

///=====================================
float Geometry::Sin(float _x) {
  return (sin(convertDegToRad(_x)));
}

///=====================================
float Geometry::Tan(float _x) {
  return (tan(convertDegToRad(_x)));
}

///=====================================
float Geometry::ATan2(float _x, float _y) {
  if (fabs(_x) < 0.00001 && fabs(_y) < 0.00001)
    return (0.0);

  return (convertRadToDeg(atan2(_x, _y)));
}

///=====================================
Point Geometry::determineMidpoint(Point _a, Point _b) {
  return _a + ((_b - _a) / 2);
}
