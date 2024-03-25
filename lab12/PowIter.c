#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

double PowIter(vector* v, double TOL, int MaxIters, matrix* A)
{
    int k = 0;
    double lambda_old = 0.0;
    double lambda = 0.0;
    double diff = TOL + 1.0;

    while (diff > TOL && k < MaxIters)
    {
        vector w = matrix_vector_mult(A, v);
        lambda = vector_dot_mult(v, &w);
        diff = fabs(lambda - lambda_old);
        lambda_old = lambda;

        // Normalize the vector
        double norm_w = vector_norm(&w);
        for (int i = 1; i <= w.size; i++)
        {
            w.val[i - 1] /= norm_w;
        }

        // Copy the normalized vector w to v
        for (int i = 1; i <= v->size; i++)
        {
            v->val[i - 1] = w.val[i - 1];
        }

        delete_vector(&w);

        k++;
    }

    printf("Number of iterations: %d", k);
    return lambda;
}


