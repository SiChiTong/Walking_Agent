#include "HingeJoint.h"
///===================================
HingeJoint::HingeJoint(){
}
///===================================
HingeJoint::~HingeJoint(){
}
///===================================
void HingeJoint::setName(char strN[15]){
	strcpy (name , strN);
}
///===================================
void HingeJoint::setAxis(float ax){
	axis = ax;
}
///===================================
char* HingeJoint::getName(){
	return name;
}
///===================================
float HingeJoint::getAxis(){
	return axis;
}
///===================================
void HingeJoint::setRate(float ra){
	rate = ra;
}
///===================================
float HingeJoint::getRate(){
	return rate;
}
///===================================
