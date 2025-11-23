#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "utils.h"

static bool IsReportSafe(int* report, int reportLength, bool useProblemDampener)
{
    bool isSafe = true;

    // (Handle problem dampener stuff in the loop in part 2. 
    //  For now, just ignore that parameter.)
    const bool REPORT_STARTS_INCREASING = report[1] > report[0];
    const int MIN_LEVEL_DIFFERENCE = 1;
    const int MAX_LEVEL_DIFFERENCE = 3;
    for (int i = 1; i < reportLength; i++)
    {
        int levelDifference = abs(report[i] - report[i - 1]);
        bool isIncreasing = report[i] > report[i - 1];
        bool safeLevelDifference = levelDifference >= MIN_LEVEL_DIFFERENCE
                                   && levelDifference <= MAX_LEVEL_DIFFERENCE;
        if (isIncreasing != REPORT_STARTS_INCREASING
            || !safeLevelDifference)
        {
            isSafe = false;
            break;
        }
    }

    return isSafe;
}

static void Part1(bool useProblemDampener)
{
    const char filename[] = "AoC2024_Day2.txt";
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("The file \"%s\" could not be found/opened.\n", filename);
        exit(EXIT_FAILURE);
    }

    #define LINE_LENGTH 30
    #define LINE_COUNT 1000
    const int MAX_LEVEL_COUNT = 10;
    int safeReportsCount = 0;
    char line[LINE_LENGTH] = "";
    while (fgets(line, LINE_LENGTH, file))
    {
        int *report = calloc(MAX_LEVEL_COUNT, sizeof(*report));
        if (report == NULL)
        {
            printf("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }

        const int BASE = 10;
        char *remainingReportStr = line;
        int level = 0;
        int reportLength = 0;
        while (( level = strtol(remainingReportStr, &remainingReportStr, BASE) ))
            report[reportLength++] = level;

        // Resize report to its actual size (/number of elements).
        int *reportBackup = report;  // (To prevent the realloc() warning.)
        report = realloc(report, reportLength * sizeof(*report));
        if (report == NULL)
        {
            printf("Memory allocation failed.");
            free(reportBackup);
            reportBackup = NULL;
            exit(EXIT_FAILURE);
        }

        if (IsReportSafe(report, reportLength, useProblemDampener))
            safeReportsCount += 1;

        free(report);
        report = NULL;
    }

    printf("Part 1: There were a total of %d safe reports.\n", safeReportsCount);
}

static void Part2()
{
    //maybe just call Part1(true)?
    printf("<Code of part 2 hasn't been implemented yet.>\n");
}

void Day2()
{
    bool useProblemDampener = false;
    Part1(useProblemDampener);

    Part2();
}
