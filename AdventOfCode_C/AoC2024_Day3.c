#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include "AoC2024_Day3.h"
#include "utils.h"
#include "pcre2posix_custom.h"

#define REGEX_MATCHED 0
#define LINE_LENGTH 3500
#define MUL_MATCH_LENGTH 3
#define DO_MATCH_LENGTH 1
#define DONT_MATCH_LENGTH 1

static regex_t MulExpression = {0};
static regex_t DoExpression = {0};
static regex_t DontExpression = {0};

static void FreeRegexExpressions()
{
    regfree(&MulExpression);
    regfree(&DoExpression);
    regfree(&DontExpression);
}

/// Compiles the regex expressions for mul(), do(), and don't().
///
/// @return Returns true when an error occurred, false otherwise.
static bool CompileRegexExpressions()
{
    bool anyRegcompFailed = false;

    bool ifndefMulExpression = MulExpression.re_match_data == 0;
    if (ifndefMulExpression)
    {
        const char MUL_REGEX_STR[] = "mul\\((\\d{1,3}),(\\d{1,3})\\)";
        const char DO_REGEX_STR[] = "do\\(\\)";
        const char DONT_REGEX_STR[] = "don\\'t\\(\\)";

        anyRegcompFailed = regcomp(&MulExpression, MUL_REGEX_STR, REG_EXTENDED)
                           || regcomp(&DoExpression, DO_REGEX_STR, REG_EXTENDED)
                           || regcomp(&DontExpression, DONT_REGEX_STR, REG_EXTENDED);
    }

    return anyRegcompFailed;
}

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
    bool anyRegcompFailed = CompileRegexExpressions();
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
        // (I guess I could technically put the regexec() stuff into its own function, 
        //  but how to return the individual regexec() return values?)
        regmatch_t mulMatch[MUL_MATCH_LENGTH];
        regmatch_t doMatch[DO_MATCH_LENGTH];
        regmatch_t dontMatch[DONT_MATCH_LENGTH];

        int mulReturn = regexec(&MulExpression, readHead, MUL_MATCH_LENGTH, mulMatch, 0);
        int doReturn = regexec(&DoExpression, readHead, DO_MATCH_LENGTH, doMatch, 0);
        int dontReturn = regexec(&DontExpression, readHead, DONT_MATCH_LENGTH, dontMatch, 0);
        if (mulReturn == REG_NOMATCH)
        {
            hasMoreMulInstructions = false;
            break;
        }

        bool mulMatchFound = mulReturn == REGEX_MATCHED;
        bool doMatchFound = doReturn == REGEX_MATCHED;
        bool dontMatchFound = dontReturn == REGEX_MATCHED;

        bool mulRegexecFailed = !(mulMatchFound || mulReturn == REG_NOMATCH);
        bool doRegexecFailed = !(doMatchFound || doReturn == REG_NOMATCH);
        bool dontRegexecFailed = !(dontMatchFound || dontReturn == REG_NOMATCH);
        if (mulRegexecFailed || doRegexecFailed || dontRegexecFailed)
        {
            perror("A regexec() failed.");
            FreeRegexExpressions();
            exit(EXIT_FAILURE);
        }

        // (Maybe I could put the whole 'finding the first-occurring match' stuff 
        //  into its own function, but that'd have to also make sure that there
        //  actually was a match for the returned value. Because I can't really 
        //  use mulReturn etc. if that just stays in the above 'GetNextMatches' (regexec) function.)
        // A 'start' value of LINE_LENGTH means there was no match.
        int mulMatchStart = mulMatchFound ? mulMatch->rm_so : LINE_LENGTH;
        int doMatchStart = doMatchFound ? doMatch->rm_so : LINE_LENGTH;
        int dontMatchStart = dontMatchFound ? dontMatch->rm_so : LINE_LENGTH;

        int firstMatchStart = min(mulMatchStart, min(doMatchStart, dontMatchStart));
        if (mulMatchFound && mulMatch->rm_so == firstMatchStart)
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
        else if (doMatchFound && doMatch->rm_so == firstMatchStart)
        {
            if (handleDoDont)
                *isMulEnabled = true;
            readHead += doMatch->rm_eo;
        }
        else if (dontMatchFound && dontMatch->rm_so == firstMatchStart)
        {
            if (handleDoDont)
            {
                if (doMatchFound)
                {
                    // Take a shortcut to after the next do(), since all mul()
                    // until then are disable anyway.
                    readHead += doMatch->rm_eo;
                }
                else
                {
                    // If there are no more do(), just stop checking the current string.
                    *isMulEnabled = false;
                    break;
                }
            }
            else
            {
                readHead += dontMatch->rm_eo;
            }
        }
    }

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

    FreeRegexExpressions();
}
