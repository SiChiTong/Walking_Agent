#include "Bezier.h"

Bezier::Bezier(const Point p0, const Point p1, float duration)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = Point(0.f, 0.f, 0.f);
    this->p3 = Point(0.f, 0.f, 0.f);
    this->duration = duration;
    type = "Linear";
};

Bezier::Bezier(const Point p0, const Point p1, const Point p2, float duration)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = Point(0.f, 0.f, 0.f);
    this->duration = duration;
    type = "Quadratic";
};

Bezier::Bezier(const Point p0, const Point p1, const Point p2, const Point p3, float duration)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->duration = duration;
    type = "Cubic";
};

void Bezier::setDuration(float duration)
{
    this->duration = duration;
}

void Bezier::setLinear(const Point p0, const Point p1, float duration)
{
	this->p0 = p0;
	this->p1 = p1;
	this->duration = duration;
	type = "Linear";
}

void Bezier::setQuadratic(const Point p0, const Point p1, const Point p2, float duration)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->duration = duration;
	type = "Quadratic";
}

void Bezier::setCubic(const Point p0, const Point p1, const Point p2, const Point p3, float duration)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->duration = duration;
	type = "Cubic";
}


float Bezier::getDuration() const
{
    return duration;
}

string Bezier::getType() const
{
    return type;
}



Point Bezier::getLinearPosition(float t) const
{
    t = t/duration;
    if(t>1.f) t=1.f;
    if(t<0.f) t=0.f;
    
    float x= (1-t)*p0.x_Ro + t*p1.x_Ro;
    float y = (1-t)*p0.y_Phi + t*p1.y_Phi;
    float z = (1-t)*p0.z_Teta + t*p1.z_Teta;

    return Point(x,y,z);
}


Point Bezier::getQuadraticPosition(float t) const
{
    t = t/duration;
    if(t>1.f) t=1.f;
    if(t<0.f) t=0.f;

    float x = pow((1-t),2)*p0.x_Ro + 2*(1-t)*t*p1.x_Ro + pow(t,2)*p2.x_Ro;
    float y = pow((1-t),2)*p0.y_Phi + 2*(1-t)*t*p1.y_Phi + pow(t,2)*p2.y_Phi;
    float z = pow((1-t),2)*p0.z_Teta + 2*(1-t)*t*p1.z_Teta + pow(t,2)*p2.z_Teta;

    return Point(x,y,z);
}



Point Bezier::getCubicPosition(float t) const
{
    t = t/duration;
    if(t>1.f) t=1.f;
    if(t<0.f) t=0.f;
    
    float x = pow((1-t),3)*p0.x_Ro + 3*pow((1-t),2)*t*p1.x_Ro + 3*(1-t)*pow(t,2)*p2.x_Ro + pow(t,3)*p3.x_Ro;
    float y = pow((1-t),3)*p0.y_Phi + 3*pow((1-t),2)*t*p1.y_Phi + 3*(1-t)*pow(t,2)*p2.y_Phi + pow(t,3)*p3.y_Phi;
    float z = pow((1-t),3)*p0.z_Teta + 3*pow((1-t),2)*t*p1.z_Teta + 3*(1-t)*pow(t,2)*p2.z_Teta + pow(t,3)*p3.z_Teta;
    
    return Point(x,y,z);
}









