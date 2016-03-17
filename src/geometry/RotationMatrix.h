#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include <cmath>
#include <iomanip>
#include "Point.h"

class RotationMatrix
{
protected:


public:
    Point l0, l1, l2; //LINES
    
    
    RotationMatrix();
    RotationMatrix(const Point& lin0, const Point& lin1, const Point& lin2);

    RotationMatrix operator*(const RotationMatrix& other) const;
    Point operator*(const Point& vector) const;
    
    RotationMatrix& rotateX(const float angle);
    RotationMatrix& rotateY(const float angle);
    RotationMatrix& rotateZ(const float angle);
    RotationMatrix getInverse() const;
    
    
    friend std::ostream& operator<<(std::ostream& os, const RotationMatrix& r);   
    
    
private:
    
    
};

RotationMatrix GetRotationMatrixX(const float& angle);
RotationMatrix GetRotationMatrixY(const float& angle);
RotationMatrix GetRotationMatrixZ(const float& angle);

#endif // ROTATIONMATRIX_H
