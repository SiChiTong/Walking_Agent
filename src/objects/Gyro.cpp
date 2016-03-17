#include "Gyro.h"
///=====================================
void Gyro::setName(char *strName){
	strcpy(name,strName);
}
///=====================================
char* Gyro::getName(){
	return name;
}
///=====================================
void Gyro::setRate(Point p){
	rate = p;
}
///=====================================
Point Gyro::getRate(){
	return rate;
}
///=====================================
