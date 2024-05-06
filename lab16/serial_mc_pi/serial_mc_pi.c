#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

int main() {

	clock_t start_time, end_time;
	double elapsed_time;
	double error;
	int i;

	printf("N,cpu-time, pi_estimate, relative error\n");

	for (i = 1; i < 20000; i += 1000) {

		start_time = clock();
		double pi_value = monte_carlo(i);
		end_time = clock();

		elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		error = fabs(pi_value - ACTUAL_PI);
		printf("%d,%.8f,%.8f, %.8f\n", i, elapsed_time, pi_value, error);

	}

}


