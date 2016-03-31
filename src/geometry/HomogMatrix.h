#ifndef HOMOGMATRIX_H
#define HOMOGMATRIX_H

#include <sstream>
#include "RotationMatrix.h"

class HomogMatrix
{
private:
  float elem[4][4];

public:
	HomogMatrix();
	HomogMatrix(const RotationMatrix& rot, const Point& trans);
	HomogMatrix(const Point& trans);
	HomogMatrix(const RotationMatrix& rot);
	HomogMatrix operator*(const HomogMatrix& other) const;
	friend std::ostream& operator<<(std::ostream& os, const HomogMatrix& h);
	void setTranslation(const Point& trans);
	void setRotation(const RotationMatrix& rot);
	void translate(const float& x, const float& y, const float& z);
	void translate(const Point& trans);
	Point getTranslation();
	RotationMatrix getRotation();
	HomogMatrix getInverse();
	
};

#endif // HOMOGMATRIX_H
