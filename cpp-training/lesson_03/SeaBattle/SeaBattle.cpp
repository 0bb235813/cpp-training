#include <iostream>
#include <vector>

using namespace std;

const int Board_Size = 10;

class Pos
{
public:
    Pos() : x(0), y(0) {}
    Pos(int n, int m) : x(n), y(m) {}

    bool operator== (const Pos& other)
    {
        return x == other.x && y == other.y;
    }

    int x, y;
    bool horizontal;
};

class Ship
{
public:

};

class Board
{
public:
    Board() 
    {
        map.resize(10, vector<string>(10, ". "));
    }

    void addShip(const Pos& pos, int size, bool horizontal)
    {
        vector<Pos> p;
        if (horizontal)
        {
            for (int i{}; i < size; ++i) {
                map[pos.x][pos.y+i] = "S ";
                p.push_back(Pos(pos.x, pos.y+i));
            }
        }
        else {
            for (int i{}; i < size; ++i) {
                map[pos.x+i][pos.y] = "S ";
                p.push_back(Pos(pos.x+i, pos.y));
            }
        }
        positions.push_back(p);
    }

    void printBoard()
    {
        cout << "  ";
        for (int i{}; i < 10; ++i)
            cout << i << ' ';
        cout << endl;
        for (int i{}; i < 10; ++i)
        {
            cout << i << ' ';
            for (int j{}; j < 10; ++j)
                cout << map[i][j];

            cout << endl;
        }
    }

    bool shot (const Pos& pos)
    {
        if (map[pos.x][pos.y] == "S ")
        {
            for (int i{}; i < positions.size(); ++i)
            {
                for (auto j : positions[i])
                {
                    if (j == pos)
                        positions.erase(positions.begin()+i);
                }
            }
            map[pos.x][pos.y] = "X ";
            return true;
        }
        return false;
    }

    void printPos()
    {
        for (int i{}; i < positions.size(); ++i)
            for (auto j : positions[i])
                cout << j.x << " " << j.y << endl;
    }

    bool gameOver() { return positions.empty(); }

private:
    vector<vector<string>> map;
    vector<vector<Pos>> positions;
};

int main()
{
    Board player1;
    Board player2;
    player1.printBoard();
    player2.printBoard();

    player1.addShip(Pos(1, 3), 4, true);
    player2.addShip(Pos(4, 8), 3, false);
    cout << endl;
    player1.printBoard();
    player2.printBoard();

    player1.shot(Pos(1, 3));
    player1.shot(Pos(1, 4));
    player1.shot(Pos(1, 5));
    player1.shot(Pos(1, 6));

    player2.shot(Pos(4, 8));
    player2.shot(Pos(5, 8));
    player2.shot(Pos(6, 8));
    cout << endl;
    player1.printBoard();
    player2.printBoard();

    cout << "PLAYER1 OVER\t" << player1.gameOver() << endl;
    cout << "PLAYER2 OVER\t" << player2.gameOver() << endl;
}
