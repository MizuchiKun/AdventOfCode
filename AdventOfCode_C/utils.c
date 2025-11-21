#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int **Create2DIntArray(int lengthDimension1, int lengthDimension2)
{
	int *values = calloc(lengthDimension1 * lengthDimension2, sizeof(int));
	int **array = malloc(lengthDimension1 * sizeof(int*));

	for (int i = 0; i < lengthDimension1; i++)
	{
		array[i] = values + i * lengthDimension2;
	}

	return array;
}

void Destroy2DIntArray(int **array)
{
	free(*array);
	free(array);
}
