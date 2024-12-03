#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "vector"

class Code3
{
public:
    int getMultTotal()
    {
        // Read input file
        std::ifstream input("Input/Input_Day_3.txt");
        std::string inputLine;

        std::string testInput = "do()mul(3,3)mul()don't()mul(1,3)";
        std::regex mulPattern(R"((do\(\))|(don't\(\))|(mul\((\d+){1,3}\,(\d+){1,3}\)))");

        int total = 0;
        bool on = true;

        while (std::getline(input, inputLine))
        {
            std::regex_iterator<std::string::iterator> rit(inputLine.begin(), inputLine.end(), mulPattern);
            std::regex_iterator<std::string::iterator> rend;

            while (rit != rend)
            {
                std::string match = rit -> str();

                if (match == "do()")
                {
                    on = true;
                }
                else if (match == "don't()")
                {
                    on = false;
                }
                else if (on)
                {
                    int first = match.find('(');
                    int mid = match.find(',');
                    int last = match.find(')');

                    int a = std::stoi(match.substr(first + 1, mid - first - 1));
                    int b = std::stoi(match.substr(mid + 1, last - mid - 1));

                    total += a * b;
                }

                rit++;
            }
        }

        return total;
    }

private:

};

