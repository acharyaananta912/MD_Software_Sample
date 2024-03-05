#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <assert.h>
#include <math.h>

int main()
{
    matrix A = new_matrix(3, 3);
    mget(A, 1, 1) = 2.0; mget(A, 1, 2) = 1.0; mget(A, 1, 3) = 1.0;
    mget(A, 2, 1) = 1.0; mget(A, 2, 2) = 3.0; mget(A, 2, 3) = 1.0;
    mget(A, 3, 1) = 1.0; mget(A, 3, 2) = 1.0; mget(A, 3, 3) = 4.0;
  
  print_matrix(&A);
    vector v0 = new_vector(3);
    vget(v0, 1) = 1.0; vget(v0, 2) = 1.0; vget(v0, 3) = 1.0;

    double TOL = 1.0e-8;
    int MaxIters = 500;

    double lambda = PowIter(&v0, TOL, MaxIters, &A);

    printf("Final approximation of the largest eigenvalue: %f\n", lambda);

    delete_matrix(&A);
    delete_vector(&v0);

    return 0;
}

