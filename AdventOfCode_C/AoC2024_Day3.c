#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef PCRE2POSIX_H
    #define PCRE2POSIX_H
    #define PCRE2_STATIC
    #define PCRE2_CODE_UNIT_WIDTH 8
    #include <pcre2posix.h>  // Essentially regex.h.
#endif
#include <malloc.h>
#include <string.h>
#include "utils.h"

#define REGEX_MATCHED 0
#define LINE_LENGTH 3500
#define MUL_MATCH_LENGTH 3
#define DO_MATCH_LENGTH 1
#define DONT_MATCH_LENGTH 1

/// Handles the given sequence of instructions 
/// and returns the total of all mul() instructions.
///
/// @param instructions The string containing the sequence of instructions.
/// @param isMulEnabled Whether mul() instructions are enabled at the start.
/// @param handleDoDont Whether do() and don't() instructions are handled.\n 
///                     These instructions set isMulEnabled to true and false respectively.
/// @return The total of all mul() instructions in the given string.
static int HandleInstructions(char *instructions, bool *isMulEnabled, const bool handleDoDont)
{
    const char MUL_REGEX_STR[] = "mul\\((\\d{1,3}),(\\d{1,3})\\)";
    const char DO_REGEX_STR[] = "do\\(\\)";
    const char DONT_REGEX_STR[] = "don\\'t\\(\\)";
    regex_t mulExpression;
    regex_t doExpression;
    regex_t dontExpression;

    // make regex_t global and put compilation into its own function which only runs when they are uninitialised?
    bool anyRegcompFailed = regcomp(&mulExpression, MUL_REGEX_STR, REG_EXTENDED)
                            || regcomp(&doExpression, DO_REGEX_STR, REG_EXTENDED)
                            || regcomp(&dontExpression, DONT_REGEX_STR, REG_EXTENDED);
    if (anyRegcompFailed)
    {
        perror("A regex compilation failed.");
        exit(EXIT_FAILURE);
    }

    int totalMul = 0;
    const char *readHead = instructions;
    bool hasMoreMulInstructions = true;
    while (hasMoreMulInstructions)
    {
        regmatch_t mulMatch[MUL_MATCH_LENGTH];
        regmatch_t doMatch[DO_MATCH_LENGTH];
        regmatch_t dontMatch[DONT_MATCH_LENGTH];

        int mulReturn = regexec(&mulExpression, readHead, MUL_MATCH_LENGTH, mulMatch, 0);
        int doReturn = regexec(&doExpression, readHead, DO_MATCH_LENGTH, doMatch, 0);
        int dontReturn = regexec(&dontExpression, readHead, DONT_MATCH_LENGTH, dontMatch, 0);

        if (mulReturn == REG_NOMATCH)
        {
            hasMoreMulInstructions = false;
            break;
        }

        bool mulRegexecFailed = !(mulReturn == REGEX_MATCHED || mulReturn == REG_NOMATCH);
        bool doRegexecFailed = !(doReturn == REGEX_MATCHED || doReturn == REG_NOMATCH);
        bool dontRegexecFailed = !(dontReturn == REGEX_MATCHED || dontReturn == REG_NOMATCH);
        if (mulRegexecFailed || doRegexecFailed || dontRegexecFailed)
        {
            perror("A regexec() failed.");
            regfree(&mulExpression);
            regfree(&doExpression);
            regfree(&dontExpression);
            exit(EXIT_FAILURE);
        }

        // (A 'start' value of LINE_LENGTH means there was no match.)
        int mulMatchStart = (mulReturn == REGEX_MATCHED) ? mulMatch->rm_so : LINE_LENGTH;
        int doMatchStart = (doReturn == REGEX_MATCHED) ? doMatch->rm_so : LINE_LENGTH;
        int dontMatchStart = (dontReturn == REGEX_MATCHED) ? dontMatch->rm_so : LINE_LENGTH;

        int firstMatchStart = min(mulMatchStart, min(doMatchStart, dontMatchStart));
        if (mulReturn == REGEX_MATCHED && mulMatch->rm_so == firstMatchStart)
        {
            if (*isMulEnabled)
            {
                const int RADIX = 10;
                char *endPtr = NULL;
                const char *arg1Start = readHead + mulMatch[1].rm_so;
                const char *arg2Start = readHead + mulMatch[2].rm_so;

                int arg1 = strtol(arg1Start, &endPtr, RADIX);
                int arg2 = strtol(arg2Start, &endPtr, RADIX);
                totalMul += arg1 * arg2;
            }

            readHead += mulMatch->rm_eo;
        }
        else if (doReturn == REGEX_MATCHED && doMatch->rm_so == firstMatchStart)
        {
            if (handleDoDont)
                *isMulEnabled = true;
            readHead += doMatch->rm_eo;
        }
        else if (dontReturn == REGEX_MATCHED && dontMatch->rm_so == firstMatchStart)
        {
            if (handleDoDont)
                *isMulEnabled = false;
            readHead += dontMatch->rm_eo;
        }
    }

    regfree(&mulExpression);
    regfree(&doExpression);
    regfree(&dontExpression);

    return totalMul;
}

static int ProcessInstructionsFile(const char *filename, bool handleDoDont)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file \"%s\" could not be found/opened.\n", filename);
        exit(EXIT_FAILURE);
    }

    int totalMul = 0;
    bool isMulEnabled = true;
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, file))
    {
        totalMul += HandleInstructions(line, &isMulEnabled, handleDoDont);
    }

    fclose(file);
    return totalMul;
}

static void Part1()
{
    const char filename[] = "AoC2024_Day3.txt";
    
    int totalMul = ProcessInstructionsFile(filename, false);

    printf("Part 1: Total of all mul(): %d\n", totalMul);
}

static void Part2()
{
    const char filename[] = "AoC2024_Day3.txt";

    int totalMul = ProcessInstructionsFile(filename, true);

    printf("Part 2: Total of all mul() (considering do() and don't()): %d\n", totalMul);
}

void Day3()
{
    Part1();

    Part2();
}
