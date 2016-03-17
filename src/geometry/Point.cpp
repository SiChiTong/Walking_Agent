#include "Point.h"

///=====================================
Point::Point(double x, double y, double z){
    x_Ro = x;
    y_Phi = y;
    z_Teta = z;
}
///=====================================
void Point::setX(double fX){
    x_Ro = fX;
}
///=====================================
void Point::setRo(double fRo){
    x_Ro = fRo;
}
///=====================================
void Point::setPhi(double fPhi){
    y_Phi= fPhi;
}
///=====================================
void Point::setTeta(double fTeta){
    z_Teta= fTeta;
}
///=====================================
void Point::setY(double fY){
    y_Phi = fY;
}
///=====================================
void Point::setZ(double fZ){	
    z_Teta = fZ;
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
Point Point::operator +=(Point p){
    
    this->x_Ro    =  this->x_Ro    +  p.x_Ro  ;
    this->y_Phi   =  this->y_Phi   +  p.y_Phi ;
    this->z_Teta  =  this->z_Teta  +  p.z_Teta;
    
    return (*this);
}
///======================================
Point Point::operator -=(Point p){
    
    this->x_Ro    =  this->x_Ro    -  p.x_Ro  ;
    this->y_Phi   =  this->y_Phi   -  p.y_Phi ;
    this->z_Teta  =  this->z_Teta  -  p.z_Teta;
    
    return (*this);
}
///======================================
Point Point::operator +(Point p){
    
    Point temp;
    
    temp.x_Ro    =  this->x_Ro    +  p.x_Ro  ;
    temp.y_Phi   =  this->y_Phi   +  p.y_Phi ;
    temp.z_Teta  =  this->z_Teta  +  p.z_Teta;
    
    return (temp);
}
///====================================
Point Point::operator -(Point p){
    
    Point temp;
    
    temp.x_Ro    =  this->x_Ro    -  p.x_Ro  ;
    temp.y_Phi   =  this->y_Phi   -  p.y_Phi ;
    temp.z_Teta  =  this->z_Teta  -  p.z_Teta;
    
    return (temp);
}
///=====================================
bool Point::operator ==(Point p){
    
    return( ( p.x_Ro - 0.0000000001 < this->x_Ro )  && ( this->x_Ro < p.x_Ro + 0.0000000001 ) && ( p.y_Phi - 0.0000000001 < this->y_Phi ) && ( this->y_Phi <  p.y_Phi + 0.0000000001 ) &&
	    ( p.z_Teta - 0.0000000001 < this->z_Teta ) && ( this->z_Teta < p.z_Teta + 0.0000000001 ) );
}
///=====================================
bool Point::operator !=(Point p){
    
    return ( ! ( *this == p ) );
}
///=====================================
Point Point::operator /=(double d){
    
    if (d == 0)
	cerr <<"!!!Divided By Zero!!!"<<(*this)<<endl;

    this->x_Ro    =  this->x_Ro    /  d;
    this->y_Phi   =  this->y_Phi   /  d;
    this->z_Teta  =  this->z_Teta  /  d;
    
    return (*this);
}
///=====================================
Point Point::operator /(double d){
    
    if (d == 0)
	cerr <<"!!!Divided By Zero!!!"<<(*this)<<endl;
	
    Point temp;
    
    temp.x_Ro    =  this->x_Ro    /  d;
    temp.y_Phi   =  this->y_Phi   /  d;
    temp.z_Teta  =  this->z_Teta  /  d;
    
    return (temp);
}
///====================================
Point Point::operator *=(double d){
    
    this->x_Ro    =  this->x_Ro    *  d;
    this->y_Phi   =  this->y_Phi   *  d;
    this->z_Teta  =  this->z_Teta  *  d;
    
    return (*this);
}
///=====================================
Point Point::operator *(double d){
    
    Point temp;
    
    temp.x_Ro    =  this->x_Ro    *  d;
    temp.y_Phi   =  this->y_Phi   *  d;
    temp.z_Teta  =  this->z_Teta  *  d;
    
    return (temp);
}
///=====================================
double Point::getMagnitude (){
    
    return ( sqrt ( ( this->x_Ro * this->x_Ro ) + ( this->y_Phi * this->y_Phi ) + ( this->z_Teta * this->z_Teta ) ) );
}
///=====================================
double Point::getDistanceTo(Point p){
    
    return ( ( *this - p ).getMagnitude());
}
///=====================================
double Point::getDistanceTo2(Point p){

    return ( sqrt ( ( ( this->x_Ro - p.x_Ro ) * ( this->x_Ro - p.x_Ro )   ) + ( ( this->y_Phi - p.y_Phi ) * ( this->y_Phi - p.y_Phi ) ) ));
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
Point Point::rotate( float angle )
{
    float dMag    = this->getMagnitude();
    float dNewDir = this->getDirection( ) + angle;  // add rotation angle to phi
    return Point( dMag * Geometry::Cos( dNewDir ), dMag * Geometry::Sin( dNewDir ));
}
///=====================================
float Point::getDirection( )
{
    return ( Geometry::ATan2( this->y_Phi, this->x_Ro ) );
}
