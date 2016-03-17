#ifndef BEZIER_H
#define BEZIER_H

#include <string>
#include <cmath>

#include "Point.h"



class Bezier
{
public:
	Bezier(){};
    Bezier(const Point p0, const Point p1, float duration=1.f);
    Bezier(const Point p0, const Point p1, const Point p2, float duration=1.f);
    Bezier(const Point p0, const Point p1, const Point p2, const Point p3, float duration=1.f);
    
    void setDuration(float duration);
    void setLinear(const Point p0, const Point p1, float duration=1.f);
    void setQuadratic(const Point p0, const Point p1, const Point p2, float duration);
    void setCubic(const Point p0, const Point p1, const Point p2, const Point p3, float duration);
    float getDuration() const;
    string getType() const;
    Point getCubicPosition(float t) const;
    Point getQuadraticPosition(float t) const;

    Point getLinearPosition(float t) const;

    
private:
    Point p0, p1, p2, p3;
    string type;
    float duration;

};

#endif // BEZIER_H
