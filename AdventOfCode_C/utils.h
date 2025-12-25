#ifndef utils_h
#define utils_h

#include <stdbool.h>
#include "pcre2posix_custom.h"
#include "stdint_custom.h"

#define GET_VARIABLE_NAME(variable) (#variable)

//// Maybe create NDArray .c and .h files? With actual, 'proper', struct-based implementation?

/// Creates a 2D int array of the given dimensions and returns an int** to it.
/// 
/// @param lengthDimension1 The length of the array's first dimension.
/// @param lengthDimension2 The length of the array's second dimension.
/// @return An int** to the created 2D int array.
i32 **Create2DIntArray(size_t lengthDimension1, size_t lengthDimension2);

/// Frees the memory the given 2D array occupies.
/// 
/// @param array The array to be destroyed.
void Destroy2DIntArray(i32 **array);

/// Finds the frequency of the target value in the given array.
/// 
/// @param array The sorted array to be searched.
/// @param length The length of the given array.
/// @param target The value to be searched for / counted.
/// @return The number of times the target value occurs in the given array.
i32 CountFrequency(i32 array[], i32 length, i32 target);

/// @brief Calculates the result of a mod b.
/// @param a The first argument.
/// @param b The second argument.
/// @return The modulus of a and b.
u64 Modulo(i64 a, i64 b);

/// @brief Returns the sign of the given number.
/// @param number The number to check.
/// @return +1 when number is positive, -1 when number is negative, and 0 when number is 0.
i8 Sign(i64 number);

/// @brief Counts the number of digits in value.
/// @param value The value to check.
/// @return The number of digits in value.
u8 CountDigits(i64 value);

#endif
