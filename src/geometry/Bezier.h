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
#ifndef BEZIER_H
#define BEZIER_H

#include <string>
#include <cmath>

#include "Point.h"

/// \define This class presents the tools to create different types of Bézier curve
/// (i.e. Linear, Quadratic and Cubic Bézier curves). A Bézier curve is a parametric
/// curve frequently used in robotics to generate position trajectories. See this link for more information:
/// https://en.wikipedia.org/wiki/B%C3%A9zier_curve.

class Bezier {

public:

  /// \define The constructor of the Class
  Bezier() {
  }
  ;

  /// \define The constructor of the Class for creating linear Bézier curve.
  /// Simply the straight line between the given points P0 and P1.
  /// \param[in] _p0 The first point
  /// \param[in] _p1 The second point
  /// \param[in] _duration The duration of the path
  Bezier(const Point _p0, const Point _p1, float _duration = 1.f);

  /// \define The constructor of the Class for creating Quadratic Bézier curve.
  /// Simply the path traced between the given points P0, P1 and P2.
  /// \param[in] _p0 The first point
  /// \param[in] _p1 The second point
  /// \param[in] _p2 The third point
  /// \param[in] _duration The duration of the path
  Bezier(const Point _p0, const Point _p1, const Point _p2, float _duration =
      1.f);

  /// \define The constructor for creating Cubic Bézier curve.
  /// Simply the path traced between the given points P0, P1, P2 and P3.
  /// \param[in] _p0 The first point
  /// \param[in] _p1 The second point
  /// \param[in] _p2 The third point
  /// \param[in] _p2 The forth point
  /// \param[in] _duration The duration of the path
  Bezier(const Point _p0, const Point _p1, const Point _p2, const Point _p3,
      float _duration = 1.f);

  /// \define The setter of the duration of the path.
  void setDuration(float _duration);

  /// \define The setter of the linear Bézier curve.
  void setLinear(const Point _p0, const Point _p1, float _duration = 1.f);

  /// \define The setter of the quadratic Bézier curve.
  void setQuadratic(const Point _p0, const Point _p1, const Point _p2,
      float _duration);

  /// \define The setter of the cubic Bézier curve.
  void setCubic(const Point _p0, const Point _p1, const Point _p2,
      const Point _p3, float _duration);

  /// \define The getter of the path duration.
  float getDuration() const;

  /// \define The getter of the type of the path.
  string getType() const;

  /// \define Calculate the position in the Linear bezier trajectory for the given time.
  /// \define param[in] _t The in input time in the trajectory
  /// \define param[out] The Calculated point position on the Bezier trajectory.
  Point getLinearPosition(float _t) const;

  /// \define Calculate the position in the Cubic bezier trajectory for the given time.
  /// \define param[in] _t The in input time in the trajectory
  /// \define param[out] The Calculated point position on the Bezier trajectory.
  Point getCubicPosition(float _t) const;

  /// \define Calculate the position in the Quadratic bezier trajectory for the given time.
  /// \define param[in] _t The in input time in the trajectory
  /// \define param[out] The Calculated point position on the Bezier trajectory.
  Point getQuadraticPosition(float _t) const;

private:

  /// define The private variables used in the class for constructing a Bezier curve
  Point p0, p1, p2, p3;
  string type;
  float duration;

};

#endif
