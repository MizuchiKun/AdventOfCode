#ifndef utils_h
#define utils_h

#include <stdint.h>
#include "pcre2posix_custom.h"

#define GET_VARIABLE_NAME(variable) (#variable)

/// Creates a 2D int array of the given dimensions and returns an int** to it.
/// 
/// @param lengthDimension1 The length of the array's first dimension.
/// @param lengthDimension2 The length of the array's second dimension.
/// @return An int** to the created 2D int array.
int32_t **Create2DIntArray(size_t lengthDimension1, size_t lengthDimension2);

/// Frees the memory the given 2D array occupies.
/// 
/// @param array The array to be destroyed.
void Destroy2DIntArray(int32_t **array);

/// Finds the frequency of the target value in the given array.
/// 
/// @param array The sorted array to be searched.
/// @param length The length of the given array.
/// @param target The value to be searched for / counted.
/// @return The number of times the target value occurs in the given array.
int32_t CountFrequency(int32_t *array, int32_t length, int32_t target);

/// Creates the substring of sourceString described by match.
/// 
/// @param match The match which describes the substring.
/// @param sourceString The string in which the match was found.
/// @return A pointer to the created substring.
char *MatchToStr(regmatch_t *match, char *sourceString);

/// @brief Calculates the result of a mod b.
/// @param a The first argument.
/// @param b The second argument.
/// @return The modulus of a and b.
uint64_t Modulo(int64_t a, int64_t b);

/// @brief Returns the sign of the given number.
/// @param number The number to check.
/// @return +1 when number is positive, -1 when number is negative, and 0 when number is 0.
int8_t Sign(int64_t number);

/// @brief Counts the number of digits in value.
/// @param value The value to check.
/// @return The number of digits in value.
uint8_t CountDigits(int64_t value);

/// @brief A 'safe' version of malloc() which prints an error and exits the program when malloc() fails.
/// @param size The size (in bytes) to allocate.
/// @return A pointer to the allocated block of memory.
void *SafeMalloc(size_t size);

/// @brief A 'safe' version of calloc() which prints an error and exits the program when calloc() fails.
/// @param count The number of elements to allocate memory for.
/// @param size The size (in bytes) of each element.
/// @return A pointer to the allocated block of memory.
void *SafeCalloc(size_t count, size_t size);

/// @brief A 'safe' version of realloc() which prints an error and exits the program when realloc() fails.
/// @param block A pointer to the block of memory to re-allocate.
/// @param size The size (in bytes) to re-allocate to the given block.
/// @return A pointer to the allocated block of memory.
void *SafeRealloc(void *block, size_t size);

#endif
