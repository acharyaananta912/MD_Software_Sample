#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

double monte_carlo(const int N) {
    int in_circle = 0;
    double x, y, r;

    srand(time(NULL));

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

#define ACTUAL_PI  3.14159265358979323846

int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("N,cpu-time, pi_estimate, relative error\n");
    }

    for (int i = 10; i <= 20000; i += 1000) {
        double start_time, end_time;
        double elapsed_time;

        start_time = MPI_Wtime();

        double local_pi_value = monte_carlo(i / size);
        double global_pi_value;

        if (rank == 0) {
            global_pi_value = local_pi_value;
            for (int p = 1; p < size; p++) {
                double recv_value;
                MPI_Recv(&recv_value, 1, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                global_pi_value += recv_value;
            }

        } else {
            MPI_Send(&local_pi_value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        end_time = MPI_Wtime();

        if (rank == 0) {
            elapsed_time = end_time - start_time;
            printf("%d,%.8f,%.8f,%.8f\n", i, elapsed_time, global_pi_value / size, fabs(global_pi_value / size - ACTUAL_PI));
        }
    }

    MPI_Finalize();

    return 0;
}

