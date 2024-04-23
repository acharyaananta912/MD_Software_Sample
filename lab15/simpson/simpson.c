#include <stdio.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <stdlib.h>

double f(double x) {
    return exp(-8 * x * x);
}

double simpson_rule(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = f(a) + f(b);

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < N / 2; i++) {
        double x1 = a + 2 * i * h;
        double x2 = a + (2 * i - 1) * h;
        sum += 4 * f(x1) + 2 * f(x2);
    }
    return (h * sum / 3);
}

void print_err(double a, double b) {
    int N_values[] = {10, 20, 40, 80, 160, 320, 640, 1280};
    int num_values = sizeof(N_values) / sizeof(N_values[0]);

    printf("|   N   |     Error    |   Error Ratio |\n");
    printf("|-------|--------------|---------------|\n");

    double prev_error = 0.0;
    for (int i = 0; i < num_values; i++) {
        int N = N_values[i];
        double integral = simpson_rule(a, b, N);
        double error = fabs(integral - 0.62661737464261433833);
        double error_ratio = 0.0;
        if (i > 0) {
            error_ratio = prev_error / error;
        }
        printf("| %5d | %12.10f | %13.10f |\n", N, error, error_ratio);
        prev_error = error;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_threads> <N>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);

    const double a = -1.0; // Lower limit of integration
    const double b = 1.0;  // Upper limit of integration

    omp_set_num_threads(num_threads);

    const double start_time = omp_get_wtime();
    double integral = simpson_rule(a, b, N);
    const double end_time = omp_get_wtime();

    printf("\n******************************************\n");
    printf("* Function: e^(-8x^2):\n");
    printf("* Interval: %.2f to %.2f\n",a,b) ;
    printf("* Number of subinterval(N): %d\n", N);
    printf("* Number of threads: %d\n", num_threads);
    printf("* Result ~ %.20f\n",integral);
    printf("* Error: %.20f\n", fabs(integral - 0.62661737464261433833));
    printf("* Time taken: %.6f seconds\n", end_time - start_time);
    printf("********************************************\n");

    if (num_threads == 1) {
        printf("\nErrors:\n");
        print_err(a, b);
    }
    return 0;
}

