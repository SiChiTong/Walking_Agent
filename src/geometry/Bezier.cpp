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
#include "Bezier.h"

Bezier::Bezier(const Point _p0, const Point _p1, float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->p2 = Point(0.f, 0.f, 0.f);
  this->p3 = Point(0.f, 0.f, 0.f);
  this->duration = _duration;
  type = "Linear";
}
;

///=====================================
Bezier::Bezier(const Point _p0, const Point _p1, const Point _p2,
    float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->p2 = _p2;
  this->p3 = Point(0.f, 0.f, 0.f);
  this->duration = _duration;
  type = "Quadratic";
}


///=====================================
Bezier::Bezier(const Point _p0, const Point _p1, const Point _p2,
    const Point _p3, float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->p2 = _p2;
  this->p3 = _p3;
  this->duration = _duration;
  type = "Cubic";
}


///=====================================
void Bezier::setDuration(float _duration) {
  this->duration = _duration;
}

///=====================================
void Bezier::setLinear(const Point _p0, const Point _p1, float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->duration = _duration;
  type = "Linear";
}

///=====================================
void Bezier::setQuadratic(const Point _p0, const Point _p1, const Point _p2,
    float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->p2 = _p2;
  this->duration = _duration;
  type = "Quadratic";
}

///=====================================
void Bezier::setCubic(const Point _p0, const Point _p1, const Point _p2,
    const Point _p3, float _duration) {
  this->p0 = _p0;
  this->p1 = _p1;
  this->p2 = _p2;
  this->p3 = _p3;
  this->duration = _duration;
  type = "Cubic";
}

///=====================================
float Bezier::getDuration() const {
  return duration;
}

///=====================================
string Bezier::getType() const {
  return type;
}

///=====================================
Point Bezier::getLinearPosition(float _t) const {
  float t = _t / duration;
  if (t > 1.f)
    t = 1.f;
  if (t < 0.f)
    t = 0.f;

  float x = (1 - t) * p0.x_Ro + t * p1.x_Ro;
  float y = (1 - t) * p0.y_Phi + t * p1.y_Phi;
  float z = (1 - t) * p0.z_Yaw + t * p1.z_Yaw;

  return Point(x, y, z);
}

///=====================================
Point Bezier::getQuadraticPosition(float _t) const {
  float t = _t / duration;
  if (t > 1.f)
    t = 1.f;
  if (t < 0.f)
    t = 0.f;

  float x = pow((1 - t), 2) * p0.x_Ro + 2 * (1 - t) * t * p1.x_Ro
      + pow(t, 2) * p2.x_Ro;
  float y = pow((1 - t), 2) * p0.y_Phi + 2 * (1 - t) * t * p1.y_Phi
      + pow(t, 2) * p2.y_Phi;
  float z = pow((1 - t), 2) * p0.z_Yaw + 2 * (1 - t) * t * p1.z_Yaw
      + pow(t, 2) * p2.z_Yaw;

  return Point(x, y, z);
}

///=====================================
Point Bezier::getCubicPosition(float _t) const {
  float t = _t / duration;
  if (t > 1.f)
    t = 1.f;
  if (t < 0.f)
    t = 0.f;

  float x = pow((1 - t), 3) * p0.x_Ro + 3 * pow((1 - t), 2) * t * p1.x_Ro
      + 3 * (1 - t) * pow(t, 2) * p2.x_Ro + pow(t, 3) * p3.x_Ro;
  float y = pow((1 - t), 3) * p0.y_Phi + 3 * pow((1 - t), 2) * t * p1.y_Phi
      + 3 * (1 - t) * pow(t, 2) * p2.y_Phi + pow(t, 3) * p3.y_Phi;
  float z = pow((1 - t), 3) * p0.z_Yaw + 3 * pow((1 - t), 2) * t * p1.z_Yaw
      + 3 * (1 - t) * pow(t, 2) * p2.z_Yaw + pow(t, 3) * p3.z_Yaw;

  return Point(x, y, z);
}
