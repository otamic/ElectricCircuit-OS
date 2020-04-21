//
//  matrix.h
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include "circuitElem.h"

typedef ElemType * Vector;
typedef ElemType ** Matrix;

void ini_vector(Vector & V, int n);
void ini_matrix(Matrix & M, int n, int m);
void destroy_matrix(Matrix & M, int n);
void destroy_vector(Vector & V);
double det(Matrix M, int n);
Vector crammer(Matrix M, Vector V, int n);

#endif /* matrix_h */
