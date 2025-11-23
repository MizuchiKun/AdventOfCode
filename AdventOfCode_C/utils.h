#ifndef utils_h
#define utils_h

/// Creates a 2D int array of the given dimensions and returns an int** to it.
/// 
/// @param lengthDimension1 The length of the array's first dimension.
/// @param lengthDimension2 The length of the array's second dimension.
/// @return An int** to the created 2D int array.
int **Create2DIntArray(int lengthDimension1, int lengthDimension2);

/// Frees the memory the given 2D array occupies.
/// 
/// @param array The array to be destroyed.
void Destroy2DIntArray(int **array);

/// Finds the frequency of the target value in the given array.
/// 
/// @param array The sorted array to be searched.
/// @param length The length of the given array.
/// @param target The value to be searched for / counted.
/// @return The number of times the target value occurs in the given array.
int CountFrequency(int array[], int length, int target);

#endif
