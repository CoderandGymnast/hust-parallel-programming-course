#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main()
{
	int a[10][10], b[10][10], mul[10][10], r, c, i, j, k;
	system("cls");
	printf("enter the number of row=");
	scanf("%d", &r);
	printf("enter the number of column=");
	scanf("%d", &c);
	printf("enter the first matrix element=\n");
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	printf("enter the second matrix element=\n");
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			scanf("%d", &b[i][j]);
		}
	}

	int numCols = c;
	int NUM_THREADS = omp_get_num_threads();
	int numColsPerThread = floor(numCols / NUM_THREADS);
	int numColsForLastThread = numCols - (NUM_THREADS - 1) * numColsPerThread;

	int lastThreadID = NUM_THREADS - 1;
	int numNonLastThread = NUM_THREADS - 1;

#pragma omp parallel
	{

		int threadID = omp_get_thread_num();
		if (threadID != lastThreadID)
		{
			for (int i = 0; i < r; i++)
			{
				int nc = (threadID + 1) * numColsPerThread;
				for (int j = threadID * numColsPerThread; j < nc; j++)
				{

					mul[i][j] = 0;
					for (k = 0; k < nc; k++)
					{
						mul[i][j] += a[i][k] * b[k][j];
					}
				}
			}
		}
		else
		{ // last thread.
			for (int i = 0; i < r; i++)
			{
				int nc = numCols;
				for (int j = threadID * numColsPerThread; j < numCols; j++)
				{

					mul[i][j] = 0;
					for (k = 0; k < nc; k++)
					{
						mul[i][j] += a[i][k] * b[k][j];
					}
				}
			}
		}
	}

	printf("multiply of the matrix=\n");

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			printf("%d\t", mul[i][j]);
		}
		printf("\n");
	}
	return 0;
}
