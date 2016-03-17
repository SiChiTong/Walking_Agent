#include "RotationMatrix.h"

RotationMatrix::RotationMatrix()
{
    l0 = Point(1,0,0);
    l1 = Point(0,1,0);
    l2 = Point(0,0,1);
}

RotationMatrix::RotationMatrix(const Point& lin0, const Point& lin1, const Point& lin2)
{
    l0 = lin0;
    l1 = lin1;
    l2 = lin2;
}

RotationMatrix RotationMatrix::operator*(const RotationMatrix& other) const
{
    RotationMatrix result;

    result.l0.x_Ro = l0.x_Ro*other.l0.x_Ro + l0.y_Phi*other.l1.x_Ro + l0.z_Teta*other.l2.x_Ro;
    result.l0.y_Phi = l0.x_Ro*other.l0.y_Phi + l0.y_Phi*other.l1.y_Phi + l0.z_Teta*other.l2.y_Phi;
    result.l0.z_Teta = l0.x_Ro*other.l0.z_Teta + l0.y_Phi*other.l1.z_Teta + l0.z_Teta*other.l2.z_Teta;

    result.l1.x_Ro = l1.x_Ro*other.l0.x_Ro + l1.y_Phi*other.l1.x_Ro + l1.z_Teta*other.l2.x_Ro;
    result.l1.y_Phi = l1.x_Ro*other.l0.y_Phi + l1.y_Phi*other.l1.y_Phi + l1.z_Teta*other.l2.y_Phi;
    result.l1.z_Teta = l1.x_Ro*other.l0.z_Teta + l1.y_Phi*other.l1.z_Teta + l1.z_Teta*other.l2.z_Teta;

    result.l2.x_Ro = l2.x_Ro*other.l0.x_Ro + l2.y_Phi*other.l1.x_Ro + l2.z_Teta*other.l2.x_Ro;
    result.l2.y_Phi = l2.x_Ro*other.l0.y_Phi + l2.y_Phi*other.l1.y_Phi + l2.z_Teta*other.l2.y_Phi;
    result.l2.z_Teta = l2.x_Ro*other.l0.z_Teta + l2.y_Phi*other.l1.z_Teta + l2.z_Teta*other.l2.z_Teta;

    return result;
}


Point RotationMatrix::operator*(const Point& vector) const
{
    return Point(l0.x_Ro*vector.x_Ro + l0.y_Phi*vector.y_Phi + l0.z_Teta*vector.z_Teta,
		    l1.x_Ro*vector.x_Ro + l1.y_Phi*vector.y_Phi + l1.z_Teta*vector.z_Teta,
		    l2.x_Ro*vector.x_Ro + l2.y_Phi*vector.y_Phi + l2.z_Teta*vector.z_Teta );
}

ostream& operator<<(ostream& os, const RotationMatrix& r)
{
    os << setiosflags(ios::fixed) << setprecision(3);
    os << r.l0.x_Ro << ", " << r.l0.y_Phi << ", " << r.l0.z_Teta << endl;
    os << r.l1.x_Ro << ", " << r.l1.y_Phi << ", " << r.l1.z_Teta << endl;
    os << r.l2.x_Ro << ", " << r.l2.y_Phi << ", " << r.l2.z_Teta;
    return os;
}



RotationMatrix RotationMatrix::getInverse() const
{
    //The inverse of a rotation matrix is its transpose, which is also a rotation matrix
    return RotationMatrix(Point(l0.x_Ro, l1.x_Ro, l2.x_Ro),
			   Point(l0.y_Phi, l1.y_Phi, l2.y_Phi),
			   Point(l0.z_Teta, l1.z_Teta, l2.z_Teta));
}


RotationMatrix& RotationMatrix::rotateX(const float angle)
{
	const float c = cos(angle), s = sin(angle);
	RotationMatrix aux = *this;
	
	l0.y_Phi = c*aux.l0.y_Phi + s*aux.l0.z_Teta;
	l1.y_Phi = c*aux.l1.y_Phi + s*aux.l1.z_Teta;
	l2.y_Phi = c*aux.l2.y_Phi + s*aux.l2.z_Teta;
	
	l0.z_Teta = -s*aux.l0.y_Phi + c*aux.l0.z_Teta;
	l1.z_Teta = -s*aux.l1.y_Phi + c*aux.l1.z_Teta;
	l2.z_Teta = -s*aux.l2.y_Phi + c*aux.l2.z_Teta;
	
	return *this;
}

RotationMatrix& RotationMatrix::rotateY(const float angle)
{
	const float c = cos(angle), s = sin(angle);
	RotationMatrix aux = *this;
	
	l0.x_Ro = c*aux.l0.x_Ro - s*aux.l0.z_Teta;
	l1.x_Ro = c*aux.l1.x_Ro - s*aux.l1.z_Teta;
	l2.x_Ro = c*aux.l2.x_Ro - s*aux.l2.z_Teta;
	
	l0.z_Teta = s*aux.l0.x_Ro + c*aux.l0.z_Teta;
	l1.z_Teta = s*aux.l1.x_Ro + c*aux.l1.z_Teta;
	l2.z_Teta = s*aux.l2.x_Ro + c*aux.l2.z_Teta;
	
	return *this;
}

RotationMatrix& RotationMatrix::rotateZ(const float angle)
{
	const float c = cos(angle), s = sin(angle);
	RotationMatrix aux = *this;
	
	l0.x_Ro = c*aux.l0.x_Ro + s*aux.l0.y_Phi;
	l1.x_Ro = c*aux.l1.x_Ro + s*aux.l1.y_Phi;
	l2.x_Ro = c*aux.l2.x_Ro + s*aux.l2.y_Phi;
	
	l0.y_Phi = -s*aux.l0.x_Ro + c*aux.l0.y_Phi;
	l1.y_Phi = -s*aux.l1.x_Ro + c*aux.l1.y_Phi;
	l2.y_Phi = -s*aux.l2.x_Ro + c*aux.l2.y_Phi;
	return *this;
}





RotationMatrix GetRotationMatrixX(const float& angle)
{
    RotationMatrix result;
    result.l0 = Point(1, 0, 0);
    result.l1 = Point(0, cos(angle), -sin(angle));
    result.l2 = Point(0, sin(angle), cos(angle));
    return result;
}

RotationMatrix GetRotationMatrixY(const float& angle)
{
    RotationMatrix result;
    result.l0 = Point(cos(angle), 0, sin(angle));
    result.l1 = Point(0, 1, 0);
    result.l2 = Point(-sin(angle), 0, cos(angle));
    return result;
}

RotationMatrix GetRotationMatrixZ(const float& angle)
{
    RotationMatrix result;
    result.l0 = Point(cos(angle), -sin(angle), 0);
    result.l1 = Point(sin(angle), cos(angle), 0);
    result.l2 = Point(0, 0, 1);
    return result;  
}



