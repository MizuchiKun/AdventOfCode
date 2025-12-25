#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AoC2025_Day1.h"
#include "stdint_custom.h"
#include "utils.h"

#define LINE_LENGTH 10

/// @brief Converts the given rotation instruction to the numeric representation of the rotation.
/// 
/// @param instruction A rotation instruction of form "L\d+" or "R\d+".
/// @return The numeric representation of the rotation. E.g.: "L13" = -13, "R4" = +4.
static i32 GetRotation(char *instruction)
{
    const char LEFT_PREFIX = 'L';
    const char RIGHT_PREFIX = 'R';

    char *endPtr;
    const i32 BASE10 = 10;
    char *numberStart = instruction + 1;
    i32 rotation = strtol(numberStart, &endPtr, BASE10);
    
    if (instruction[0] == LEFT_PREFIX)
        rotation *= (-1);

    return rotation;
}

/// @brief Increments the password in-place if the dial poi32s to 0 after the given instruction.
/// 
/// @param instruction A rotation instruction of form "L\d+" or "R\d+".
/// @param password The current password.
/// @param dial The current dial position. Will be changed according to `instruction`.
static void IncrementPasswordOldMethod(char *instruction, i32 *password, i32 *dial)
{
    const i32 TARGET_VALUE = 0;
    const i32 CLICK_COUNT = 100;

    *dial += GetRotation(instruction);
    *dial %= CLICK_COUNT;
    if (*dial == TARGET_VALUE)
        (*password)++;
}

/// @brief Increments the password in-place for every time the dial poi32s to 0, whether during a rotation or at the end.
/// 
/// @param instruction A rotation instruction of form "L\d+" or "R\d+".
/// @param password The current password.
/// @param dial The current dial position. Will be changed according to `instruction`.
static void IncrementPasswordNewMethod(char *instruction, i32 *password, i32 *dial)
{
    const i32 TARGET = 0;
    const i32 CLICK_COUNT = 100;

    i32 rotation = GetRotation(instruction);
    i32 rotationFullCycles = abs(rotation) / CLICK_COUNT;
    i32 rotationRemainder = rotation % CLICK_COUNT;
    i32 dialOld = *dial;
    i32 dialNew = dialOld + rotationRemainder;
    bool dialHitTarget = false;
    if (rotationRemainder < 0)
    {
        if (dialOld > TARGET && dialNew <= TARGET)
            dialHitTarget = true;
        else if (dialOld < TARGET && dialNew <= TARGET - CLICK_COUNT)
            dialHitTarget = true;
    }
    else if (rotationRemainder > 0)
    {
        if (dialOld < TARGET && dialNew >= TARGET)
            dialHitTarget = true;
        else if (dialOld > TARGET && dialNew >= TARGET + CLICK_COUNT)
            dialHitTarget = true;
    }

    if (dialHitTarget)
        (*password)++;
    *password += rotationFullCycles;

    *dial += rotation;
    *dial = (i32)Modulo(*dial, CLICK_COUNT);
}

/// @brief Prcoesses all rotation instructions in the given file and returns the password from it.
/// 
/// @param filename The name of the file with the rotation instructions.
/// @param useNewMethod Whether to use the new or old method.
/// @return The password aka. number of times the vault's dial poi32s at 0 after a rotation.
static i32 RotationsToPassword(char *filename, const bool useNewMethod)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "The file \"%s\" could not be found / opened.\n", filename);
        perror("");
        exit(EXIT_FAILURE);
    }

    i32 password = 0;
    i32 dial = 50;
    char line[LINE_LENGTH] = "";
    while (fgets(line, LINE_LENGTH, file))
    {
        if (useNewMethod)
            IncrementPasswordNewMethod(line, &password, &dial);
        else
            IncrementPasswordOldMethod(line, &password, &dial);
    }

    fclose(file);
    return password;
}

static void Part1()
{
    char filename[] = "AoC2025_Day1.txt";
    i32 password = RotationsToPassword(filename, false);

    printf("Part 1: The password is: %d\n", password);
}

static void Part2()
{
    char filename[] = "AoC2025_Day1.txt";
    i32 password = RotationsToPassword(filename, true);

    printf("Part 2: The password (using new method) is: %d\n", password);
}

void AoC2025_Day1()
{
    Part1();
    Part2();
}
