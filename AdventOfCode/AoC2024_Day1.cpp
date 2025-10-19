#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace AoC2024
{
    int Day1()
    {
        /*** Part One ***/

        // Open file with data.
        ifstream dataFile("AoC-2024-01.txt");

        // Read data file and store values in arrays.
        // (Not sure if I should dynamically determine file line count for array length but I guess this works?)
        const int listLength = 1000;
        int list1[listLength];
        int list2[listLength];
        string line = "";
        for (int i = 0; getline(dataFile, line); i++)
        {
            // Create stringstream to extract the 'lines' delimited by the delimiter of the values in dataFile.
            // (Possibly bad solution, just getting "123" "" "" "456" and ignoring the middle bits, but oh well.)
            stringstream stream(line);
            char del = ' ';
            string substring;
            for (int k = 0; getline(stream, substring, del); k++)
            {
                if (k == 0)
                    list1[i] = stoi(substring);
                else if (k == 3)
                    list2[i] = stoi(substring);
            }
        }

        // Close dataFile.
        dataFile.close();

        // Sort lists.
        sort(list1, list1+listLength);
        sort(list2, list2+listLength);

        // Calculate distances between the pairs of the two lists and sum them up.
        int totalDistance = 0;
        for (int i = 0; i < listLength; i++)
        {
            totalDistance += abs(list1[i] - list2[i]);
        }

        // Return total difference.
        cout << "The total distance is: " << totalDistance << '\n';



        /*** Part Two ***/

        int similarityScore = 0;
        for (int i = 0; i < listLength; i++)
        {
            // Count occurences of each value of list1 in list2.
            int count = 0;
            for (int k = 0; k < listLength; k++)
                if (list2[k] == list1[i])
                    count++;

            // Add product of list1 value and count to similarityScore.
            similarityScore += list1[i] * count;
        }

        cout << "The similarity score is: " << similarityScore << '\n';

        return 0;
    }
}
