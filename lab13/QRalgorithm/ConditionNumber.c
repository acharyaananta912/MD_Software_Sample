#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "matrix.h"
#include "trimatrix.h"

double ConditionNumber(const trimatrix* T, double* smallest_abs_eig, double* largest_abs_eig)
{
    // Find the smallest and largest absolute eigenvalues
    double min_abs_eig = INFINITY;
    double max_abs_eig = 0.0;
    for (int i = 1; i <= T->rows; i++)
    {
        double eig = tget(T, i, i);
        double abs_eig = fabs(eig);
        if (abs_eig < min_abs_eig)
        {
            min_abs_eig = abs_eig;
        }
        if (abs_eig > max_abs_eig)
        {
            max_abs_eig = abs_eig;
        }
    }

    *smallest_abs_eig = min_abs_eig;
    *largest_abs_eig = max_abs_eig;

    // Calculate and return the condition number
    return max_abs_eig / min_abs_eig;
}

