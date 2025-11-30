#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#ifndef PCRE2POSIX_H
    #define PCRE2POSIX_H
    #define PCRE2_STATIC
    #define PCRE2_CODE_UNIT_WIDTH 8
    #include <pcre2posix.h>  // Essentially regex.h.
#endif

#define GET_VARIABLE_NAME(variable) (#variable)

int **Create2DIntArray(int lengthDimension1, int lengthDimension2)
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

void Destroy2DIntArray(int **array)
{
    free(*array);
    free(array);
}

static int OccurenceLowerBound(int array[], int length, int target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    int result = length;
    int lowerBound = 0;
    int upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        int intervalSpan = upperBound - lowerBound;
        int middle = lowerBound + intervalSpan / 2;

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

static int OccurenceUpperBound(int array[], int length, int target)
{
    // Feels a bit redundant having two identical functions with only one condition being different.
    int result = length;
    int lowerBound = 0;
    int upperBound = length - 1;

    while (lowerBound <= upperBound)
    {
        int intervalSpan = upperBound - lowerBound;
        int middle = lowerBound + intervalSpan / 2;

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
int CountFrequency(int array[], int length, int target)
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
