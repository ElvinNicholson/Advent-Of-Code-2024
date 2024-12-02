#include <iostream>
#include <fstream>
#include <sstream>
#include "vector"

class Code2
{
public:
    int getSafeReports()
    {
        // Read Input File
        std::ifstream input("Input/Input_Day_2.txt");
        std::string inputLine;
        std::vector<std::vector<int>> reportVector;

        while (std::getline(input, inputLine))
        {
            std::string s;
            std::stringstream ss(inputLine);
            std::vector<int> report;

            while (ss >> s)
            {
                report.push_back(std::stoi(s));
            }

            reportVector.push_back(report);
        }

        // Check if Safe

        int safeReports = 0;

        for (std::vector<int> report : reportVector)
        {
            if (!isReportSafe(calculateDiff(report)))
            {
                // Not Safe
                for (int i = 0; i < report.size(); i++)
                {
                    std::vector<int> corrected = report;
                    corrected.erase(corrected.begin() + i);
                    if (isReportSafe(calculateDiff(corrected)))
                    {
                        safeReports++;
                        break;
                    }
                }
            }
            else
            {
                safeReports++;
            }
        }

        return safeReports;
    }

private:
    static bool isNegative(int num)
    {
        if (num < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static bool isReportSafe(const std::vector<int>& differences)
    {
        int increases = 0;
        int decreases = 0;
        bool _isIncrease = false;

        for (int diff : differences)
        {
            if (diff > 0)
            {
                increases++;
            }
            else if (diff < 0)
            {
                decreases++;
            }
        }

        if (increases > decreases)
        {
            _isIncrease = true;
        }

        for (int diff : differences)
        {
            if (_isIncrease & isNegative(diff) ||
                !_isIncrease & !isNegative(diff) ||
                abs(diff) < 1 ||
                abs(diff) > 3 ||
                diff == 0)
            {
                // Not safe
                return false;
            }
        }
        return true;
    }

    static std::vector<int> calculateDiff(std::vector<int>& report)
    {
        std::vector<int> differences;
        for (int i = 1; i < report.size(); i++)
        {
            int diff = report[i] - report[i - 1];
            differences.push_back(diff);
        }

        return differences;
    }
};

