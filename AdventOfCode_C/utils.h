#ifndef utils_h
#define utils_h

/// <summary>
/// Creates a 2D int array of the given dimensions and returns an int** to it.
/// </summary>
/// <param name="lengthDimension1">The length of the array's first dimension.</param>
/// <param name="lengthDimension2">The length of the array's second dimension.</param>
/// <returns></returns>
int **Create2DIntArray(int lengthDimension1, int lengthDimension2);

/// <summary>
/// Frees the memory the given 2D array occupies.
/// </summary>
/// <param name="array">The array to be destroyed.</param>
void Destroy2DIntArray(int **array);

/// <summary>
/// Finds the frequency of the target value in the given array.
/// </summary>
/// <param name="array">The sorted array to be searched.</param>
/// <param name="length">The length of the given array.</param>
/// <param name="target">The value to be searched for / counted.</param>
/// <returns>The number of times the target value occurs in the given array.</returns>
int CountFrequency(int array[], int length, int target);

#endif
