#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define ACTUAL_PI  3.14159265358979323846

double monte_carlo(const int N) {

    int in_circle = 0;
    double x, y, r;

    #pragma omp parallel for reduction(+:in_circle) private(x, y, r)
    for (int i = 0; i < N; i++) {

        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        r = sqrt(x*x + y*y);
        if (r <= 1) {
            in_circle++;
        }
    }

    double pi_value = 4.0 * in_circle / N;

    return pi_value;
}

int main() {

    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);

    printf("N,wall-time,pi_estimate, relative-error\n");

    for (int N = 1; N <= 20000; N += 1000) {

        double start_time = omp_get_wtime();
        double pi_value = monte_carlo(N);
        double end_time = omp_get_wtime();

        double elapsed_time = end_time - start_time;
        double error = fabs(pi_value - ACTUAL_PI);

        printf("%d,%.8f,%.8f,%.8f\n", N, elapsed_time, pi_value, error);

    }

    return 0;
}

