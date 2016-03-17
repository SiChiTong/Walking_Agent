#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H


#include <vector>
#include "../geometry/Point.h"
#include "../geometry/HomogMatrix.h"


#define PI		3.14159265358979323846f
#define DEGTORAD(A)	((A * PI) / 180.0f)
#define RADTODEG(A)	((A * 180.0f) / PI)


class InverseKinematics
{
public:

	float 	LENGTHBETWEENLEGS;
	float 	UPPERLEGLENGTH;
	float 	LOWERLEGLENGTH ;

	InverseKinematics();

    bool calcLegJoints(const HomogMatrix& position, vector<float> &joints, bool left);
};

#endif // INVERSEKINEMATICS_H
