#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number of threads> <size N>\n", argv[0]);
        return 1;
    }

    // Get number of threads and size N from command line arguments
    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);

    if (num_threads <= 0 || N <= 0) {
        printf("Invalid number of threads or size N\n");
        return 1;
    }

    // Create matrix A, vector x and result vector
    matrix A = new_matrix(N, N);
    vector x = new_vector(N);
    vector result = new_vector(N);

    // Initialize matrix A and vector x with random values
    # pragma omp parallel for num_threads(num_threads)
    for (int i = 1; i <= N; i++) {
        vget(x, i) = rand();
    }
    
    # pragma omp parallel for num_threads(num_threads)
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= N; k++) {
            mget(A, i, k) = rand();
        }
    }

    // Perform matrix-vector multiplication using OpenMP
    const double time1 = omp_get_wtime();
    # pragma omp parallel for num_threads(num_threads)
    for (int i = 1; i <= N ; i++) {
        result.val[i] = 0.0;
        for (int j = 0; j < N; j++) {
            result.val[i] += A.val[i * N + j] * x.val[j];
        }
    }
    const double time2 = omp_get_wtime();
    const double time_taken = time2 - time1;

    printf("Time taken for matrix-vector multiplication: %f seconds with %d threads\n", time_taken, num_threads);
    // Free dynamically allocated memory
    delete_matrix(&A);
    delete_vector(&x);
    delete_vector(&result);

    return 0;
}

