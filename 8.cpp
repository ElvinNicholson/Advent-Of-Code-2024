#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Code8
{
public:
    int getTotalAntinode()
    {
        readInput("Input/Input_Day_8.txt");
        antinodeTilemap = tilemap;

        for (const Antenna& a : antennas)
        {
            for (int index = 0; index < a.positions.size(); index++)
            {
                for (int i = 0; i < a.positions.size(); i++)
                {
                    if (index == i)
                    {
                        continue;
                    }

                    Position A = a.positions[index];
                    Position B = a.positions[i];
                    Position dis = {B.x - A.x, B.y - A.y};
                    Position antinodePos = {(dis.x * 2) + A.x, (dis.y * 2) + A.y};

                    setTile(&antinodeTilemap, A, '#');

                    while (isPosWithinBounds(&tilemap, antinodePos))
                    {
                        setTile(&antinodeTilemap, antinodePos, '#');
                        antinodePos = {dis.x + antinodePos.x, dis.y + antinodePos.y};
                    }
                }
            }

        }

        printTilemap(&antinodeTilemap);

        return countCharInTilemap(&antinodeTilemap, '#');
    }

private:
    struct Position
    {
        int x;
        int y;
    };

    struct Antenna
    {
        char frequency;
        std::vector<Position> positions;
    };

    std::vector<std::vector<char>> tilemap;
    std::vector<std::vector<char>> antinodeTilemap;

    std::vector<Antenna> antennas;

    void readInput(const std::string& inputFilePath)
    {
        // Read input file
        std::ifstream input(inputFilePath);
        std::string inputLine;

        int y = 0;
        while (std::getline(input, inputLine))
        {
            std::vector<char> tileRow;
            int x = 0;

            for (char& c : inputLine)
            {
                if (c != '.')
                {
                    bool foundFrequency = false;
                    for (Antenna& antenna : antennas)
                    {
                        if (antenna.frequency == c)
                        {
                            antenna.positions.push_back(Position{x, y});
                            foundFrequency = true;
                        }
                    }

                    if (!foundFrequency)
                    {
                        // New frequency
                        Antenna newAntenna;
                        newAntenna.frequency = c;
                        newAntenna.positions.push_back(Position{x, y});
                        antennas.push_back(newAntenna);
                    }
                }

                tileRow.push_back(c);
                x++;
            }

            tilemap.push_back(tileRow);
            y++;
        }
    }

    void setTile(std::vector<std::vector<char>> *_tilemap, Position pos, char c)
    {
        if (pos.x >= _tilemap[0].size() || pos.y >= _tilemap->size() || pos.x < 0 || pos.y < 0)
        {
            return;
        }

        _tilemap->at(pos.y)[pos.x] = c;
    }

    void printTilemap(std::vector<std::vector<char>> *_tilemap)
    {
        for (const std::vector<char>& tileRow : *_tilemap)
        {
            for (char c: tileRow)
            {
                std::cout << c;
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    int countCharInTilemap(std::vector<std::vector<char>> *_tilemap, char c)
    {
        int count = 0;

        for (const std::vector<char>& y : *_tilemap)
        {
            for (char x : y)
            {
                if (x == c)
                {
                    count++;
                }
            }
        }

        return count;
    }

    bool isPosWithinBounds(std::vector<std::vector<char>> *_tilemap, Position pos)
    {
        if (pos.x >= _tilemap[0].size() || pos.y >= _tilemap->size() || pos.x < 0 || pos.y < 0)
        {
            return false;
        }

        return true;
    }
};

