#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "malloc_custom.h"
#include "pcre2posix_custom.h"
#include "stdint_custom.h"
#include "utils.h"

i32 **Create2DIntArray(size_t lengthDimension1, size_t lengthDimension2)
{
    // I might try using the dynamic arrays here, but not now . . . (a bit more complicated, I think)
    i32 *values = (int*)SafeCalloc(lengthDimension1 * lengthDimension2, sizeof(int));
    i32 **array = (int**)SafeMalloc(lengthDimension1 * sizeof(int*));

    for (size_t i = 0; i < lengthDimension1; i++)
    {
        array[i] = values + i * lengthDimension2;
    }

    return array;
}

void Destroy2DIntArray(i32 **array)
{
    free(*array);
    free(array);
}

static i32 OccurenceLowerBound(i32 array[], i32 length, i32 target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    i32 result = length;
    i32 lowerBound = 0;
    i32 upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        i32 intervalSpan = upperBound - lowerBound;
        i32 middle = lowerBound + intervalSpan / 2;

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

static i32 OccurenceUpperBound(i32 array[], i32 length, i32 target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    i32 result = length;
    i32 lowerBound = 0;
    i32 upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        i32 intervalSpan = upperBound - lowerBound;
        i32 middle = lowerBound + intervalSpan / 2;

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
i32 CountFrequency(i32 array[], i32 length, i32 target)
{
    return OccurenceUpperBound(array, length, target)
           - OccurenceLowerBound(array, length, target);
}

u64 Modulo(i64 a, i64 b)
{
    u64 result = a % b;
    return (result < 0) ? result + b : result;
}

i8 Sign(i64 number)
{
    return (number == 0) ? 0 : number / abs(number);
}

u8 CountDigits(i64 value)
{
    if (value == 0)  return 1;
    return (u8)log10l(llabs(value)) + 1;
}
