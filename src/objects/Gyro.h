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

#ifndef GYRO_H
#define GYRO_H

#include "../etc/CommonHeaders.h"
#include "../geometry/Point.h"

/// \define This class contains data structures and accessors methods
/// for representing the Gyro object. Gyros has rates and names
class Gyro {

public:

  void setName(char*);

  char* getName();

  void setRate(Point);

  Point getRate();

private:

  char name[10];

  Point rate;

};

#endif
