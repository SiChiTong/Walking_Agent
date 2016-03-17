#ifndef GYRO_H
#define GYRO_H
///=====================================
#include "../etc/CommonHeaders.h"
#include "../geometry/Point.h"
///=====================================
class Gyro{
	private:
		char name[10];
		Point rate;
	public:
		void setName (char*);
		char* getName();
		void setRate(Point);
		Point getRate();
};
///=====================================
#endif
///=====================================
