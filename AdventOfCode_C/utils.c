#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <math.h>
#ifndef PCRE2POSIX_H
    #define PCRE2POSIX_H
    #define PCRE2_STATIC
    #define PCRE2_CODE_UNIT_WIDTH 8
    #include <pcre2posix.h>  // Essentially regex.h.
#endif

#define GET_VARIABLE_NAME(variable) (#variable)

int32_t **Create2DIntArray(uint32_t lengthDimension1, uint32_t lengthDimension2)
{
    int *values = calloc(lengthDimension1 * lengthDimension2, sizeof(int));
    int **array = malloc(lengthDimension1 * sizeof(int*));

    if (!values || !array)
        return NULL;

    for (int i = 0; i < lengthDimension1; i++)
    {
        array[i] = values + i * lengthDimension2;
    }

    return array;
}

void Destroy2DIntArray(uint32_t **array)
{
    free(*array);
    free(array);
}

static int32_t OccurenceLowerBound(int32_t array[], int32_t length, int32_t target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    int32_t result = length;
    int32_t lowerBound = 0;
    int32_t upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        int32_t intervalSpan = upperBound - lowerBound;
        int32_t middle = lowerBound + intervalSpan / 2;

        if (array[middle] >= target)
        {
            result = middle;
            upperBound = middle - 1;
        }
        else
        {
            lowerBound = middle + 1;
        }
    }

    return result;
}

static int32_t OccurenceUpperBound(int32_t array[], int32_t length, int32_t target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    int32_t result = length;
    int32_t lowerBound = 0;
    int32_t upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        int32_t intervalSpan = upperBound - lowerBound;
        int32_t middle = lowerBound + intervalSpan / 2;

        if (array[middle] > target)
        {
            result = middle;
            upperBound = middle - 1;
        }
        else
        {
            lowerBound = middle + 1;
        }
    }

    return result;
}

// Basis of this binary search frequency counting code: https://www.geeksforgeeks.org/dsa/count-number-of-occurrences-or-frequency-in-a-sorted-array/#expected-approach-using-binary-search-ologn-time-and-o1-space.
int32_t CountFrequency(int32_t *array, int32_t length, int32_t target)
{
    return OccurenceUpperBound(array, length, target)
           - OccurenceLowerBound(array, length, target);
}

char *MatchToStr(regmatch_t *match, char *sourceString)
{
    const char NUL = '\0';
    const size_t NUL_SIZE = sizeof(NUL);
    size_t size = (size_t)(match->rm_eo - match->rm_so);
    char *substring = malloc(size + NUL_SIZE);
    if (substring == NULL)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }

    memcpy(substring, sourceString + match->rm_so, size);
    substring[size] = NUL;

    return substring;
}

uint32_t Modulo(int64_t a, int64_t b)
{
    int result = a % b;
    return (result < 0) ? result + b : result;
}

int8_t Sign(int64_t number)
{
    return (number == 0) ? 0 : number / abs(number);
}

uint32_t CountDigits(int64_t value)
{
    if (value == 0)  return 1;
    return (uint32_t)log10l(llabs(value)) + 1;
}
