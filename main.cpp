#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <conio.h>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

class Tile;
class Board;


class Game
{
public:
    
};


class Random
{
private:
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };


public:

    int generate(int min, int max) {
        std::uniform_int_distribution<int> random{ min, max };
        return random(mersenne);
    }

};

Random random;

class Tile
{
private:
    int m_value;
 

public:
    Tile(int value = 0)
        : m_value{ value }
    {
    }


    int getValue() { return m_value; }
    void setValue(int value) { m_value = value; }

    friend std::ostream& operator<< (std::ostream& out, Tile tile);


};

std::ostream& operator<< (std::ostream& out, Tile tile)
{
    out << tile.getValue();
    return out;
}



class Board
{
private:
    std::vector <Tile> m_grid;

    int leftTile(int i) { return i == 0 ? i : i - 1; }
    int rightTile(int i) { return i == 15 ? i : i + 1; }
    int upTile(int i) { return i < 4 ? i : i - 4; }
    int downTile(int i) { return i > 11 ? i : i + 4; }

public:
    Board(Random random)
    {
        for (int x{ 1 }; x <= 4; ++x)
            for (int y{ 1 }; y <= 4; ++y)
                m_grid.push_back({});

        m_grid.at(random.generate(0, 15)).setValue(2);
        m_grid.at(random.generate(0, 15)).setValue(4);
    }

    std::vector<Tile> getGrid() { return m_grid; }

    bool lose()
    {
        int usedTiles{};
        for (int i{ 0 }; i < 16; ++i)
            if (m_grid.at(i).getValue())
                ++usedTiles;

        if (usedTiles == 16)
            return true;
        return false;
    }


    void spawnTile()
    {
        if (lose()) { 
            std::cout << "Game over" << std::endl;
            return;
        }

        int randomTile{ random.generate(0, 15) };
        while (m_grid.at(randomTile).getValue() != 0)
            randomTile = random.generate(0, 15);
        
        m_grid.at(randomTile).setValue(random.generate(0, 5) ? 2 : 4); // chance to spawn "4" tile is 20%
    }

    void moveLeft()
    {
        for (int i{ 0 }; i < 16; ++i)
        {
            if (m_grid.at(i).getValue() == 0)
                continue;
            while (m_grid.at(leftTile(i)).getValue() == 0 && i % 4 != 0)
            {
                m_grid.at(leftTile(i)).setValue(m_grid.at(i).getValue());
                m_grid.at(i).setValue(0);
                --i;
            }
            if (m_grid.at(i).getValue() == m_grid.at(leftTile(i)).getValue() && i!=0)
            {
                m_grid.at(leftTile(i)).setValue(m_grid.at(leftTile(i)).getValue() * 2);
                m_grid.at(i).setValue(0);
            }            
        }
        spawnTile();
    }

   
    void moveRight()
    {
        for (int i{ 0 }; i < 16; ++i)
        {
            if (m_grid.at(i).getValue() == 0)
                continue;
            while (m_grid.at(rightTile(i)).getValue() == 0 && (i+1)%4 != 0)
            {
                m_grid.at(rightTile(i)).setValue(m_grid.at(i).getValue());
                m_grid.at(i).setValue(0);
                ++i;
            }
            if (m_grid.at(i).getValue() == m_grid.at(rightTile(i)).getValue() && i != 15)
            {
                m_grid.at(rightTile(i)).setValue(m_grid.at(rightTile(i)).getValue() * 2);
                m_grid.at(i).setValue(0);
            }


        }

        spawnTile();
    }

    void moveUp()
    {
        for (int i{ 0 }; i < 16; ++i)
        {
            if (m_grid.at(i).getValue() == 0)
                continue;
            while (m_grid.at(upTile(i)).getValue() == 0 && i >= 4)
            {
                m_grid.at(upTile(i)).setValue(m_grid.at(i).getValue());
                m_grid.at(i).setValue(0);
                i-=4;
            }
            if (m_grid.at(i).getValue() == m_grid.at(upTile(i)).getValue() && i > 3)
            {
                m_grid.at(upTile(i)).setValue(m_grid.at(upTile(i)).getValue() * 2);
                m_grid.at(i).setValue(0);
            }
        }
        spawnTile();
    }

    void moveDown()
    {
        for (int i{ 0 }; i < 16; ++i)
        {
            if (m_grid.at(i).getValue() == 0)
                continue;
            while (m_grid.at(downTile(i)).getValue() == 0 && i <= 11)
            {
                m_grid.at(downTile(i)).setValue(m_grid.at(i).getValue());
                m_grid.at(i).setValue(0);
                i+=4;
            }
            if (m_grid.at(i).getValue() == m_grid.at(downTile(i)).getValue() && i < 11)
            {
                m_grid.at(downTile(i)).setValue(m_grid.at(downTile(i)).getValue() * 2);
                m_grid.at(i).setValue(0);
            }
        }
        spawnTile();
    }


    friend std::ostream& operator<< (std::ostream& out, Board board);

};

std::ostream& operator<< (std::ostream& out, Board board)
{
    out << board.m_grid.at(0) << "  " << board.m_grid.at(1) << "  " << board.m_grid.at(2) << "  " << board.m_grid.at(3) << std::endl
        << board.m_grid.at(4) << "  " << board.m_grid.at(5) << "  " << board.m_grid.at(6) << "  " << board.m_grid.at(7) << std::endl
        << board.m_grid.at(8) << "  " << board.m_grid.at(9) << "  " << board.m_grid.at(10) << "  " << board.m_grid.at(11) << std::endl
        << board.m_grid.at(12) << "  " << board.m_grid.at(13) << "  " << board.m_grid.at(14) << "  " << board.m_grid.at(15) << std::endl;
    return out;
}


int main()
{
    Random random{};
    Board board{ random };


    int c{};
    while (1)
    {
        c = 0;
        switch ((c = _getch())) {
        case KEY_UP:
            board.moveUp();
            break;
        case KEY_DOWN:
            board.moveDown();
            break;
        case KEY_LEFT:
            board.moveLeft();
            break;
        case KEY_RIGHT:
            board.moveRight();
            break;
        default:
            continue;
            break;
        }
        std::cout << board << std::endl;
    }

    return 0;
}
