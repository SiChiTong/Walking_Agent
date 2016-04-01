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
#include "MessageParser.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

MessageParser::MessageParser() {
  WM = WorldModel::getUniqueInstance();
}

MessageParser::~MessageParser() {

}

void MessageParser::parseMessage(const std::string& msg) {
  char linebuf[BUFSIZ + 16000];
  sexp_t *exp;

  stringstream ss;
  ss << "(msg " << msg << ")";

  strcpy(linebuf, ss.str().c_str());
  exp = parse_sexp(linebuf, BUFSIZ + 16000);
  if (exp == NULL)
    return;
  else if (exp->list == NULL)
    return;
  else if (exp->list->next == NULL)
    return;

  sexp_t* ptr = exp->list->next;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST)
      parseSexp(ptr);
    ptr = ptr->next;
  }

  destroy_sexp(exp);
}

void MessageParser::parseSexp(sexp_t *exp) {
  char *v;

  if (exp->ty == SEXP_LIST) {
    if (exp->list->ty == SEXP_VALUE)
      v = exp->list->val;
    else
      return;
  } else
    return;

  if (!strcmp(v, "time")) {
    parseTime(exp);
  } else if (!strcmp(v, "GS")) {
    parseGameState(exp);
  } else if (!strcmp(v, "GYR")) {
    parseGyro(exp);
  } else if (!strcmp(v, "HJ")) {
    parseHingeJoint(exp);
  } else if (!strcmp(v, "FRP")) {
    parseFRP(exp);
  } else if (!strcmp(v, "See")) {
    parseVision(exp);
  }
}

Point* MessageParser::parsePolarCoords(sexp_t* exp_p) {

  // polar coordinates are given as a list
  if (exp_p->ty != SEXP_LIST) {
    cerr
        << "ERROR parsing polar coordinates: s-expression is not a list. Returning (0,0,0). ";
    return new Point(0, 0, 0);
  }
  // the head of that list must be "pol"
  if (strcmp(exp_p->list->val, "pol")) {
    cerr
        << "ERROR parsing polar coordinates: \"pol\" identifier expected. Found "
        << (exp_p->list->val) << ". Returning (0,0,0). ";
    return new Point(0, 0, 0);
  }

  return parsePoint(exp_p->list->next);
}

Point* MessageParser::parsePoint(sexp_t* ptr) {

  float x = 0, y = 0, z = 0;

  x = atof(ptr->val);
  y = atof(ptr->next->val);
  z = atof(ptr->next->next->val);

  return new Point(x, y, z);
}

void MessageParser::parseTime(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  float time = 0.0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "now"))
        time = atof(ptr->list->next->val);
    }
    ptr = ptr->next;
  }

  WM->setTime(time);
}

void MessageParser::parseGameState(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "t")) {
        float t = atof(ptr->list->next->val);
        WM->setGSTime(t);
      }

      if (!strcmp(ptr->list->val, "pm")) {
        string pm = ptr->list->next->val;
        WM->setPlayMode(pm);
      }

      if (!strcmp(ptr->list->val, "unum")) {
        int unum = atoi(ptr->list->next->val);
        WM->setMyNum(unum);
      }

      if (!strcmp(ptr->list->val, "team")) {
        string team = ptr->list->next->val;
        WM->setTeamName(team);
      }
    }
    ptr = ptr->next;
  }
}

void MessageParser::parseGoal(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  string name = exp->list->val;
  float x = 0, y = 0, z = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "pol")) {
        x = atof(ptr->list->next->val);
        y = atof(ptr->list->next->next->val);
        z = atof(ptr->list->next->next->next->val);
      }
    }
    ptr = ptr->next;
  }

  Point(x, y, z);
}

void MessageParser::parseFlag(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  string name = exp->list->val;
  float x = 0, y = 0, z = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "pol")) {
        x = atof(ptr->list->next->val);
        y = atof(ptr->list->next->next->val);
        z = atof(ptr->list->next->next->next->val);
      }
    }
    ptr = ptr->next;
  }
  Point(x, y, z);
}

void MessageParser::parseBall(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  float x = 0, y = 0, z = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "pol")) {
        x = atof(ptr->list->next->val);
        y = atof(ptr->list->next->next->val);
        z = atof(ptr->list->next->next->next->val);
      }
    }
    ptr = ptr->next;
  }

  Ball ball;
  ball.setPolarPos(Point(x, y, z));
  WM->setBall(ball);
}

void MessageParser::parseVision(sexp_t *exp) {

  sexp_t* ptr = exp->list->next;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST && ptr->list->val != NULL) {
      if (!strcmp(ptr->list->val, "G1L"))
        parseGoal(ptr);
      if (!strcmp(ptr->list->val, "G2L"))
        parseGoal(ptr);
      if (!strcmp(ptr->list->val, "G1R"))
        parseGoal(ptr);
      if (!strcmp(ptr->list->val, "G2R"))
        parseGoal(ptr);

      if (!strcmp(ptr->list->val, "F1L"))
        parseFlag(ptr);
      if (!strcmp(ptr->list->val, "F2L"))
        parseFlag(ptr);
      if (!strcmp(ptr->list->val, "F1R"))
        parseFlag(ptr);
      if (!strcmp(ptr->list->val, "F2R"))
        parseFlag(ptr);

      if (!strcmp(ptr->list->val, "B"))
        parseBall(ptr);
    }
    ptr = ptr->next;
  }
}

void MessageParser::parseHingeJoint(sexp_t *exp) {
  sexp_t* ptr = exp->list->next;

  string name = "";
  float angle = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "n"))
        name = ptr->list->next->val;

      if (!strcmp(ptr->list->val, "ax"))
        angle = atof(ptr->list->next->val);
    }
    ptr = ptr->next;
  }
  HingeJoint hJoint;

  hJoint.setAxis(angle);

  if (name == "hj1") {
    WM->setAHingeJoint(hJoint, 0);
  } else if (name == "hj2") {
    WM->setAHingeJoint(hJoint, 1);
  } else if (name == "raj1") {
    WM->setAHingeJoint(hJoint, 2);
  } else if (name == "raj2") {
    WM->setAHingeJoint(hJoint, 3);
  } else if (name == "raj3") {
    WM->setAHingeJoint(hJoint, 4);
  } else if (name == "raj4") {
    WM->setAHingeJoint(hJoint, 5);
  } else if (name == "laj1") {
    WM->setAHingeJoint(hJoint, 6);
  } else if (name == "laj2") {
    WM->setAHingeJoint(hJoint, 7);
  } else if (name == "laj3") {
    WM->setAHingeJoint(hJoint, 8);
  } else if (name == "laj4") {
    WM->setAHingeJoint(hJoint, 9);
  } else if (name == "rlj1") {
    WM->setAHingeJoint(hJoint, 10);
  } else if (name == "rlj2") {
    WM->setAHingeJoint(hJoint, 11);
  } else if (name == "rlj3") {
    WM->setAHingeJoint(hJoint, 12);
  } else if (name == "rlj4") {
    WM->setAHingeJoint(hJoint, 13);
  } else if (name == "rlj5") {
    WM->setAHingeJoint(hJoint, 14);
  } else if (name == "rlj6") {
    WM->setAHingeJoint(hJoint, 15);
  } else if (name == "llj1") {
    WM->setAHingeJoint(hJoint, 16);
  } else if (name == "llj2") {
    WM->setAHingeJoint(hJoint, 17);
  } else if (name == "llj3") {
    WM->setAHingeJoint(hJoint, 18);
  } else if (name == "llj4") {
    WM->setAHingeJoint(hJoint, 19);
  } else if (name == "llj5") {
    WM->setAHingeJoint(hJoint, 20);
  } else if (name == "llj6") {
    WM->setAHingeJoint(hJoint, 21);
  }

}

void MessageParser::parseFRP(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  string name = "";
  float cx = 0, cy = 0, cz = 0;
  float fx = 0, fy = 0, fz = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "n"))
        name = ptr->list->next->val;

      if (!strcmp(ptr->list->val, "c")) {
        cx = atof(ptr->list->next->val);
        cy = atof(ptr->list->next->next->val);
        cz = atof(ptr->list->next->next->next->val);
      }

      if (!strcmp(ptr->list->val, "f")) {
        fx = atof(ptr->list->next->val);
        fy = atof(ptr->list->next->next->val);
        fz = atof(ptr->list->next->next->next->val);
      }

    }
    ptr = ptr->next;
  }

  if (name == "lf") {
    WM->setFRPCenterL(Point(cx, cy, cz));
    WM->setFRPForceL(Point(cx, cy, cz));
  } else {
    WM->setFRPCenterR(Point(cx, cy, cz));
    WM->setFRPForceR(Point(fx, fy, fz));
  }

}

void MessageParser::parseGyro(sexp_t* exp) {
  sexp_t* ptr = exp->list->next;

  string name = "";
  float rx = 0, ry = 0, rz = 0;

  while (ptr != NULL) {
    if (ptr->ty == SEXP_LIST) {
      if (!strcmp(ptr->list->val, "n"))
        name = ptr->list->next->val;

      if (!strcmp(ptr->list->val, "rt")) {
        rx = atof(ptr->list->next->val);
        ry = atof(ptr->list->next->next->val);
        rz = atof(ptr->list->next->next->next->val);
      }
    }
    ptr = ptr->next;
  }

  Gyro gyro;
  gyro.setRate(Point(rx, ry, rz));
  WM->setGyro(gyro);
}
