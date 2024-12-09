#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Code7
{
public:
    long long int getTotal()
    {
        readInput("Input/Input_Day_7.txt");

        for (int i = 0; i < results.size(); i++)
        {
            solutionsFound = 0;

            solveEquation(results[i], equations[i][0], i, 1);

            if (solutionsFound > 0)
            {
                total += results[i];
            }
        }

        return total;
    }

private:
    std::vector<long long int> results;
    std::vector<std::vector<int>> equations;

    long long int total = 0;
    int solutionsFound = 0;

    void readInput(const std::string& inputFilePath)
    {
        // Read input file
        std::ifstream input(inputFilePath);
        std::string inputLine;

        while (std::getline(input, inputLine))
        {
            int separator = inputLine.find(':');
            results.push_back(std::stoll(inputLine.substr(0, separator)));

            std::stringstream ss(inputLine.substr(separator + 1));
            std::string s;
            std::vector<int> equation;

            while (ss >> s)
            {
                equation.push_back(std::stoi(s));
            }

            equations.push_back(equation);
        }
    }

    void solveEquation(long long int finalResult, long long int currentResult, int eqIndex, int index)
    {
        if (index < equations[eqIndex].size())
        {
            solveEquation(finalResult, currentResult * equations[eqIndex][index], eqIndex, index + 1);
            solveEquation(finalResult, currentResult + equations[eqIndex][index], eqIndex, index + 1);
            solveEquation(finalResult, std::stoll(std::to_string(currentResult) + std::to_string(equations[eqIndex][index])), eqIndex, index + 1);
        }
        else
        {
            if (finalResult == currentResult)
            {
                solutionsFound++;
            }
        }
    }
};

