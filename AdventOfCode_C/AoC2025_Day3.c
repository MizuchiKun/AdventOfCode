#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "AoC2025_Day3.h"
#include "utils.h"

#define LINE_LENGTH 110

static uint32_t LargestJoltageInBank(uint8_t *batteries, const uint8_t batteryCount)
{
    if (batteryCount < 2)
    {
        printf("Battery array / bank must have at least 2 elements.");
        exit(EXIT_FAILURE);
    }
    uint8_t firstDigit = batteries[0];
    uint8_t secondDigit = batteries[1];

    for (uint8_t i = 2; i < batteryCount; i++)
    {
        uint8_t newDigit = batteries[i];

        // Let's call the first, second, and 'new' digits 'A', 'B', and 'N'.
        if (secondDigit > firstDigit)
        {
            // If B > A, store B in A, and store whichever-value-N-is in B.
            // This is because any value of 'B-ty something' will always 
            //   be greater than a value of 'A-ty something', when B > A.
            // E.g.: batteries = {781} => A=7, B=8, N=1;  A=8, B=1;  81 > 78.
            // (Maybe there's a better explanation/wording, but oh well . . .)
            firstDigit = secondDigit;
            secondDigit = newDigit;
        }
        else if (newDigit > secondDigit)
        {
            // If N > B, store N in B.
            // So just update B with a larger value. Not sure what else to say.
            // This might cause the above case in the next iteration.
            secondDigit = newDigit;
        }
    }

    uint32_t maxJoltage = 10 * firstDigit + secondDigit;
    return maxJoltage;
}

static uint32_t GetTotalJoltageOfFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[LINE_LENGTH] = "";

    uint32_t totalJoltage = 0;
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

        totalJoltage += LargestJoltageInBank(batteries, batteryCount);

        free(batteries);
    }

    return totalJoltage;
}

static void Part1()
{
    const char *filename = "AoC2025_Day3.txt";
    uint32_t totalJoltage = GetTotalJoltageOfFile(filename);
    printf("Part 1: Total Joltage: %d\n", totalJoltage);
}

static void Part2()
{
    printf("Part 2: <not implemented yet>\n");
}

void AoC2025_Day3()
{
    Part1();
    Part2();
}
