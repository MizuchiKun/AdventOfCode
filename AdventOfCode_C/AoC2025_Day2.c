#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "utils.h"

#define LINE_LENGTH 560

/// @brief Checks whether the given product ID is invalid.\n 
/// An ID is invalid if it's of the pattern (A.A) aka. "A concatenate A", 
/// where A is a positive integer. E.g.: 123123, 11, 1717, 537537, etc.
/// 
/// @param id The ID to check.
/// @return True if the ID is invalid, false otherwise.
static inline bool IsInvalidID(uint64_t id)
{
    int32_t digitCount = CountDigits(id);
    if (digitCount % 2 == 1)
    {
        perror("Parameter id must not have an odd number of digits.\n");
        exit(EXIT_FAILURE);
    }

    const int32_t BASE10 = 10;
    const uint32_t POWER_OF_TEN_IN_MIDDLE = pow(BASE10, (double)digitCount / 2);
    uint64_t firstHalf = id / POWER_OF_TEN_IN_MIDDLE;
    uint64_t secondHalf = id % POWER_OF_TEN_IN_MIDDLE;

    return firstHalf == secondHalf;
}

/// @brief Sums all invalid IDs in the given range.
/// @param start The start of the range (inclusively).
/// @param end The end of the range (inclusively).
/// @return The sum of all invalid IDs in the range.
static uint64_t SumInvalidIDsInRange(uint64_t start, uint64_t end)
{
    const uint8_t BASE10 = 10;
    uint64_t invalidIDsSum = 0;
    for (uint64_t id = start; id <= end; id++)
    {
        uint32_t digitCount = CountDigits(id);
        bool hasOddDigitCount = digitCount % 2 == 1;

        if (hasOddDigitCount)
        {
            long double lel = 0.0;
            int32_t size = sizeof(lel);
            uint64_t minValueWithMoreDigits = powl(BASE10, digitCount);
            if (minValueWithMoreDigits <= end)
            {
                // Skip ahead to the smallest value with more digits than value, 
                // since an ID with an odd digitCount cannot be invalid.
                id = minValueWithMoreDigits - 1;  // -1 due to id++ in loop head.
                continue;
            }
            else
            {
                // Stop checking, since there are no more IDs with an even digitCount.
                break;
            }
        }

        if (IsInvalidID(id))
        {
            invalidIDsSum += id;
        }
    }

    return invalidIDsSum;
}

/// @brief Processes the given file of product ID ranges.
/// @param filename The name of the file to process.
/// @return The sum of all invalid IDs.
static uint64_t ProcessIDsFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file \"%s\" could not be opened/found.\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[LINE_LENGTH] = "";
    uint64_t invalidIDsSum = 0;
    const char NUL = '\0';
    const uint8_t BASE10 = 10;
    const uint8_t SEPARATOR_OFFSET = sizeof(char);  // The size of a separating '-' or ','.
    while (fgets(line, LINE_LENGTH, file))
    {
        char *numStart = line;
        while (*numStart != NUL)
        {
            uint64_t start = strtoull(numStart, &numStart, BASE10);
            numStart += SEPARATOR_OFFSET;  // Offset because of separating '-'.
            uint64_t end = strtoull(numStart, &numStart, BASE10);
            numStart += SEPARATOR_OFFSET;  // Offset because of separating ','.

            invalidIDsSum += SumInvalidIDsInRange(start, end);
        }
    }

    fclose(file);
    return invalidIDsSum;
}

static void Part1()
{
    const char filename[] = "AoC2025_Day2.txt";
    uint64_t invalidIDsSum = ProcessIDsFile(filename);

    printf("Part 1: The sum of all invalid IDs: %ju\n", (intmax_t)invalidIDsSum);
}

static void Part2()
{
    printf("Part 2: <not implemented yet>\n");
}

void AoC2025_Day2()
{
    Part1();
    Part2();
}
