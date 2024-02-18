#include <stdio.h>

int main()
{
	int N = 53;
	int count = 0;

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
