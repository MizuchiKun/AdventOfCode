#ifndef utils_h
#define utils_h

#include <stdint.h>
#ifndef PCRE2POSIX_H
    #define PCRE2POSIX_H
    #define PCRE2_STATIC
    #define PCRE2_CODE_UNIT_WIDTH 8
    #include <pcre2posix.h>  // Essentially regex.h.
#endif

/// Creates a 2D int array of the given dimensions and returns an int** to it.
/// 
/// @param lengthDimension1 The length of the array's first dimension.
/// @param lengthDimension2 The length of the array's second dimension.
/// @return An int** to the created 2D int array.
int32_t **Create2DIntArray(uint32_t lengthDimension1, uint32_t lengthDimension2);

/// Frees the memory the given 2D array occupies.
/// 
/// @param array The array to be destroyed.
void Destroy2DIntArray(uint32_t **array);

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
uint32_t Modulo(int64_t a, int64_t b);

/// @brief Returns the sign of the given number.
/// @param number The number to check.
/// @return +1 when number is positive, -1 when number is negative, and 0 when number is 0.
int8_t Sign(int64_t number);

/// @brief Counts the number of digits in value.
/// @param value The value to check.
/// @return The number of digits in value.
uint32_t CountDigits(int64_t value);

#endif
