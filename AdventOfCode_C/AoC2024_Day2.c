#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include "AoC2024_Day2.h"
#include "utils.h"

static bool IsReportSafe(int *report, int reportLength)
{
    bool isSafe = true;

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

static bool IsReportSafeProblemDampener(int *report, int reportLength)
{
    if (IsReportSafe(report, reportLength))
        return true;  // Don't bother checking 'problem dampener' stuff.

    const int SUBREPORT_LENGTH = reportLength - 1;
    bool isSafe = false;

    for (int preGapCount = 0; preGapCount < reportLength; preGapCount++)
    {
        int *subreport = (int*)SafeCalloc(SUBREPORT_LENGTH, sizeof(*subreport));

        const int bytesPreGap = preGapCount * sizeof(*subreport);
        const int bytesPostGap = (SUBREPORT_LENGTH - preGapCount) 
                                 * sizeof(*subreport);
        memcpy(subreport, report, bytesPreGap);
        memcpy(subreport + preGapCount, report + preGapCount + 1, bytesPostGap);

        if (IsReportSafe(subreport, SUBREPORT_LENGTH))
        {
            isSafe = true;
            break;
        }

        free(subreport);
    }

    return isSafe;
}

static int CountSafeReports(const char filename[], bool useProblemDampener)
{
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
        int *report = (int*)SafeCalloc(MAX_LEVEL_COUNT, sizeof(*report));

        const int BASE = 10;
        char *remainingReportStr = line;
        int level = 0;
        int reportLength = 0;
        while ((level = strtol(remainingReportStr, &remainingReportStr, BASE)))
            report[reportLength++] = level;

        // Resize report to its actual size (/number of elements).
        report = SafeRealloc(report, reportLength * sizeof(*report));

        bool reportIsSafe = useProblemDampener
                            ? IsReportSafeProblemDampener(report, reportLength)
                            : IsReportSafe(report, reportLength);
        if (reportIsSafe)
            safeReportsCount += 1;

        free(report);
        report = NULL;
    }

    return safeReportsCount;
}

static void Part1()
{
    int safeReportsCount = CountSafeReports("AoC2024_Day2.txt", false);

    printf("Part 1: Safe reports without problem dampener: %d\n", safeReportsCount);
}

static void Part2()
{
    int safeReportsCount = CountSafeReports("AoC2024_Day2.txt", true);

    printf("Part 2: Safe reports with problem dampener: %d\n", safeReportsCount);
}

void Day2()
{
    Part1();
    Part2();
}
