#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "AoC2025_Day3.h"
#include "DynamicArray.h"
#include "malloc_custom.h"
#include "stdint_custom.h"
#include "utils.h"

#define LINE_LENGTH 110

/// @brief Gets the largest Joltage in the given battery bank/array.\n
/// Joltage is the number you get when enabling enabledBatteriesCount batteries 
/// per bank and then concatenating their values/digits.
/// @param batteries The battery bank.
/// @param enabledBatteriesCount How many batteries to enable in each bank.
/// @return The max Joltage of the given battery bank under the given conditions.
static u64 LargestJoltageInBank(u8DA batteries, 
                                const u8 enabledBatteriesCount)
{
    if (batteries.count < enabledBatteriesCount
        || enabledBatteriesCount == 0)
    {
        printf("Battery array / bank must have at least %d elements.\n", enabledBatteriesCount);
        exit(EXIT_FAILURE);
    }
    u8DA enabledBatteries = {0};
    for (u8 i = 0; i < enabledBatteriesCount; i++)
    {
        daAppend(enabledBatteries, batteries.items[i]);
    }
    daCrop(enabledBatteries);

    u8 *lastEnabledBattery = &enabledBatteries.items[enabledBatteries.count - 1];
    for (u8 i = enabledBatteries.count; i < batteries.count; i++)
    {
        u8 nextBattery = batteries.items[i];

        bool batteriesAreDecreasing = true;
        u8 increasingBatteryIndex = -1;
        for (u8 i = 0; i < enabledBatteries.count - 1; i++)
        {
            // Check for a battery value which is lower than the previous one,
            // FROM START TO END, so the stored index is of the case 
            //     with a more significant digit (in case of multiple cases), 
            // since 'removing' the value before it results in the biggest maxJoltage increase.
            // (See if-elseif after this loop.)
            if (enabledBatteries.items[i] < enabledBatteries.items[i + 1])
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
            for (u8 i = increasingBatteryIndex; i < enabledBatteries.count; i++)
            {
                enabledBatteries.items[i - 1] = enabledBatteries.items[i];
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

    u64 maxJoltage = 0;
    const u8 BASE10 = 10;
    for (u8 i = 0; i < enabledBatteries.count; i++)
    {
        u64 powerOfTen = (u64)powl(BASE10, enabledBatteries.count - i - 1);
        maxJoltage += enabledBatteries.items[i] * powerOfTen;
    }

    daFree(enabledBatteries);
    return maxJoltage;
}

/// @brief Gets the max total Joltage of the given file.\n
/// Joltage is the number you get when enabling enabledBatteriesCount batteries 
/// per bank/line and then concatenating their values/digits.
/// @param filename The filename of the file to get the Joltage of.
/// @param enabledBatteriesCount How many batteries to enable in each bank.
/// @return The max total Joltage of the file.
static u64 GetMaxTotalJoltageOfFile(const char *filename, const u8 enabledBatteriesCount)
{
    FILE *file = fopen(filename, "r");
    char line[LINE_LENGTH] = "";

    u64 totalJoltage = 0;
    while (fgets(line, LINE_LENGTH, file))
    {
        char *currentChar = line;
        u8DA batteries = {0};
        // (The digits end with a newline character or NUL.)
        while (!(*currentChar == '\n' || *currentChar == '\0'))
        {
            u8 digit = (i8)(*currentChar - '0');
            daAppend(batteries, digit);
            currentChar++;
        }
        daCrop(batteries);

        totalJoltage += LargestJoltageInBank(batteries, enabledBatteriesCount);

        daFree(batteries);
    }

    return totalJoltage;
}

static void Part1()
{
    const char *filename = "AoC2025_Day3.txt";
    const u8 enabledBatteriesCount = 2;
    u64 totalJoltage = GetMaxTotalJoltageOfFile(filename, enabledBatteriesCount);
    printf("Part 1: Total Joltage (%u enabled batteries): %zu\n", 
           enabledBatteriesCount, totalJoltage);
}

static void Part2()
{
    const char *filename = "AoC2025_Day3.txt";
    const u8 enabledBatteriesCount = 12;
    u64 totalJoltage = GetMaxTotalJoltageOfFile(filename, enabledBatteriesCount);
    printf("Part 2: Total Joltage (%u enabled batteries): %zu\n",
           enabledBatteriesCount, totalJoltage);
}

void AoC2025_Day3()
{
    Part1();
    Part2();
}
