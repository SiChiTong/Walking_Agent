#ifndef GEOMETRY_H
#define GEOMETRY_H
///=====================================
#include "Point.h"
#include "../etc/CommonHeaders.h"
///=====================================

class Geometry{
	private:
		static double PI;
	public:
		static Point convertPolToCart(Point);
		static Point convertCartToPol(Point);
    static Point  determineMidpoint(Point a, Point b);
		static float convertDegToRad(float);
		static float convertRadToDeg(float);
		static double getPI();
		static double normalizeAngle( double angle );
		static float Cos(float x);
	  static float Sin(float x);
	  static float Tan( float x );
	  static float ATan2( float x, float y );
		static int signX(double x);
		static double SineF(double time, double A1, double T1, double phi1, double alpha1, double A2, double T2, double phi2, double alpha2);
};
///=====================================
#endif
///=====================================
