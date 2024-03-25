#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include <time.h>



void tridiagonal(matrix *A)
{
    mgetp(A,1,1)=2;
    mgetp(A,2,1)=-1;

for(int i=1; i<=A->rows; i++)
    {
    mgetp(A,i,i)=2;
    mgetp(A,i+1,i)=-1;
    mgetp(A,i-1,i)=-1;

    }
}

int main()
{
    // Matrix A
    matrix A = new_matrix(3, 3);

    mget(A, 1, 1) = 2.0;
    mget(A, 1, 2) = 1.0;
    mget(A, 1, 3) = 1.0;
    mget(A, 2, 1) = 1.0;
    mget(A, 2, 2) = 3.0;
    mget(A, 2, 3) = 1.0;
    mget(A, 3, 1) = 1.0;
    mget(A, 3, 2) = 1.0;
    mget(A, 3, 3) = 4.0;

    // Initial vector v
    vector v0 = new_vector(3);
    vget(v0, 1) = 1.0;
    vget(v0, 2) = 1.0;
    vget(v0, 3) = 1.0;

    // Print matrices
    print_matrix(&A);
    print_vector(&v0);

    double TOL = 1e-64;
    int MaxIters = 500;
    double lambda;

    lambda = RQiter(&v0, TOL, MaxIters, &A);
    printf("\nRQiter: Largest eigenvalue: %f\n\n", lambda);



    // Time test


    int N = 1;
    FILE *f = fopen("Ntime.csv", "w");
    double time_elapsed;
    double eigen_low, eigen_high;

    fprintf(f, "N,TIME\n");
    while (N!=0)
    {
        printf("\nEnter the size of the trigonal matrix (N*N) enter 0 to exit: ");
        scanf("%d", &N);
        if (N == 0)
        {
            break;
        }
        matrix B = new_matrix(N, N);
        tridiagonal(&B);
        vector u = new_vector(N);
        vget(u, 1) = 1.0;

        clock_t start = clock();

        eigen_high = PowIter(&u, TOL, 10, &B);
        eigen_high = RQiter(&u, TOL, N, &B);

        eigen_low = InversePowIter(0 ,&u, TOL, 10, &B);
        eigen_low = RQiter(&u, TOL, MaxIters, &B);

        

        clock_t end = clock();
        time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("\n################RESULTS################\n");
        printf("Time elapsed for N = %d: %f\n", N, time_elapsed);
        printf("Lowest eigenvalue: %f\n", eigen_low);
        printf("Highest eigenvalue: %f\n", eigen_high);
        fprintf(f, "%d,%f\n", N, time_elapsed);


    // Free memory
    delete_matrix(&B);
    delete_vector(&u);
    } 
    fclose(f);

    system("python3 plot.py");
    delete_matrix(&A);
    delete_vector(&v0);


}

