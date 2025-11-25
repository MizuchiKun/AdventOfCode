#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <pcre2posix.h>  // Essentially regex.h.
#include "..\packages\pcre2.10.39.0\include\pcre2posix.h";
#include <malloc.h>
#include <string.h>
#include "utils.h"

#define MUL_MATCH_LENGTH 3
#define DO_MATCH_LENGTH 1
#define DONT_MATCH_LENGTH 1

/// Handles the given sequence of instructions 
/// and returns the total of all mul() instructions.
///
/// @param instructions The string containing the sequence of instructions.
/// @return The total of all mul() instructions in the given string.
static int HandleInstructions(char *instructions)
{
    const char MUL_REGEX_STR[] = "mul\\((\\d{1,3}),(\\d{1,3})\\)";
    const char DO_REGEX_STR[] = "";                            // "do\\(\\)";
    const char DONT_REGEX_STR[] = "don\\'t\\(\\)";
    regex_t mulExpression;
    regex_t doExpression;
    regex_t dontExpression;
    regmatch_t mulMatch[MUL_MATCH_LENGTH];
    regmatch_t doMatch[DO_MATCH_LENGTH];
    regmatch_t dontMatch[DONT_MATCH_LENGTH];

    bool anyRegcompFailed = regcomp(&mulExpression, MUL_REGEX_STR, REG_EXTENDED)
                            || regcomp(&doExpression, DO_REGEX_STR, REG_EXTENDED)
                            || regcomp(&dontExpression, DONT_REGEX_STR, REG_EXTENDED);
    if (anyRegcompFailed)
    {
        perror("A regex compilation failed.");
        exit(EXIT_FAILURE);
    }

    int totalMul = 0;
    char *readHead = instructions;
    while (*readHead != '\0')
    {
        //how regex?
        //
    }
}

static void Part1()
{
    const char filename[] = "AoC2024_Day3.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file \"%s\" could not be found/opened.\n", filename);
        exit(EXIT_FAILURE);
    }

    int totalMul = 0;
    #define LINE_LENGTH 1000
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, file))
    {
        totalMul += HandleInstructions(line);
    }

    fclose(file);

    printf("Part 1: Total of all mul(): %d\n", totalMul);
}

static void Part2()
{
    printf("<Code of part 2 hasn't been implemented yet.>\n");
}

void Day3()
{
    Part1();

    Part2();
}
