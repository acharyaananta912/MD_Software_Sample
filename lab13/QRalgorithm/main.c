#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "matrix.h"
#include "trimatrix.h"

int main()
{
  srand( time(NULL) );
  int N=0;
  printf("    Input N: ");
  scanf("%i",&N);
  assert(N>1);

  // Create a random symmetric matrix
  matrix A = new_matrix(N,N);

  for (int i=1; i<=N; i++)
    for (int j=1; j<=i; j++)
      {
        double tmp = ((double)rand())/((double)RAND_MAX);
        tmp = (double)((int)(10000.0*tmp))/10000.0;
        mget(A,i,j) = tmp;
      }
  for (int i=1; i<=(N-1); i++)
    for (int j=(i+1); j<=N; j++)
      { mget(A,i,j) = mget(A,j,i); }

  // Hessenberg reduction to tridiagonal form
  trimatrix T = new_trimatrix(N);
  void Hessenberg(const matrix* A, trimatrix* T);
  Hessenberg(&A,&T);
  printf("\n");
  printf("Original Matrix:\n");
  print_matrix(&A);
  printf("Reduction to Tridiagonal Form:\n");
  print_trimatrix(&T);

  // QR Algorithm to find eigenvalues of T
  // which are the same as the eigenvalues of A
  void QRA(trimatrix* T);
  QRA(&T);
  printf("After QR Algorithm:\n");
  print_trimatrix(&T);

  double min_eig, max_eig;
  double cond = ConditionNumber(&T, &min_eig, &max_eig);
  printf("Minimum Eigenvalue: %f\n", min_eig);
  printf("Maximum Eigenvalue: %f\n", max_eig);
  printf("Condition Number: %f\n", cond);
  printf("\n");
  printf("*** Check cputime.txt for time required using two method ***\n\n");
  

// Open the file for writing
FILE* file = fopen("cputime.txt", "w");
if (file == NULL)
{
    fprintf(stderr, "Error opening file for writing.\n");
    return 1;
}

fprintf(file, "N\tHessenberg\tQRA\tConditionNumber\tConditionNumberValue\n");

for (int N = 5; N <= 80; N *= 2)
{
    // Create a random symmetric matrix
    matrix A = new_matrix(N, N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= i; j++)
        {
            double tmp = ((double)rand()) / ((double)RAND_MAX);
            tmp = (double)((int)(10000.0 * tmp)) / 10000.0;
            mget(A, i, j) = tmp;
        }
    for (int i = 1; i <= (N - 1); i++)
        for (int j = (i + 1); j <= N; j++)
        {
            mget(A, i, j) = mget(A, j, i);
        }

    // Hessenberg reduction to tridiagonal form
    trimatrix T = new_trimatrix(N);
    clock_t hessenberg_start = clock();
    Hessenberg(&A, &T);
    clock_t hessenberg_end = clock();
    double hessenberg_time = ((double)(hessenberg_end - hessenberg_start)) / CLOCKS_PER_SEC;

    // QR Algorithm to find eigenvalues of T
    void QRA(trimatrix* T);
    clock_t qra_start = clock();
    QRA(&T);
    clock_t qra_end = clock();
    double qra_time = ((double)(qra_end - qra_start)) / CLOCKS_PER_SEC;

    // Find the smallest and largest absolute eigenvalues and compute the condition number
    double min_eig, max_eig;
    clock_t condition_start = clock();
    double cond = ConditionNumber(&T, &min_eig, &max_eig);
    clock_t condition_end = clock();
    double condition_time = ((double)(condition_end - condition_start)) / CLOCKS_PER_SEC;

    // Print the results to the file
    fprintf(file, "%d\t%f\t%f\t%f\t%f\n", N, hessenberg_time, qra_time, condition_time, cond);

    // Cleanup
    delete_matrix(&A);
    delete_trimatrix(&T);
}

// Close the file
fclose(file);

return 0;
}
