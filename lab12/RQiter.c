#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

// Added Functions
  void vector_normalize(vector* v)
{
    assert(v != NULL);
    double norm = vector_norm(v);
    for (int i = 0; i < v->size; i++)
    {
        v->val[i] /= norm;
    }
}

double vector_norm(vector* v)
{
    assert(v != NULL);
    double norm = 0.0;
    for (int i = 0; i < v->size; i++)
    {
        norm += v->val[i] * v->val[i];
    }
    return sqrt(norm);
}


double RQiter(vector* v, double TOL, int MaxIters, matrix* A) 
{
    int k = 0;
    double lambda_old = 0.0;
    double lambda = 0.0;
    double error = TOL + 1.0;

    vector_normalize(v);
    // computes Av(0)
    vector mult1 = matrix_vector_mult(A, v);
    // calculated lambda(0)
    lambda_old = vector_dot_mult(v, &mult1);

    matrix LambdaI = new_matrix(A->rows, A->cols);
    matrix A_minus_lambdaI = new_matrix(A->rows, A->cols);


    do
    {
        k++;
        for (int i = 1; i <= A->rows; i++)
        {
            mget(LambdaI, i, i) = lambda_old;
        }
        A_minus_lambdaI = matrix_sub(A, &LambdaI);
        // Solve (A - lam(k-1)I)w = v(k-1)
        vector w = solve(&A_minus_lambdaI, v);
        vector_normalize(&w);
        v = &w; // update v(k-1)

        vector mult2 = matrix_vector_mult(A, v);
        lambda = vector_dot_mult(v, &mult2);

        // Check convergence
        error = fabs(lambda - lambda_old);
        lambda_old = lambda;

    } while (error > TOL && k < MaxIters);
    printf("\nNumber of iterations: %d", k);

    return lambda;

}