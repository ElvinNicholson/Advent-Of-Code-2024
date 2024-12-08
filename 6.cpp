#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Code6
{
public:
    int getTotalMovement()
    {
        readInput("Input/Input_Day_6.txt");

        while (!guardIsOutOfBounds)
        {
            moveGuard();
        }

        //totalMovement = countCharInTilemap('X');

        //printTilemap(&tilemap);

        totalLoop = loopWallPos.size();

        return totalLoop;
    }

private:
    struct Position
    {
        int x = 0;
        int y = 0;
    };

    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    enum TileType
    {
        WALL,
        NORMAL,
        OUT_OF_BOUNDS,
        TURN
    };

    std::vector<std::vector<char>> predictionTilemap;
    std::vector<std::vector<char>> cleanTilemap;
    std::vector<std::vector<char>> tilemap;
    std::vector<Position> loopWallPos;
    Position guardPos;
    Position guardStartPos;
    Direction guardDir = UP;
    bool guardIsOutOfBounds = false;
    int totalMovement = 0;
    int totalLoop = 0;

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
                if (c == '^')
                {
                    guardPos = Position{x, y};
                    guardStartPos = guardPos;
                }

                tileRow.push_back(c);
                x++;
            }

            tilemap.push_back(tileRow);
            y++;
        }

        cleanTilemap = tilemap;
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

    void setTile(std::vector<std::vector<char>> *_tilemap, Position pos, char c)
    {
        _tilemap->at(pos.y)[pos.x] = c;
    }

    bool isTile(std::vector<std::vector<char>> *_tilemap, Position pos, char c)
    {
        // Out of bounds
        if (pos.x >= _tilemap[0].size() || pos.y >= _tilemap->size() || pos.x < 0 || pos.y < 0)
        {
            return false;
        }

        if (_tilemap->at(pos.y)[pos.x] == c)
        {
            return true;
        }
        return false;
    }

    TileType getTileType(std::vector<std::vector<char>> *_tilemap, Position pos)
    {
        if (pos.x >= tilemap[0].size() || pos.y >= tilemap.size() || pos.x < 0 || pos.y < 0)
        {
            // Out of bounds
            return OUT_OF_BOUNDS;
        }

        if (_tilemap->at(pos.y)[pos.x] == '#')
        {
            // Is wall
            return WALL;
        }

        if (_tilemap->at(pos.y)[pos.x] == '+')
        {
            // Is wall
            return TURN;
        }

        return NORMAL;
    }

    void moveGuard()
    {
        TileType nextTile;
        Position nextPos;

        switch (guardDir)
        {
            case UP:
                checkLoop(guardPos, UP);

                nextPos = {guardPos.x, guardPos.y - 1};
                nextTile = getTileType(&tilemap, nextPos);
                solveGuardMovement(&tilemap, nextTile, nextPos, RIGHT, '^', &guardPos, &guardDir, &guardIsOutOfBounds);
                break;

            case RIGHT:
                checkLoop(guardPos, RIGHT);

                nextPos = {guardPos.x + 1, guardPos.y};
                nextTile = getTileType(&tilemap, nextPos);
                solveGuardMovement(&tilemap, nextTile, nextPos, DOWN, '>', &guardPos, &guardDir, &guardIsOutOfBounds);
                break;

            case DOWN:
                checkLoop(guardPos, DOWN);

                nextPos = {guardPos.x, guardPos.y + 1};
                nextTile = getTileType(&tilemap, nextPos);
                solveGuardMovement(&tilemap, nextTile, nextPos, LEFT, 'v', &guardPos, &guardDir, &guardIsOutOfBounds);
                break;

            case LEFT:
                checkLoop(guardPos, LEFT);

                nextPos = {guardPos.x - 1, guardPos.y};
                nextTile = getTileType(&tilemap, nextPos);
                solveGuardMovement(&tilemap, nextTile, nextPos, UP, '<', &guardPos, &guardDir, &guardIsOutOfBounds);
                break;
        }
    }

    bool simulateNewWall(std::vector<std::vector<char>> *_tilemap)
    {
        bool guardOOB = false;
        Position _guardPos = guardStartPos;
        Direction _guardDir = UP;
        TileType lastTile = NORMAL;

        while (!guardOOB)
        {
            TileType nextTile;
            Position nextPos;

            switch (_guardDir)
            {
                case UP:
                    nextPos = {_guardPos.x, _guardPos.y - 1};
                    nextTile = getTileType(_tilemap, nextPos);
                    solveGuardMovement(_tilemap, nextTile, nextPos, RIGHT, '^', &_guardPos, &_guardDir, &guardOOB);
                    break;

                case RIGHT:
                    nextPos = {_guardPos.x + 1, _guardPos.y};
                    nextTile = getTileType(_tilemap, nextPos);
                    solveGuardMovement(_tilemap, nextTile, nextPos, DOWN, '>', &_guardPos, &_guardDir, &guardOOB);
                    break;

                case DOWN:
                    nextPos = {_guardPos.x, _guardPos.y + 1};
                    nextTile = getTileType(_tilemap, nextPos);
                    solveGuardMovement(_tilemap, nextTile, nextPos, LEFT, 'v', &_guardPos, &_guardDir, &guardOOB);
                    break;

                case LEFT:
                    nextPos = {_guardPos.x - 1, _guardPos.y};
                    nextTile = getTileType(_tilemap, nextPos);
                    solveGuardMovement(_tilemap, nextTile, nextPos, UP, '<', &_guardPos, &_guardDir, &guardOOB);
                    break;
            }

            if (nextTile == WALL & lastTile == TURN)
            {
                //printTilemap(_tilemap);
                return true;
            }

            lastTile = nextTile;
        }

        return false;
    }

    void solveGuardMovement(std::vector<std::vector<char>> *_tilemap, TileType nextTile, Position nextPos, Direction turnDir, char c, Position *guardPosRef, Direction *guardDirRef, bool *oob)
    {
        switch (nextTile)
        {
            case WALL:
                // Turn
                *guardDirRef = turnDir;
                setTile(_tilemap, *guardPosRef, '+');
                break;

            case TURN:
            case NORMAL:
                // Move there
//                if (!isTile(_tilemap, *guardPosRef, '+'))
//                {
//                    setTile(_tilemap, *guardPosRef, 'X');
//                }
                *guardPosRef = nextPos;
                break;

            case OUT_OF_BOUNDS:
                // End
                *oob = true;
//                setTile(_tilemap, *guardPosRef, 'X');
                break;
        }
    }

    int countCharInTilemap(char c)
    {
        int count = 0;

        for (const std::vector<char>& y : tilemap)
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

    bool predictLoop(Position _guardPos, Direction dir)
    {
        // Place Wall
        Position newWallPos;

        switch (dir)
        {
            case UP:
                newWallPos = Position{_guardPos.x, _guardPos.y - 1};
                break;

            case RIGHT:
                newWallPos = Position{_guardPos.x + 1, _guardPos.y};
                break;

            case DOWN:
                newWallPos = Position{_guardPos.x, _guardPos.y + 1};
                break;

            case LEFT:
                newWallPos = Position{_guardPos.x - 1, _guardPos.y};
                break;
        }

        if (getTileType(&cleanTilemap, newWallPos) != NORMAL)
        {
            return false;
        }

        predictionTilemap = cleanTilemap;
        setTile(&predictionTilemap, newWallPos, '#');

        // Start simulation with new wall

        bool result = simulateNewWall(&predictionTilemap);

        if (result)
        {
            isPosInVector(newWallPos);
        }

        return result;
    }

    bool checkLoop(Position pos, Direction dir)
    {
        switch (dir)
        {
            case UP:
                // Check RIGHT
                for (int i = pos.x + 1; i < tilemap[0].size(); i++)
                {
                    if (isTile(&tilemap, Position{i, pos.y}, '#'))
                    {
                        if (predictLoop(pos, dir))
                        {
                            return true;
                        }
                        return false;
                    }
                }
                break;

            case RIGHT:
                // Check DOWN
                for (int i = pos.y + 1; i < tilemap.size(); i++)
                {
                    if (isTile(&tilemap, Position{pos.x, i}, '#'))
                    {
                        if (predictLoop(pos, dir))
                        {
                            return true;
                        }
                        return false;
                    }
                }
                break;

            case DOWN:
                // Check LEFT
                for (int i = pos.x - 1; i >= 0; i--)
                {
                    if (isTile(&tilemap, Position{i, pos.y}, '#'))
                    {
                        if (predictLoop(pos, dir))
                        {
                            return true;
                        }
                        return false;
                    }
                }
                break;

            case LEFT:
                // Check UP
                for (int i = pos.y - 1; i >= 0; i--)
                {
                    if (isTile(&tilemap, Position{pos.x, i}, '#'))
                    {
                        if (predictLoop(pos, dir))
                        {
                            return true;
                        }
                        return false;
                    }
                }
                break;
        }

        return false;
    }

    bool isPosInVector(Position pos)
    {
        for (Position wallPos : loopWallPos)
        {
            if (wallPos.x == pos.x & wallPos.y == pos.y)
            {
                return true;
            }
        }

        loopWallPos.push_back(pos);
        return false;
    }
};