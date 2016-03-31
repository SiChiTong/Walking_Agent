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
#include "HingeJoint.h"

HingeJoint::HingeJoint() {
}

///===================================
HingeJoint::~HingeJoint() {
}

///===================================
void HingeJoint::setName(char strN[15]) {
  strcpy(name, strN);
}

///===================================
void HingeJoint::setAxis(float ax) {
  axis = ax;
}

///===================================
char* HingeJoint::getName() {
  return name;
}

///===================================
float HingeJoint::getAxis() {
  return axis;
}

///===================================
void HingeJoint::setRate(float ra) {
  rate = ra;
}

///===================================
float HingeJoint::getRate() {
  return rate;
}

///===================================
