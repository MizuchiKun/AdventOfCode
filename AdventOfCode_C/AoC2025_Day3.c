#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AoC2025_Day3.h"
#include "utils.h"

#define LINE_LENGTH 110

/// @brief Gets the largest Joltage in the given battery bank/array.\n
/// Joltage is the number you get when enabling enabledBatteriesCount batteries 
/// per bank and then concatenating their values/digits.
/// @param batteries The battery bank.
/// @param batteryCount The number of batteries in the given bank.
/// @param enabledBatteriesCount How many batteries to enable in each bank.
/// @return The max Joltage of the given battery bank under the given conditions.
static uint64_t LargestJoltageInBank(uint8_t *batteries, 
                                     const uint8_t batteryCount,
                                     const uint8_t enabledBatteriesCount)
{
    if (batteryCount < enabledBatteriesCount)
    {
        printf("Battery array / bank must have at least %d elements.\n", enabledBatteriesCount);
        exit(EXIT_FAILURE);
    }
    uint8_t *enabledBatteries = (uint8_t*)SafeCalloc(enabledBatteriesCount, sizeof(*enabledBatteries));
    for (uint8_t i = 0; i < enabledBatteriesCount; i++)
    {
        enabledBatteries[i] = batteries[i];
    }

    for (uint8_t i = enabledBatteriesCount; i < batteryCount; i++)
    {
        uint8_t nextBattery = batteries[i];
        uint8_t *lastEnabledBattery = &enabledBatteries[enabledBatteriesCount - 1];

        bool batteriesAreDecreasing = true;
        uint8_t increasingBatteryIndex = -1;
        for (uint8_t i = 0; i < enabledBatteriesCount - 1; i++)
        {
            // Check for a battery value which is lower than the previous one,
            // FROM START TO END, so the stored index is of the case 
            //     with a more significant digit (in case of multiple cases), 
            // since 'removing' the value before it results in the biggest maxJoltage increase.
            // (See if-elseif after this loop.)
            if (enabledBatteries[i] < enabledBatteries[i + 1])
            {
                batteriesAreDecreasing = false;
                increasingBatteryIndex = i + 1;
                break;
            }
        }

        if (!batteriesAreDecreasing)
        {
            // If any battery value is greater than the one before it,
            // 'removing' that prior value from the array, and 'appending' the nextBattery
            // value at the end, results in a larger maxJoltage at the end.
            for (uint8_t i = increasingBatteryIndex; i < enabledBatteriesCount; i++)
            {
                enabledBatteries[i - 1] = enabledBatteries[i];
            }
            *lastEnabledBattery = nextBattery;
        }
        else if (nextBattery > *lastEnabledBattery)
        {
            // Else if the nextBattery is larger than the lastEnabledBattery, 
            // replace the last battery with the nextBattery, 
            // since that's the largest possible maxJoltage increase remaining.
            *lastEnabledBattery = nextBattery;
        }
    }

    uint64_t maxJoltage = 0;
    const uint8_t BASE10 = 10;
    for (uint8_t i = 0; i < enabledBatteriesCount; i++)
    {
        uint64_t powerOfTen = (uint64_t)powl(BASE10, enabledBatteriesCount - i - 1);
        maxJoltage += enabledBatteries[i] * powerOfTen;
    }

    free(enabledBatteries);
    return maxJoltage;
}

/// @brief Gets the max total Joltage of the given file.\n
/// Joltage is the number you get when enabling enabledBatteriesCount batteries 
/// per bank/line and then concatenating their values/digits.
/// @param filename The filename of the file to get the Joltage of.
/// @param enabledBatteriesCount How many batteries to enable in each bank.
/// @return The max total Joltage of the file.
static uint64_t GetMaxTotalJoltageOfFile(const char *filename, const uint8_t enabledBatteriesCount)
{
    FILE *file = fopen(filename, "r");
    char line[LINE_LENGTH] = "";

    uint64_t totalJoltage = 0;
    while (fgets(line, LINE_LENGTH, file))
    {
        char *currentChar = line;
        uint8_t *batteries = (uint8_t*)SafeCalloc(LINE_LENGTH, sizeof(*batteries));
        uint8_t batteryCount = 0;
        // (The digits end with a newline character or NUL.)
        while (!(*currentChar == '\n' || *currentChar == '\0'))
        {
            uint8_t digit = (int8_t)(*currentChar - '0');
            batteries[batteryCount] = digit;

            currentChar++;
            batteryCount++;
        }
        batteries = SafeRealloc(batteries, batteryCount * sizeof(*batteries));
        /// Replace with dynamic array, once implemented.  But do that another time . . .

        totalJoltage += LargestJoltageInBank(batteries, batteryCount, enabledBatteriesCount);

        free(batteries);
    }

    return totalJoltage;
}

static void Part1()
{
    const char *filename = "AoC2025_Day3.txt";
    const uint8_t enabledBatteriesCount = 2;
    uint64_t totalJoltage = GetMaxTotalJoltageOfFile(filename, enabledBatteriesCount);
    printf("Part 1: Total Joltage (%u enabled batteries): %zu\n", 
           enabledBatteriesCount, totalJoltage);
}

static void Part2()
{
    const char *filename = "AoC2025_Day3.txt";
    const uint8_t enabledBatteriesCount = 12;
    uint64_t totalJoltage = GetMaxTotalJoltageOfFile(filename, enabledBatteriesCount);
    printf("Part 2: Total Joltage (%u enabled batteries): %zu\n",
           enabledBatteriesCount, totalJoltage);
}

void AoC2025_Day3()
{
    Part1();
    Part2();
}
