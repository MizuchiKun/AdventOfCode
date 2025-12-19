#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <math.h>
#include "utils.h"
#include "pcre2posix_custom.h"

int32_t **Create2DIntArray(size_t lengthDimension1, size_t lengthDimension2)
{
    int32_t *values = (int*)SafeCalloc(lengthDimension1 * lengthDimension2, sizeof(int));
    int32_t **array = (int**)SafeMalloc(lengthDimension1 * sizeof(int*));

    for (size_t i = 0; i < lengthDimension1; i++)
    {
        array[i] = values + i * lengthDimension2;
    }

    return array;
}

void Destroy2DIntArray(int32_t **array)
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
    char *substring = SafeMalloc(size + NUL_SIZE);

    memcpy(substring, sourceString + match->rm_so, size);
    substring[size] = NUL;

    return substring;
}

uint64_t Modulo(int64_t a, int64_t b)
{
    uint64_t result = a % b;
    return (result < 0) ? result + b : result;
}

int8_t Sign(int64_t number)
{
    return (number == 0) ? 0 : number / abs(number);
}

uint8_t CountDigits(int64_t value)
{
    if (value == 0)  return 1;
    return (uint8_t)log10l(llabs(value)) + 1;
}

/// @brief Prints an error and exits the program if there was an allocation failure aka. the given pointer is null.
/// @param block The resulting pointer of a memory allocation to check.
static void HandleAllocationFailure(void *block)
{
    if (!block)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
}

void *SafeMalloc(size_t size)
{
    void *allocatedMemory = malloc(size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}

void *SafeCalloc(size_t count, size_t size)
{
    void *allocatedMemory = calloc(count, size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}

void *SafeRealloc(void *block, size_t size)
{
    void *allocatedMemory = realloc(block, size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}
