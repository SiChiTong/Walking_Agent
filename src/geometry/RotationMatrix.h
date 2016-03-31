/*
 * Copyright (C) 2016 nima@ua.pt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include <cmath>
#include <iomanip>
#include "Point.h"

class RotationMatrix
{


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
    RotationMatrix GetRotationMatrixX(const float& angle);
    RotationMatrix GetRotationMatrixY(const float& angle);
    RotationMatrix GetRotationMatrixZ(const float& angle);
    
    
};


#endif // ROTATIONMATRIX_H
