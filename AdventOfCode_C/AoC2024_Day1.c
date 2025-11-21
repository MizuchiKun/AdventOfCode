#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <search.h>  // Why do I allegedly need those?
//#include <malloc.h>
#include "utils.h"

static int CompareInts(const void *a, const void *b)
{
    int intA = *((int*)a);
    int intB = *((int*)b);

    return (intA > intB) - (intA < intB);
}

static void Part1()
{
    char filename[] = "AoC2024_Day1.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file \"%s\" could not be opened/found.", filename);
        return;
    }

    #define LINE_LENGTH 20
    #define LOCATIONS_PER_LIST 1000
    #define LIST_COUNT 2
    char line[LINE_LENGTH];
    int lineIndex = 0;
    int locationIDs[LIST_COUNT][LOCATIONS_PER_LIST] = {0};
    while (fgets(line, LINE_LENGTH, file))
    {
        const char DELIMITER[] = " \n";
        const int BASE = 10;
        char *numberToken = NULL;
        char *savePointer = line;
        int listIndex = 0;
        while ((numberToken = strtok_s(savePointer, DELIMITER, &savePointer)))
        {
            // Technically strtok_s() is somewhat redundant here because strtol() can just extract 
            // the numbers on its own. But I'm gonna leave it as a reference, so I know how to use it, I guess.
            char *end = NULL;
            locationIDs[listIndex++][lineIndex] = strtol(numberToken, &end, BASE);

            if (listIndex >= LIST_COUNT)
                break;
        }

        if (++lineIndex >= LOCATIONS_PER_LIST)  // Is the ++ a war crime, or ok (i.a. regarding readability)?
            break;
    }

    fclose(file);

    for (int i = 0; i < LIST_COUNT; i++)
        qsort(locationIDs[i], LOCATIONS_PER_LIST, sizeof(locationIDs[i][0]), CompareInts);
    
    int totalDistance = 0;
    for (int i = 0; i < LOCATIONS_PER_LIST; i++)
        totalDistance += abs(locationIDs[0][i] - locationIDs[1][i]);

    printf("Part 1: The total distance between the lists is: %d\n", totalDistance);
}

static void Part2()
{
    printf("<Code of part 2 hasn't been implemented yet.>\n");
}

void Day1()
{
    Part1();

    Part2();
}
