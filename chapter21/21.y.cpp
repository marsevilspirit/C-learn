#include <iostream>
#include <limits>
#include <numeric>
#include <cassert>
#include "Random.h"

constexpr int g_consoleLines{ 60 };

class Direction{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    Direction(Type type):m_type(type){}

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch(m_type)
        {
            case up:   return Direction{down};
            case down: return Direction{up};
            case left: return Direction{right};
            case right:return Direction{left};
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{up};
    }

    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch(dir.getType())
        {
        case Direction::up:     return (stream << "up");
        case Direction::down:   return (stream << "down");
        case Direction::left:   return (stream << "left");
        case Direction::right:  return (stream << "right");
        default:                return (stream << "unknown direction");
        }
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};

struct Point{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }

    Point getAdjacentPoint(Direction direction) const
    {
        switch(direction.getType())
        {
        case Direction::up:     return {x, y-1};
        case Direction::down:   return {x, y+1};
        case Direction::left:   return {x-1, y};
        case Direction::right:  return {x+1, y};
        }

        return *this;
    }
};

namespace UserInput{

    bool isVaildCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd' 
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine();
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isVaildCommand(ch))
        {
            ch = getCharacter(); 
        }

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
}

class Tile{
private:
    int m_num{0};

public:
    Tile() = default;
    explicit Tile(int num):m_num(num){}

    int getNum() const {return m_num;}

    bool isEmpty() const {return(m_num == 0)?true:false;}

    friend std::ostream& operator<<(std::ostream& out, const Tile& tile)
    {
        if (tile.m_num > 9) // if two digit number
            out << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            out << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            out << "    ";
        return out;
    }
};

class Board{
private:
    static constexpr int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };

public:
    Board() = default;

    static void printEmptyLines(int count)
    {
        for(int i = 0; i < count; i++)
            std::cout<< '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, const Board& board)
    {
        printEmptyLines(g_consoleLines);

        for(int y = 0; y < SIZE; y++)
        {
            for(int x = 0; x < SIZE; x++)
            {
                out << board.m_tiles[y][x];
            }
            out << '\n';
        }

        return out;
    }

    Point getEmptyTilePos() const
    {
        for(int y = 0; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x)
                if(m_tiles[y][x].isEmpty())
                    return {x,y};

        assert(0 && "There is no empty tile in the board!!!");
        return {-1, -1};
    }

    static bool isVaildPoint(Point point)
    {
        return (point.x >= 0 && point.x < SIZE) && (point.y >= 0 && point.y < SIZE);
    }

    void m_tiles_swap(Point p1, Point p2)
    {
        std::swap(m_tiles[p1.y][p1.x], m_tiles[p2.y][p2.x]);
    }

    friend bool operator==(const Board& f1, const Board& f2)
    {
        for(int y = 0; y < SIZE; ++y)
            for(int x =0; x < SIZE; ++x)
                if(f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
                    return false;

        return true;
    }

    bool moveTile(Direction dir)
    {
        Point emptyTile{getEmptyTilePos()};
        Point adj{emptyTile.getAdjacentPoint(-dir)};

        if(!isVaildPoint(adj))
            return false;

        m_tiles_swap(adj, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        static Board s_solved{};
        return s_solved == *this;
    }

    void randomize() 
    {
        for (int i = 0; i < 1000; ++i)
        {
            bool success = moveTile(Direction::getRandomDirection());

            if(!success)
                --i;
        }
    }
};

int main()
{
    Board board{};
    board.randomize();
    std::cout << board;

    while (!board.playerWon())
    {
        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        bool userMoved{ board.moveTile(dir) };
        if (userMoved)
            std::cout << board;
    }

    std::cout << "\n\nYou won!\n\n";
    return 0;
}
