#ifndef HINGEJOINT_H
#define HINGEJOINT_H
///=====================================
#include "../etc/CommonHeaders.h"
///=====================================
class HingeJoint{
	private:
		char name[15];
		float axis;
		float rate;
	public:
		HingeJoint();
		~HingeJoint();
		void setName(char[]);
		void setAxis(float);
		void setRate(float);
		char* getName();
		float getAxis();
		float getRate();
};
///=====================================
#endif
///=====================================
