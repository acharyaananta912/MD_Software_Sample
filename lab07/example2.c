#include <stdio.h>

int main()
{
        int N;
        int count = 0;

	printf("Enter a positive and odd integer: ");
	scanf("%d", &N);

	if (N <= 0 || N % 2 == 0) 
	{
		printf("ERROR: Positive and Odd number expected.\n");
		return 1;
	};
        for (int i=1; i<=N; i++)
        {
                if (i%2 != 0)
                {
                        printf("%d ", i);
                        count++;
                }
                if (count == 5 || i == N)
                {
                        printf("\n");
                        count = 0;
                }
        }

        return 0;
}
