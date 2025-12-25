#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AoC2024_Day2.h"
#include "DynamicArray.h"
#include "malloc_custom.h"
#include "stdint_custom.h"
#include "utils.h"

static bool IsReportSafe(i32DA report)
{
    bool isSafe = true;

    const bool REPORT_STARTS_INCREASING = report.items[1] > report.items[0];
    const i32 MIN_LEVEL_DIFFERENCE = 1;
    const i32 MAX_LEVEL_DIFFERENCE = 3;
    for (u32 i = 1; i < report.count; i++)
    {
        i32 levelDifference = abs(report.items[i] - report.items[i - 1]);
        bool isIncreasing = report.items[i] > report.items[i - 1];
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

static bool IsReportSafeProblemDampener(i32DA report)
{
    if (IsReportSafe(report))
        return true;  // Don't bother checking 'problem dampener' stuff.

    const u32 SUBREPORT_LENGTH = report.count - 1;
    bool isSafe = false;

    for (u32 preGapCount = 0; preGapCount < report.count; preGapCount++)
    {
        i32DA subreport = {
            .items = SafeCalloc(SUBREPORT_LENGTH, sizeof(*subreport.items)),
            .count = SUBREPORT_LENGTH,
            .capacity = SUBREPORT_LENGTH
        };

        const i32 bytesPreGap = preGapCount * sizeof(*subreport.items);
        const i32 bytesPostGap = (u64)(SUBREPORT_LENGTH - preGapCount) 
                                 * sizeof(*subreport.items);
        memcpy(subreport.items, report.items, bytesPreGap);
        memcpy(subreport.items + preGapCount, report.items + preGapCount + 1, bytesPostGap);

        if (IsReportSafe(subreport))
        {
            isSafe = true;
            break;
        }

        daFree(subreport);
    }

    return isSafe;
}

static i32 CountSafeReports(const char filename[], bool useProblemDampener)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("The file \"%s\" could not be found/opened.\n", filename);
        exit(EXIT_FAILURE);
    }

    #define LINE_LENGTH 30
    #define LINE_COUNT 1000
    const i32 MAX_LEVEL_COUNT = 10;
    i32 safeReportsCount = 0;
    char line[LINE_LENGTH] = "";
    while (fgets(line, LINE_LENGTH, file))
    {
        i32DA report = {0};

        const i32 BASE = 10;
        char *remainingReportStr = line;
        i32 level = 0;
        while ((level = strtol(remainingReportStr, &remainingReportStr, BASE)))
            daAppend(report, level);
        daCrop(report);

        bool reportIsSafe = useProblemDampener
                            ? IsReportSafeProblemDampener(report)
                            : IsReportSafe(report);
        if (reportIsSafe)
            safeReportsCount += 1;

        daFree(report);
    }

    return safeReportsCount;
}

static void Part1()
{
    i32 safeReportsCount = CountSafeReports("AoC2024_Day2.txt", false);

    printf("Part 1: Safe reports without problem dampener: %d\n", safeReportsCount);
}

static void Part2()
{
    i32 safeReportsCount = CountSafeReports("AoC2024_Day2.txt", true);

    printf("Part 2: Safe reports with problem dampener: %d\n", safeReportsCount);
}

void AoC2024_Day2()
{
    Part1();
    Part2();
}
