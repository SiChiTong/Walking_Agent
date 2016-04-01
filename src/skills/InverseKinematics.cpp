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

#include "InverseKinematics.h"

InverseKinematics::InverseKinematics() {

  // The robot leg segments sizes in meter
  LENGTHBETWEENLEGS = 0.11;
  UPPERLEGLENGTH = 0.12;
  LOWERLEGLENGTH = 0.1;
}

///====================================
bool InverseKinematics::calcLegJoints(const HomogMatrix& position,
    vector<float> &joints, bool left) {

  HomogMatrix target(position);

  int sign(left ? -1 : 1);

  // translate to origin of leg
  target.translate(0, (float) LENGTHBETWEENLEGS / 2.f * sign, 0);

  // rotate by 45° around origin for the simspark NAO
  float angOrt = sqrt(2.0f) * 0.5f;
  RotationMatrix rotationX_pi_4 = RotationMatrix(Point(1, 0, 0),
      Point(0, angOrt, angOrt * (-sign)), Point(0, angOrt * sign, angOrt));
  target.setTranslation(rotationX_pi_4 * target.getTranslation());
  target.setRotation(rotationX_pi_4 * target.getRotation());

  // solve the IK problem based on cosine law
  target = target.getInverse();
  float length = (target.getTranslation()).getMagnitude();
  float sqrLength = length * length;
  float upperLeg = UPPERLEGLENGTH;
  float sqrUpperLeg = upperLeg * upperLeg;
  float lowerLeg = LOWERLEGLENGTH;
  float sqrLowerLeg = lowerLeg * lowerLeg;
  float cosLowerLeg = (sqrLowerLeg + sqrLength - sqrUpperLeg)
      / (2 * lowerLeg * length);
  float cosKnee = (sqrUpperLeg + sqrLowerLeg - sqrLength)
      / (2 * upperLeg * lowerLeg);

  bool reachable = true;

  if (!(cosKnee >= -1 && cosKnee <= 1)) {
    if (cosKnee < -1)
      cosKnee = -1;
    if (cosKnee > 1)
      cosKnee = 1;
    if (cosLowerLeg < -1)
      cosLowerLeg = -1;
    if (cosLowerLeg > 1)
      cosLowerLeg = 1;
    reachable = false;
  }

  float angKnee = PI - acos(cosKnee);

  float angFootPitch = -acos(cosLowerLeg);
  angFootPitch -=
      atan2(target.getTranslation().x_Ro,
          Point(0, target.getTranslation().y_Phi, target.getTranslation().z_Yaw).getMagnitude());

  float angFootRoll = atan2(target.getTranslation().y_Phi,
      target.getTranslation().z_Yaw) * sign;
  RotationMatrix hipFromFoot;
  hipFromFoot.rotateX(angFootRoll * -sign);
  hipFromFoot.rotateY(-angFootPitch - angKnee);
  RotationMatrix hip = hipFromFoot.getInverse() * target.getRotation();
  float angHipRoll = asin(-hip.l1.z_Yaw) * -sign;
  angHipRoll -= PI / 4;
  float angHipPitch = -atan2(hip.l0.z_Yaw, hip.l2.z_Yaw);
  float angHipYaw = atan2(hip.l1.x_Ro, hip.l1.y_Phi) * -sign;

  // set computed joints in joints vector
  joints.clear();
  joints.push_back(Geometry::convertRadToDeg(angHipYaw));
  joints.push_back(Geometry::convertRadToDeg(angHipRoll));
  joints.push_back(Geometry::convertRadToDeg(angHipPitch));
  joints.push_back(Geometry::convertRadToDeg(angKnee));
  joints.push_back(Geometry::convertRadToDeg(angFootPitch));
  joints.push_back(Geometry::convertRadToDeg(angFootRoll));

  return reachable;
}
