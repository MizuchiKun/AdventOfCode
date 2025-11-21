#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static int CompareInts(const void *a, const void *b)
{
    int intA = *((int*)a);
    int intB = *((int*)b);

    return (intA > intB) - (intA < intB);
}

static int** ExtractLocationIDs(int *listCount, int *locationsPerList)
{
    char filename[] = "AoC2024_Day1.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file \"%s\" could not be opened/found.", filename);
        return NULL;
    }

    #define LINE_LENGTH 20
    const int LIST_COUNT = 2;
    const int LOCATIONS_PER_LIST = 1000;
    *listCount = LIST_COUNT;
    *locationsPerList = LOCATIONS_PER_LIST;
    char line[LINE_LENGTH];
    int lineIndex = 0;
    int **locationIDs = Create2DIntArray(LIST_COUNT, LOCATIONS_PER_LIST);
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

    return locationIDs;
}


static void Part1()
{
    int LIST_COUNT = 0;
    int LOCATIONS_PER_LIST = 0;
    int **locationIDs = ExtractLocationIDs(&LIST_COUNT, &LOCATIONS_PER_LIST);

    for (int i = 0; i < LIST_COUNT; i++)
        qsort(locationIDs[i], LOCATIONS_PER_LIST, sizeof(locationIDs[i][0]), CompareInts);
    
    int totalDistance = 0;
    for (int i = 0; i < LOCATIONS_PER_LIST; i++)
        totalDistance += abs(locationIDs[0][i] - locationIDs[1][i]);

    printf("Part 1: The total distance between the lists is: %d\n", totalDistance);

    Destroy2DIntArray(locationIDs);
}

static void Part2()
{
    int LIST_COUNT = 0;
    int LOCATIONS_PER_LIST = 0;
    int **locationIDs = ExtractLocationIDs(&LIST_COUNT, &LOCATIONS_PER_LIST);

    for (int i = 0; i < LIST_COUNT; i++)
        qsort(locationIDs[i], LOCATIONS_PER_LIST, sizeof(locationIDs[i][0]), CompareInts);

    int similarityScore = 0;
    for (int i = 0; i < LOCATIONS_PER_LIST; i++)
    {
        int target = locationIDs[0][i];
        similarityScore += target * CountFrequency(locationIDs[1], LOCATIONS_PER_LIST, target);
    }

    printf("Part 2: The similarity score of the lists is: %d\n", similarityScore);

    Destroy2DIntArray(locationIDs);
}

void Day1()
{
    Part1();

    Part2();
}
