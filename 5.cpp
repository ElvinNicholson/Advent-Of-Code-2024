#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Code5
{
public:
    int getMidTotal()
    {
        readInput("Input/Input_Day_5.txt");

        for (std::vector<int> update : updates)
        {
            std::vector<UpdateElement> updateElements;

            for (Rule rule : rules)
            {
                bool _foundX = false;
                bool _foundY = false;

                for (int updateVal : update)
                {
                    if (rule.x == updateVal)
                    {
                        _foundX = true;
                    }
                    else if (rule.y == updateVal)
                    {
                        _foundY = true;
                    }
                }

                if (_foundX & _foundY)
                {
                    // Check if already in updateElements
                    bool xInElem = false;
                    bool yInElem = false;

                    for (int i = 0; i < updateElements.size(); i++)
                    {
                        // Adjust position
                        if (rule.x == updateElements[i].val)
                        {
                            updateElements[i].position--;
                            xInElem = true;
                        }
                        else if (rule.y == updateElements[i].val)
                        {
                            updateElements[i].position++;
                            yInElem = true;
                        }
                    }

                    // Make new elem if not found
                    if (!xInElem)
                    {
                        updateElements.push_back(UpdateElement {rule.x, -1});
                    }
                    if (!yInElem)
                    {
                        updateElements.push_back(UpdateElement {rule.y, 1});
                    }
                }
            }

            // Sort updateElements;
            std::sort(updateElements.begin(), updateElements.end(), &sortUpdateElem);

            bool isOrdered = true;
            for (int i = 0; i < update.size(); i++)
            {
                if (update[i] != updateElements[i].val)
                {
                    isOrdered = false;
                }
            }

            if (!isOrdered)
            {
                midTotal += updateElements[(updateElements.size() - 1) / 2].val;
            }
        }

        return midTotal;
    }

private:
     struct Rule
     {
        int x;
        int y;
     };

    struct UpdateElement
    {
        int val;
        int position;
    };

    std::vector<Rule> rules;
    std::vector<std::vector<int>> updates;
    int midTotal = 0;

    void readInput(const std::string& inputFilePath)
    {
        // Read input file
        std::ifstream input(inputFilePath);
        std::string inputLine;

        bool readingRule = true;

        while (std::getline(input, inputLine))
        {
            if (inputLine.empty())
            {
                readingRule = false;
                continue;
            }

            if (readingRule)
            {
                // Reading Rule
                int separator = inputLine.find('|');

                int x = std::stoi(inputLine.substr(0, separator));
                int y = std::stoi(inputLine.substr(separator + 1));

                Rule rule {};
                rule.x = x;
                rule.y = y;

                rules.push_back(rule);
            }
            else
            {
                // Reading Update
                std::stringstream ss(inputLine);
                std::string s;

                std::vector<int> update;

                while (std::getline(ss, s, ','))
                {
                    //UpdateElement updateElement {};
                    //updateElement.val = std::stoi(s);
                    update.push_back(std::stoi(s));
                }

                updates.push_back(update);
            }
        }
    }

    static bool sortUpdateElem (UpdateElement const& left, UpdateElement const& right)
    {
        return left.position < right.position;
    }
};