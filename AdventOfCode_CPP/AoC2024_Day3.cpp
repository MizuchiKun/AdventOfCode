#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;

namespace AoC2024
{
    void Day3()
    {
        /***** I REALLY NEED TO REFACTOR THIS GARBAGE CODE . . . . . . . . . . *****/
        /***** I REALLY NEED TO REFACTOR THIS GARBAGE CODE . . . . . . . . . . *****/
        /***** I REALLY NEED TO REFACTOR THIS GARBAGE CODE . . . . . . . . . . *****/



        /*** Part One ***/
        {
        //// Based on: https://en.cppreference.com/w/cpp/regex/regex_iterator.html#Example

        //// Read lines of the file.
        //ifstream dataFile("AoC2024_Day3.txt");
        //string line;
        //regex mulRegex("mul\\(\\d{1,3},\\d{1,3}\\)");  // Matches mul(X,Y). Where X and Y are 1-3 digit numbers.
        //regex numRegex("\\d{1,3}");  // Matches 1-3 digit numbers.
        //int mulResult = 0;
        //while (getline(dataFile, line))
        //{
        //    // Go through the regex matches in the line.
        //    const auto matchesEnd = std::sregex_iterator();
        //    auto mulMatchesStart = std::sregex_iterator(line.begin(), line.end(), mulRegex);
        //    for (std::sregex_iterator mulIterator = mulMatchesStart; mulIterator != matchesEnd; mulIterator++)
        //    {
        //        // Get the current match.
        //        std::smatch mulMatch = *mulIterator;
        //        string mulStr = mulMatch.str();

        //        // Get number arguments of 'mul()' instruction.
        //        auto numMatchesStart = std::sregex_iterator(mulStr.begin(), mulStr.end(), numRegex);
        //        int arguments[2] = {};
        //        int i = 0;
        //        for (std::sregex_iterator numIterator = numMatchesStart; numIterator != matchesEnd; numIterator++)
        //        {
        //            // Store number argument.
        //            std::smatch numMatch = *numIterator;
        //            arguments[i++] = stoi(numMatch.str());   ///// How to store value in the right index?
        //        }

        //        // Add result of mul() instruction to total result.
        //        mulResult += arguments[0] * arguments[1];
        //    }
        //}

        //cout << "The total of all mul() instructions is: " << mulResult;
        }


        /*** Part Two ***/

        {
        // Read lines of the file.
        ifstream dataFile("AoC2024_Day3.txt");
        string line;
        int mulResult = 0;
        bool mulIsEnabled = true;
        const regex mulExpression(R"#(mul\(\d{1,3},\d{1,3}\))#");  // Matches mul(X,Y). Where X and Y are 1-3 digit numbers.
        const regex numExpression(R"#(\d{1,3})#");  // Matches 1-3 digit numbers.
        const regex doExpression(R"#(do\(\))#");  // Matches "do()".
        const regex dontExpression(R"#(don't\(\))#");  // Matches "don't()".
        while (getline(dataFile, line))
        {
            string remainingLine = line;
            smatch mulMatch;
            smatch doMatch;
            smatch dontMatch;
            while (regex_search(remainingLine, mulMatch, mulExpression))
            {
                // Determine start-indices of matches to figure out which was first.
                int mulMatchStart;
                int doMatchStart;
                int dontMatchStart;
                mulMatchStart = doMatchStart = dontMatchStart = INT_MAX;  // INT_MAX means there was no match.
                bool mulMatchFound = !mulMatch.empty();
                bool doMatchFound = regex_search(remainingLine, doMatch, doExpression);
                bool dontMatchFound = regex_search(remainingLine, dontMatch, dontExpression);
                if (mulMatchFound)
                {
                    bool matchHasPrefix = mulMatch.prefix().matched;
                    if (matchHasPrefix)
                        mulMatchStart = mulMatch.prefix().str().length();
                    else
                        mulMatchStart = 0;
                }
                if (doMatchFound)
                {
                    bool matchHasPrefix = doMatch.prefix().matched;
                    if (matchHasPrefix)
                        doMatchStart = doMatch.prefix().str().length();
                    else
                        doMatchStart = 0;
                }
                if (dontMatchFound)
                {
                    bool matchHasPrefix = dontMatch.prefix().matched;
                    if (matchHasPrefix)
                        dontMatchStart = dontMatch.prefix().str().length();
                    else
                        dontMatchStart = 0;
                }

                bool anyMatchFound = mulMatchFound || doMatchFound || dontMatchFound;
                if (anyMatchFound)
                {
                    int firstMatchStart = min({ mulMatchStart, doMatchStart, dontMatchStart });
                    // Handle only the match/'instruction' which occurs first.
                    if (firstMatchStart == mulMatchStart)
                    {
                        if (mulIsEnabled)
                        {
                            string mulStr = mulMatch.str();

                            // Get number arguments of 'mul()' instruction.
                            auto numMatchesStart = sregex_iterator(mulStr.begin(), mulStr.end(), numExpression);
                            const auto matchesEnd = sregex_iterator();
                            int arguments[2] = {};
                            int i = 0;
                            for (sregex_iterator numIterator = numMatchesStart; numIterator != matchesEnd; numIterator++)
                            {
                                // Store number argument.
                                smatch numMatch = *numIterator;
                                arguments[i++] = stoi(numMatch.str());   // How to store value in the right index? / Is there a better way?
                            }

                            // Add result of mul() instruction to total result.
                            mulResult += arguments[0] * arguments[1];
                        }

                        remainingLine = mulMatch.suffix().str();
                    }
                    else if (firstMatchStart == doMatchStart)
                    {
                        mulIsEnabled = true;

                        remainingLine = doMatch.suffix().str();
                    }
                    else if (firstMatchStart == dontMatchStart)
                    {
                        mulIsEnabled = false;

                        remainingLine = dontMatch.suffix().str();
                    }
                }
            }
        }

        cout << "The total of all enabled mul() instructions is : " << mulResult << endl;
        }
    }
}
