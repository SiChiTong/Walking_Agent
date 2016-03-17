#include "Geometry.h"
///=====================================
double Geometry::PI = 3.141592653589793;
///=====================================
float Geometry::convertDegToRad(float ang){
  return ang * PI / 180.0;
}
///=====================================
float Geometry::convertRadToDeg(float ang){
  return ang * 180.0 / PI;
}
///=====================================
Point Geometry::convertPolToCart(Point p){
  Point pRes;

  p.setY(convertDegToRad(90 - p.getPhi()));
  p.setZ(convertDegToRad(p.getTeta()));

  pRes.setX(p.getRo() * sin(p.getPhi()) * cos(p.getTeta()));
  pRes.setY(p.getRo() * sin(p.getPhi()) * sin(p.getTeta()));
  pRes.setZ(p.getRo() * cos(p.getPhi()));

  return pRes;
}
///=====================================
Point Geometry::convertCartToPol(Point p){
  Point pRes;

  pRes.setRo(sqrt((p.getX()*p.getX()) +(p.getY()*p.getY())+(p.getZ()*p.getZ())));
  pRes.setPhi(90 - convertRadToDeg(acos(p.getZ()/pRes.getX())));

  if (p.getX()==0)
    pRes.setTeta(0);
  else
    pRes.setTeta(convertRadToDeg(atan(p.getY()/p.getX())));

  if ( p.getX()<0 && p.getY()>0)
    pRes.setTeta(pRes.getZ() + 180);
  else if ( p.getX()<0 && p.getY()<0)
    pRes.setTeta(pRes.getZ() - 180);

  return pRes;
}
///=====================================
double Geometry::getPI(){
  return PI;
}
///=====================================
double Geometry::normalizeAngle( double angle ){
  while( angle > 180.0  ) angle -= 360.0;
  while( angle < -180.0 ) angle += 360.0;

  return ( angle );
}
///=====================================
int Geometry::signX( double x ){
  if(x>0){
    return 1;
  }else if(x<0){
    return -1;
  }else{
    return 0;
  }
}
///=====================================
float Geometry::Cos( float x )
{
    return ( cos( convertDegToRad( x ) ) );
}
///=====================================
float Geometry::Sin( float x )
{
    return ( sin( convertDegToRad( x ) ) );
}
///=====================================
float Geometry::Tan( float x )
{
    return ( tan( convertDegToRad( x ) ) );
}
///=====================================
float Geometry::ATan2( float x, float y )
{
    if( fabs( x ) < 0.00001 && fabs( y ) < 0.00001 )
        return ( 0.0 );

    return ( convertRadToDeg( atan2( x, y ) ) );
}
///=====================================
double Geometry::SineF(double time, double A1, double T1, double phi1, double alpha1, double A2, double T2, double phi2, double alpha2)
{

  return A1 * sin(time / T1 * 2 * 3.1415 + phi1) + alpha1 + A2 * sin(time / T2 * 2 * 3.1415 + phi2) + alpha2;
}
///=====================================
Point Geometry::determineMidpoint(Point a, Point b) {
  return a + ((b - a) / 2);
}
///=====================================
