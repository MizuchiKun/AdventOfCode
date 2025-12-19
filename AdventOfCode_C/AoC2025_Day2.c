#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "AoC2025_Day2.h"
#include "utils.h"

#define LINE_LENGTH 560

/// @brief Checks whether the given product ID is valid, according to the old criteria.\n 
/// An ID is invalid if it consists of a sequence of digits repeated TWICE.\n
/// E.g. 123123, 11, 17731773, etc.
/// @param id The ID to check.
/// @return True if the ID is valid, false otherwise.
static inline bool IsIDValidOld(uint64_t id)
{
    uint8_t digitCount = CountDigits(id);
    if (digitCount % 2 == 1)
    {
        perror("Parameter id must not have an odd number of digits.\n");
        exit(EXIT_FAILURE);
    }

    const uint8_t BASE10 = 10;
    const uint64_t POWER_OF_TEN_IN_MIDDLE = (uint64_t)powl(BASE10, (double)digitCount / 2);
    uint64_t firstHalf = id / POWER_OF_TEN_IN_MIDDLE;
    uint64_t secondHalf = id % POWER_OF_TEN_IN_MIDDLE;

    return firstHalf != secondHalf;
}

/// @brief Checks whether the given product ID is invalid, according to the new criteria.\n 
/// An ID is invalid if it consists of a sequence of digits repeated AT LEAST TWICE.\n
/// E.g. 123123, 1717, but also 111, 5353535353, etc.
/// @param id The ID to check.
/// @return True if the ID is invalid, false otherwise.
static inline bool IsIDValidNew(uint64_t id)
{
    uint8_t digitCount = CountDigits(id);
    if (digitCount == 1)
        return true;

    const uint8_t BASE10 = 10;

    // Check if id is a sequence of digits repeated partCount times.
    for (uint8_t partCount = 2; partCount <= digitCount; partCount++)
    {
        if (digitCount % partCount != 0)  continue;

        uint8_t partLength = digitCount / partCount;
        uint64_t idCopy = id;

        uint64_t previousPart = 0;
        bool isIdValid = false;
        for (uint32_t i = 0; i < partCount; i++)
        {
            uint8_t exponent = digitCount - (i + 1) * partLength;
            uint64_t powerAfterCurrentPart = (uint64_t)powl(BASE10, (double)exponent);

            uint64_t currentPart = idCopy / powerAfterCurrentPart;
            idCopy %= powerAfterCurrentPart;

            if (i == 0)
            {
                previousPart = currentPart;
                continue;
            }

            if (previousPart != currentPart)
            {
                isIdValid = true;
                break;
            }

            previousPart = currentPart;
        }

        if (!isIdValid)
            return false;
    }

    return true;
}

/// @brief Sums all invalid IDs in the given range.
/// @param start The start of the range (inclusively).
/// @param end The end of the range (inclusively).
/// @param useOldCriteria Whether to use the old or new criteria for invalid IDs.
/// @return The sum of all invalid IDs in the range.
static uint64_t SumInvalidIDsInRange(uint64_t start, uint64_t end, bool useOldCriteria)
{
    const uint8_t BASE10 = 10;
    uint64_t invalidIDsSum = 0;
    for (uint64_t id = start; id <= end; id++)
    {
        uint8_t digitCount = CountDigits(id);
        bool hasOddDigitCount = digitCount % 2 == 1;

        if (useOldCriteria && hasOddDigitCount)
        {
            long double lel = 0.0;
            int32_t size = sizeof(lel);
            uint64_t minValueWithMoreDigits = (uint64_t)powl(BASE10, digitCount);
            if (minValueWithMoreDigits <= end)
            {
                // WHEN USING THE OLD CRITERIA, skip ahead to the smallest value 
                // with more digits than the current ID, 
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

        bool idIsValid = useOldCriteria ? IsIDValidOld(id) : IsIDValidNew(id);
        if (!idIsValid)
        {
            invalidIDsSum += id;
        }
    }

    return invalidIDsSum;
}

/// @brief Processes the given file of product ID ranges.
/// @param filename The name of the file to process.
/// @param useOldCriteria Whether to use the new or old criteria for invalid IDs.\n
/// The old criteria considers an ID invalid when it consists of a sequence of digits repeated twice (e.g. 123123),\n
/// while the new criteria considers them invalid when the sequence is repeated AT LEAST twice (e.g. also 1212121212).
/// @return The sum of all invalid IDs.
static uint64_t ProcessIDsFile(const char *filename, bool useNewCriteria)
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

            invalidIDsSum += SumInvalidIDsInRange(start, end, useNewCriteria);
        }
    }

    fclose(file);
    return invalidIDsSum;
}

static void Part1()
{
    const char filename[] = "AoC2025_Day2.txt";
    uint64_t invalidIDsSum = ProcessIDsFile(filename, true);

    printf("Part 1: The sum of all invalid IDs (old criteria): %ju\n", (intmax_t)invalidIDsSum);
}

static void Part2()
{
    const char filename[] = "AoC2025_Day2.txt";
    uint64_t invalidIDsSum = ProcessIDsFile(filename, false);

    printf("Part 2: The sum of all invalid IDs (new criteria): %ju\n", (intmax_t)invalidIDsSum);
}

void AoC2025_Day2()
{
    Part1();
    Part2();
}
