#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"



double InversePowIter(double mu,vector* v,double TOL,int MaxIters,matrix *A)
{
    double lambda,tol,lambda_new;
    vector_normalize(v);
    
    vector tmp = matrix_vector_mult(A,v);
    int iterations=0;
    lambda = vector_dot_mult(v,&tmp);

    // let's define the identity matrix
    matrix lambda_I = new_matrix(A->rows,A->cols);
    do 
    {
    iterations++;
    for(int i=1; i<=A->rows; i++)
    {
        mget(lambda_I,i,i)=mu;
    }
    /*create lamba * I*/
    matrix sub = matrix_sub(A,&lambda_I);
    vector w =solve(&sub,v);
    // normalize w
    vector_normalize(&w);
    v=&w;
    tmp = matrix_vector_mult(A,v);
    lambda_new = vector_dot_mult(v,&tmp);
    tol = fabs(lambda_new-lambda);
    lambda = lambda_new;


    } while (tol > TOL && iterations < MaxIters);
     printf("Number of Iterations InvPowerIter: %d\n", iterations);

    return lambda;

}
