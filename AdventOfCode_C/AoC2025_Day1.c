#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define LINE_LENGTH 10

/// @brief Converts the given rotation instruction to the numeric representation of the rotation.
/// 
/// @param instruction A rotation instruction of form "L\d+" or "R\d+".
/// @return The numeric representation of the rotation. E.g.: "L13" = -13, "R4" = +4.
static int GetRotation(char *instruction)
{
    const char LEFT_PREFIX = 'L';
    const char RIGHT_PREFIX = 'R';

    char *endPtr;
    const int BASE10 = 10;
    char *numberStart = instruction + 1;
    int rotation = strtol(numberStart, &endPtr, BASE10);
    
    if (instruction[0] == LEFT_PREFIX)
        rotation *= (-1);

    return rotation;
}

/// @brief Prcoesses all rotation instructions in the given file and returns the password from it.
/// 
/// @param filename The name of the file with the rotation instructions.
/// @return The password aka. number of times the vault's dial points at 0 after a rotation.
static int RotationsToPassword(char *filename)
{
    const int TARGET_VALUE = 0;
    const int CLICK_COUNT = 100;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "The file \"%s\" could not be found / opened.\n", filename);
        perror("");
        exit(EXIT_FAILURE);
    }

    int password = 0;
    int dial = 50;
    char line[LINE_LENGTH] = "";
    while (fgets(line, LINE_LENGTH, file))
    {
        dial += GetRotation(line);
        dial %= CLICK_COUNT;
        if (dial == TARGET_VALUE)
            password++;
    }

    return password;
}

static void Part1()
{
    char filename[] = "AoC2025_Day1.txt";

    int password = RotationsToPassword(filename);

    printf("Part 1: The password is: %d\n", password);
}

static void Part2()
{
    printf("<Code of part 2 hasn't been implemented yet.>\n");
}

void AoC2025_Day1()
{
    Part1();
    Part2();
}
