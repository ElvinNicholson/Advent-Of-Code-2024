#include <iostream>
#include <fstream>
#include <sstream>
#include "vector"

class Code4
{
public:
    int getXmasTotal()
    {
        readInput("Input/Input_Day_4.txt");

        for (int row = 0; row < wordList.size(); row++)
        {
            for (int column = 0; column < wordList[row].size(); column++)
            {
                // Check if A
                if (isChar(wordList[row][column],'A'))
                {
                    checkX_mas(row, column);
                }

//                // Check if X
//                if (isChar(wordList[row][column], 'X'))
//                {
//                    // Check NORTH
//                    checkXmas(row, column, 1, 0);
//                    // Check NORTH EAST
//                    checkXmas(row, column, 1, 1);
//                    // Check EAST
//                    checkXmas(row, column, 0, 1);
//                    // Check SOUTH EAST
//                    checkXmas(row, column, -1, 1);
//                    // Check SOUTH
//                    checkXmas(row, column, -1, 0);
//                    // Check SOUTH WEST
//                    checkXmas(row, column, -1, -1);
//                    // Check WEST
//                    checkXmas(row, column, 0, -1);
//                    // Check NORTH WEST
//                    checkXmas(row, column, 1, -1);
//                }
            }
        }

        return xmasTotal;
    }

private:
    std::vector<std::vector<char>> wordList;
    int xmasTotal = 0;

    void readInput(const std::string& inputFilePath)
    {
        // Read input file
        std::ifstream input(inputFilePath);
        std::string inputLine;

        while (std::getline(input, inputLine))
        {
            std::vector<char> row;

            for (char & y : inputLine)
            {
                // Populate row
                row.push_back(y);
            }

            // Add row to wordList
            wordList.push_back(row);
        }
    }

    static bool isChar(char input, char compare)
    {
        if (input == compare)
        {
            return true;
        }
        return false;
    }

    bool checkDirection(int row, int column, int rowInc, int columnInc, char compare)
    {
        // Check if within bounds
        if ((row + rowInc) >= wordList.size() || (column + columnInc) >= wordList[0].size())
        {
            return false;
        }

        if (isChar(wordList[row + rowInc][column + columnInc], compare))
        {
            return true;
        }

        return false;
    }

    bool checkXmas(int row, int column, int rowInc, int columnInc)
    {
        int _row = 0;
        int _col = 0;

        _row += rowInc;
        _col += columnInc;

        if (checkDirection(row, column, _row, _col, 'M'))
        {
            _row += rowInc;
            _col += columnInc;

            if (checkDirection(row, column, _row, _col, 'A'))
            {
                _row += rowInc;
                _col += columnInc;

                if (checkDirection(row, column, _row, _col, 'S'))
                {
                    xmasTotal++;
                    return true;
                }
            }
        }

        return false;
    }

    bool checkX_mas(int row, int column)
    {
        // 1   2   3
        // 4   5   6
        // 7   8   9

        bool _159 = false;
        bool _357 = false;

        // 1 5 9
        if (checkDirection(row, column, 1, -1, 'M'))
        {
            if (checkDirection(row, column, -1, 1, 'S'))
            {
                _159 = true;
            }
        }
        // 9 5 1
        else if (checkDirection(row, column, -1, 1, 'M'))
        {
            if (checkDirection(row, column, 1, -1, 'S'))
            {
                _159 = true;
            }
        }

        // 3 5 7
        if (checkDirection(row, column, 1, 1, 'M'))
        {
            if (checkDirection(row, column, -1, -1, 'S'))
            {
                _357 = true;
            }
        }
        // 7 5 3
        else if (checkDirection(row, column, -1, -1, 'M'))
        {
            if (checkDirection(row, column, 1, 1, 'S'))
            {
                _357 = true;
            }
        }

        if (_159 & _357)
        {
            xmasTotal++;
            return true;
        }

        return false;
    }
};