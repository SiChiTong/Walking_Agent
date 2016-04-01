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
#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <string>
#include <cstring>
#include "../sexpLibrary/sexp.h"
#include "../sexpLibrary/sexp_ops.h"
#include "../geometry/Point.h"
#include "../worldModel/WorldModel.h"

class MessageParser {
public:
  MessageParser();
  ~MessageParser();
  void parseMessage(const std::string& msg);

private:
  WorldModel *WM;
  void parseSexp(sexp_t* exp);
  Point* parsePoint(sexp_t* ptr);
  Point* parsePolarCoords(sexp_t* exp_p);
  void parseTime(sexp_t* exp);
  void parseGameState(sexp_t* exp);
  void parseGyro(sexp_t* exp);
  void parseFRP(sexp_t* exp);
  void parseHingeJoint(sexp_t *exp);
  void parseVision(sexp_t *exp);
  void parseBall(sexp_t* exp);
  void parseFlag(sexp_t* exp);
  void parseGoal(sexp_t* exp);
};

#endif // MESSAGEPARSER_H
