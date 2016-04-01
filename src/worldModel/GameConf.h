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
#ifndef GAMECONF_H
#define GAMECONF_H
///=====================================
#include "WorldModel.h"
#include "../geometry/Point.h"
#include "../geometry/Geometry.h"
#include "../objects/Ball.h"
///=====================================

class GameConf {

private:

  static GameConf *uniqueInstance;

  GameConf();
  ~GameConf();

  WorldModel *WM;
  static string rsgPath;

public:
  static GameConf* getUniqueInstance();
  void init();
  static string getRSGPath();
  static void setRSGPath(string filePath);

};
///=====================================
#endif
///=====================================
