#ifndef HOMOGMATRIX_H
#define HOMOGMATRIX_H

#include <sstream>
#include "RotationMatrix.h"

/// \define This class gives the functionality to use the homogeneous matrix with size of the 4*4.
/// the equivalent matrix equation is homogeneous if the matrix equations always has at least one
/// solution, the zero solution. This class has been used to solve the inverse Kinematics equations.
class HomogMatrix {

public:

  /// \define The constructor of the class
  HomogMatrix();

  /// \define The constructor of the homogeneous matrix
  /// \param[in] _rot rotation matrix represents the rotation of the homogeneous matrix
  /// \param[in] _trans A vector that represents the translation part of the Homogeneous matrix
  HomogMatrix(const RotationMatrix& _rot, const Point& _trans);

  /// \define The constructor of the homogeneous matrix
  /// \param[in] _trans A vector that represents the translation part of the Homogeneous matrix
  HomogMatrix(const Point& trans);

  /// \define The constructor of the homogeneous matrix
  /// \param[in] _trans A vector that represents the translation part of the Homogeneous matrix
  HomogMatrix(const RotationMatrix& rot);

  /// \define The multiplication operator for multiplying two homogeneous matrix
  HomogMatrix operator*(const HomogMatrix& other) const;

  /// \define Printing an homogeneous matrix on screen
  friend std::ostream& operator<<(std::ostream& os, const HomogMatrix& h);

  /// \define Set a translation vector of an homogeneous matrix
  void setTranslation(const Point& trans);

  /// \define Set a rotation matrix of an homogeneous matrix
  void setRotation(const RotationMatrix& rot);

  /// \define translate homogeneous matrix using a given elements of translation vector
  /// \define param[in] X, Y, Z of the traslation vector
  void translate(const float& x, const float& y, const float& z);

  /// \define translate homogeneous matrix using a given the translation vector
  /// \define param[in] _trans the translation vector
  void translate(const Point& trans);

  /// \define translate homogeneous matrix using a given the translation vector
  /// \define param[in] _trans the translation vector
  Point getTranslation();

  /// \define  Get the rotation matrix
  RotationMatrix getRotation();

  /// \define  Calculate the inverse of an homogeneous matrix
  /// this is the main functionality used in the inverse Kinematics
  HomogMatrix getInverse();

private:

  /// \define The matrix elements variables
  float elem[4][4];

};

#endif // HOMOGMATRIX_H
