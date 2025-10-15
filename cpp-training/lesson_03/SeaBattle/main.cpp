#include <algorithm>
#include <iostream>
#include <stdexcept>
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

    char x;
    int y;
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
        map.resize(10, vector<string>(10, "  "));
    }

    void addShip(const Pos& pos, int size, bool horizontal)
    {
        if (!coordinatesCorrect(pos, size, horizontal)) {
            cout << "Incorrect coordinate" << endl;
            return;
        }
        vector<Pos> p;
        vector<bool> b;
        if (horizontal)
        {
            for (int i{}; i < size; ++i) {
                map[pos.x-65][pos.y+i-1] = "S ";
                p.push_back(Pos(pos.x, pos.y+i));
                b.push_back(true);
            }
        }
        else {
            for (int i{}; i < size; ++i) {
                map[pos.x+i-65][pos.y-1] = "S ";
                p.push_back(Pos(pos.x+i, pos.y));
                b.push_back(true);
            }
        }
        positions.push_back(p);
        boolPos.push_back(b);
    }

    void printBoard()
    {
        cout << "  ";
        for (int i = 1; i < 11; ++i)
            cout << i << ' ';
        cout << endl;
        for (int i{}; i < 10; ++i)
        {
            cout << (char)(i+65) << ' ';
            for (int j{}; j < 10; ++j)
                cout << map[i][j];

            cout << endl;
        }
    }

    bool shot (const Pos pos)
    {
        if (map[pos.x-65][pos.y-1] == "S ")
        {
            regShot(pos);
            map[pos.x-65][pos.y-1] = "X ";
            return true;
        }
        else if (map[pos.x-65][pos.y-1] == "  ")
            map[pos.x-65][pos.y-1] = "O ";
        return false;
    }


    void printPos()
    {
        for (int i{}; i < positions.size(); ++i)
            for (auto j : positions[i])
                cout << j.x-65 << " " << j.y << endl;
    }

    bool gameOver() { return positions.empty(); }

private:
    vector<vector<string>> map;
    vector<vector<Pos>> positions;
    vector<vector<bool>> boolPos;
    void regShot(const Pos pos)
    {
        //for (int i{}; i < positions.size(); ++i) {
        //    for (auto j = positions[i].begin(); j != positions[i].end();) {
        //        if (*j == pos) {
        //            j = positions[i].erase(j);
        //            if (positions[i].empty()) positions.erase(positions.begin()+i);
        //            break;
        //        }
        //        else ++j;
        //    }
        //}

        for (int i{}; i < positions.size(); ++i) {
            for (int j{}; j < positions[i].size(); ++j) {
                if (positions[i][j] == pos) {
                    boolPos[i][j] = false;
                    if (*max_element(boolPos[i].begin(), boolPos[i].end()) == 0) shipDrowned(i);
                    break;
                }
            }
        }
    }

    void shipDrowned(int pos)
    {
        if (positions[pos][0].x == positions[pos][1].x) {
            for (int i = positions[pos][0].y-2; i < positions[pos][0].y + (int)positions[pos].size(); ++i) {
                for (int j = positions[pos][0].x-1-65; j <= positions[pos][0].x+1-65; ++j) {
                    if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[j][i] != "X ") {
                        map[j][i] = ". ";
                    }
                }
            }
        }
        else if (positions[pos][0].x != positions[pos][1].x) {
            for (int i = positions[pos][0].x-1-65; i < positions[pos][0].x-65 + positions[pos].size()+1; ++i) {
                for (int j = positions[pos][0].y-2; j <= positions[pos][0].y; ++j) {
                    if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[i][j] != "X ")
                        map[i][j] = ". ";
                }
            }
        }
        positions.erase(positions.begin()+pos);
    }

    bool coordinatesCorrect(const Pos pos, int size, bool horizontal)
    {
        if (size > 4 || size < 0) return false;
        if (!horizontal)
        {
            if (pos.x-65 < 0 || pos.x-65+size > 10)
                return false;
            for (int i = pos.x-1-65; i < pos.x+size+1-65; ++i) {
                for (int j = pos.y-2; j < pos.y+1; ++j) {
                    if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                        if (map[i][j] == "S ") return false;
                    }
                }
            }
        }
        else {
            if (pos.y < 0 || pos.y-1+size > 10)
                return false;
            for (int i = pos.y-2; i < pos.y+size; ++i) {
                for (int j = pos.x-1-65; j < pos.x+2-65; ++j) {
                    if (i >= 0 && i < 10 && j >= 0 && j < 10)
                        if (map[j][i] == "S ") return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    Board player1;
    Board player2;
    player1.printBoard();
    player2.printBoard();

    player1.addShip(Pos('A', 1), 4, true);
    player2.addShip(Pos('H', 3), 3, true);
    player2.addShip(Pos('E', 8), 3, false);
    player1.addShip(Pos('C', 2), 3, true);
    cout << endl;
    player1.printBoard();
    player2.printBoard();


    player1.shot(Pos('A', 1));
    player1.shot(Pos('A', 2));
    player1.shot(Pos('A', 3));
    player1.shot(Pos('A', 4));

    player2.shot(Pos('H', 3));
    player2.shot(Pos('H', 4));
    player2.shot(Pos('H', 5));

    player1.shot(Pos('C', 2));
    player1.shot(Pos('C', 3));
    player1.shot(Pos('C', 4));

    player2.shot(Pos('E', 8));
    player2.shot(Pos('F', 8));
    player2.shot(Pos('G', 8));
    cout << endl;
    player1.printBoard();
    player2.printBoard();

    cout << "PLAYER1 OVER\t" << player1.gameOver() << endl;
    cout << "PLAYER2 OVER\t" << player2.gameOver() << endl;
}
