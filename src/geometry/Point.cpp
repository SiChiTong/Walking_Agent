#include "Point.h"

///=====================================
Point::Point(double _x, double _y, double _z){
    x_Ro = _x;
    y_Phi = _y;
    z_Teta = _z;
}
///=====================================
void Point::setX(double _x){
    x_Ro = _x;
}
///=====================================
void Point::setRo(double _roll){
    x_Ro = _roll;
}
///=====================================
void Point::setPhi(double _phi){
    y_Phi= _phi;
}
///=====================================
void Point::setTeta(double _theta){
    z_Teta= _theta;
}
///=====================================
void Point::setY(double _y){
    y_Phi = _y;
}
///=====================================
void Point::setZ(double _z){
    z_Teta = _z;
}
///=====================================
double Point::getX(){
    return x_Ro;
}
///=====================================
double Point::getRo (){

    return x_Ro;
}
///=====================================
double Point::getPhi(){

    return y_Phi;
}
///=====================================
double Point::getTeta() {
    return z_Teta;
}
///=====================================
double Point::getY(){
    return y_Phi;
}
///=====================================
double Point::getZ(){
    return z_Teta;
}
///=====================================
ostream &operator << (ostream &outPut,const Point &p){

    outPut <<"X= "<<p.x_Ro<<"\t\tY= "<<p.y_Phi<<"\t\tZ= "<<p.z_Teta<<"\t\t";

    return outPut;
}
///=====================================
Point Point::operator +=(Point _p){

    this->x_Ro    =  this->x_Ro    +  _p.x_Ro  ;
    this->y_Phi   =  this->y_Phi   +  _p.y_Phi ;
    this->z_Teta  =  this->z_Teta  +  _p.z_Teta;

    return (*this);
}
///======================================
Point Point::operator -=(Point _p){

    this->x_Ro    =  this->x_Ro    -  _p.x_Ro  ;
    this->y_Phi   =  this->y_Phi   -  _p.y_Phi ;
    this->z_Teta  =  this->z_Teta  -  _p.z_Teta;

    return (*this);
}
///======================================
Point Point::operator +(Point _p){

    Point temp;

    temp.x_Ro    =  this->x_Ro    +  _p.x_Ro  ;
    temp.y_Phi   =  this->y_Phi   +  _p.y_Phi ;
    temp.z_Teta  =  this->z_Teta  +  _p.z_Teta;

    return (temp);
}
///====================================
Point Point::operator -(Point _p){

    Point temp;

    temp.x_Ro    =  this->x_Ro    -  _p.x_Ro  ;
    temp.y_Phi   =  this->y_Phi   -  _p.y_Phi ;
    temp.z_Teta  =  this->z_Teta  -  _p.z_Teta;

    return (temp);
}
///=====================================
bool Point::operator ==(Point _p){

    return( ( _p.x_Ro - 0.0000000001 < this->x_Ro )  && ( this->x_Ro < _p.x_Ro + 0.0000000001 ) && ( _p.y_Phi - 0.0000000001 < this->y_Phi ) && ( this->y_Phi <  _p.y_Phi + 0.0000000001 ) &&
	    ( _p.z_Teta - 0.0000000001 < this->z_Teta ) && ( this->z_Teta < _p.z_Teta + 0.0000000001 ) );
}
///=====================================
bool Point::operator !=(Point _p){

    return ( ! ( *this == _p ) );
}
///=====================================
Point Point::operator /=(double _d){

    if (_d == 0)
	cerr <<"!!!Divided By Zero!!!"<<(*this)<<endl;

    this->x_Ro    =  this->x_Ro    /  _d;
    this->y_Phi   =  this->y_Phi   /  _d;
    this->z_Teta  =  this->z_Teta  /  _d;

    return (*this);
}
///=====================================
Point Point::operator /(double _d){

    if (_d == 0)
	cerr <<"!!!Divided By Zero!!!"<<(*this)<<endl;

    Point temp;

    temp.x_Ro    =  this->x_Ro    /  _d;
    temp.y_Phi   =  this->y_Phi   /  _d;
    temp.z_Teta  =  this->z_Teta  /  _d;

    return (temp);
}
///====================================
Point Point::operator *=(double _d){

    this->x_Ro    =  this->x_Ro    *  _d;
    this->y_Phi   =  this->y_Phi   *  _d;
    this->z_Teta  =  this->z_Teta  *  _d;

    return (*this);
}
///=====================================
Point Point::operator *(double _d){

    Point temp;

    temp.x_Ro    =  this->x_Ro    *  _d;
    temp.y_Phi   =  this->y_Phi   *  _d;
    temp.z_Teta  =  this->z_Teta  *  _d;

    return (temp);
}
///=====================================
double Point::getMagnitude (){

    return ( sqrt ( ( this->x_Ro * this->x_Ro ) + ( this->y_Phi * this->y_Phi ) + ( this->z_Teta * this->z_Teta ) ) );
}
///=====================================
double Point::getDistanceTo(Point _p){

    return ( ( *this - _p ).getMagnitude());
}
///=====================================
double Point::getDistanceTo2(Point _p){

    return ( sqrt ( ( ( this->x_Ro - _p.x_Ro ) * ( this->x_Ro - _p.x_Ro )   ) + ( ( this->y_Phi - _p.y_Phi ) * ( this->y_Phi - _p.y_Phi ) ) ));
}
///=====================================
Point Point::getNorm(){
    double mag = getMagnitude();
    if(mag < 0.001)
	return Point(0.0, 0.0, 0.0);

    return *this / mag;
}
///=====================================
void Point::printOnScreen(){
	cout<<"point: ("<<x_Ro<<" , "<<y_Phi<<" , "<<z_Teta<<"  )"<<endl;

}
///=====================================
Point Point::rotate( float _angle )
{
    float dMag    = this->getMagnitude();
    float dNewDir = this->getDirection( ) + _angle;  // add rotation angle to phi
    return Point( dMag * Geometry::Cos( dNewDir ), dMag * Geometry::Sin( dNewDir ));
}
///=====================================
float Point::getDirection( )
{
    return ( Geometry::ATan2( this->y_Phi, this->x_Ro ) );
}
