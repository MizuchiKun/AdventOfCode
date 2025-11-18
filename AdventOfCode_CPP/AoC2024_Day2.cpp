#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

namespace AoC2024
{
    // Returns if the given report (vector<int> of levels) is safe.
    static bool isReportSafe(vector<int> levels)
    {
        // Check if the report is safe.
        bool isReportSafe = true;  // Safe until proven otherwise.
        bool startedIncreasing = levels[1] > levels[0];
        int level, prevLevel;
        for (int i = 1; i < levels.size(); i++)
        {
            // Check if level 'transition' is unsafe.
            level = levels[i];
            prevLevel = levels[i - 1];
            bool stillIncreasing = level > prevLevel;
            int levelDifference = abs(level - prevLevel);
            if (!((startedIncreasing == stillIncreasing)
                && (levelDifference >= 1 && levelDifference <= 3)))
            {
                isReportSafe = false;
            }
        }

        return isReportSafe;
    }


    int Day2(bool useProblemDampener)
    {
        /*** Part Two ***/

        // Open file and process 'reports'/lines.
        int safeReports = 0;
        ifstream dataFile("AoC2024_Day2.txt");
        string report;
        while (getline(dataFile, report))
        {
            vector<int> levels;
            // Process report into array.
            stringstream stream(report);
            string levelStr;
            char sep = ' ';
            while (getline(stream, levelStr, sep))
            {
                levels.push_back(stoi(levelStr));
            }

            // Increase counter if the report is safe.
            if (isReportSafe(levels))
                safeReports++;
            else if (useProblemDampener)
            {
                // Try if it's safe after using 'problem dampener'/removing a specific level.
                vector<int> dampenedLevels;
                for (int i = 0; i < levels.size(); i++)
                {
                    // Copy and remove i-th element.
                    dampenedLevels = levels;
                    dampenedLevels.erase(dampenedLevels.begin() + i);

                    // Check if the report is safe without that level.
                    if (isReportSafe(dampenedLevels))
                    {
                        safeReports++;
                        break;
                    }
                }
            }
        }

        // Output number of safe reports.
        cout << "Number of safe reports: " << safeReports << "\n";

        return 0;
    }
}
