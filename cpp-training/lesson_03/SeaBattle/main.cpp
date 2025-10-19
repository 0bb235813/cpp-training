#include <algorithm>
#include <cstdlib>
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

    bool addShip(const Pos& pos, int size, bool horizontal)
    {
        if (!coordinatesCorrect(pos, size, horizontal)) {
            cout << "Incorrect coordinate" << endl;
            return false;
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

        if (fullShip()) return false;
        return true;
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
        if (pos.x-65 > 10 || pos.x-65 < 0 || pos.y > 10 || pos.y < 1) {
            cout << "Неверные координы выстрела" << endl;
            return false;
        }
        if (map[pos.x-65][pos.y-1] == "S ")
        {
            regShot(pos);
            map[pos.x-65][pos.y-1] = "X ";
            cout << "Ранил" << endl;
            return true;
        }
        else if (map[pos.x-65][pos.y-1] == "  ")
        {
            map[pos.x-65][pos.y-1] = "O ";
            cout << "Мимо" << endl;
            return true;
        }
        return false;
    }


    void printPos()
    {
        for (int i{}; i < positions.size(); ++i)
            for (auto j : positions[i])
                cout << j.x-65 << " " << j.y << endl;
    }

    void autoAddShip()
    {
        while(!fullShip()) randAddShip();
    }

    void randAddShip()
    {
        Pos pos;
        int size;
        bool horizontal;
        do {
            pos = Pos((rand()%10)+65, (rand()%10)+1);
            size = (rand()%4)+1;
            horizontal = rand()%2;
        }while (!coordinatesCorrect(pos, size, horizontal));

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

    bool gameOver() { return positions.empty(); }

private:
    vector<vector<string>> map;
    vector<vector<Pos>> positions;
    vector<vector<bool>> boolPos;
    bool fullShip()
    {
        int four{}, three{}, two{}, one{};
        for (int i{}; i < boolPos.size(); ++i) {
            if (boolPos[i].size() == 4) ++four;
            if (boolPos[i].size() == 3) ++three;
            if (boolPos[i].size() == 2) ++two;
            if (boolPos[i].size() == 1) ++one;
        }
        if (four != 1 || three != 2 || two != 3 || one != 4) return false;
        return true;
    }
    void regShot(const Pos pos)
    {
        for (int i{}; i < positions.size(); ++i) {
            for (int j{}; j < positions[i].size(); ++j) {
                if (positions[i][j] == pos) {
                    boolPos[i][j] = false;
                    if (*max_element(boolPos[i].begin(), boolPos[i].end()) == 0)
                    {
                        cout << "Убил" << endl;
                        shipDrowned(i);
                    }
                    break;
                }
            }
        }
    }

    void shipDrowned(int pos)
    {
        if (positions[pos].size() == 1)
        {
            for (int i = positions[pos][0].y-2; i < positions[pos][0].y + (int)positions[pos].size(); ++i) {
                for (int j = positions[pos][0].x-1-65; j <= positions[pos][0].x+1-65; ++j) {
                    if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[j][i] != "X ") {
                        map[j][i] = ". ";
                    }
                }
            }
        }
        else if (positions[pos][0].x == positions[pos][1].x) {
            for (int i = positions[pos][0].y-2; i < positions[pos][0].y + (int)positions[pos].size(); ++i) {
                for (int j = positions[pos][0].x-1-65; j <= positions[pos][0].x+1-65; ++j) {
                    if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[j][i] != "X ") {
                        map[j][i] = ". ";
                    }
                }
            }
        }
        else if (positions[pos][0].x != positions[pos][1].x) {
            for (int i = positions[pos][0].x-1-65; i < positions[pos][0].x-65 + (int)positions[pos].size()+1; ++i) {
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
        int count{};
        for (int i{}; i < boolPos.size(); ++i) {
            if (size == 4 && boolPos[i].size() == 4) return false; 
            else if (size == 3 && boolPos[i].size() == 3) {
                ++count;
                if ( count >= 2) return false;
            }
            else if (size == 2 && boolPos[i].size() == 2) {
                ++count;
                if ( count >= 3) return false;
            }
            else if (size == 1 && boolPos[i].size() == 1) {
                ++count;
                if ( count >= 4) return false;
            }
        }
        if (size > 4 || size <= 0) return false;
        if (!horizontal)
        {
            if (pos.x-65 < 0 || pos.x-65+size > 10 || pos.y <= 0 || pos.y > 10)
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
            if (pos.y <= 0 || pos.y-1+size > 10 || pos.x-65 <= 0 || pos.x-65 > 10)
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
    Board bot;
    bot.autoAddShip();

    //cout << "Введите координаты кораблей" << endl;
    //bool fullship;
    //char x;
    //int y;
    //int s;
    //bool h;
    //cin >> x >> y >> s >> h;
    //fullship = player1.addShip(Pos(x, y), s, h);
    //player1.printBoard();
    //while(fullship)
    //{
    //    cin >> x >> y >> s >> h;
    //    cout << "\033c";
    //    fullship = player1.addShip(Pos(x, y), s, h);
    //    player1.printBoard();
    //}

    cout << "Введите координаты для удара" << endl;
    bot.printBoard();

    while(!player1.gameOver() || !bot.gameOver())
    {
        char x;
        int y;
        cin >> x >> y;
        //cout << "\033c";
        bot.shot(Pos(x, y));
        bot.printBoard();
    }
    cout << "КОНЕЦ ИГРЫ" << endl;
}
