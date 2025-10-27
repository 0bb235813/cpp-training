#include "../include/Board.hpp"
#include <algorithm>
#include <cstdlib>
#include <array>

Board::Board() {
    for (auto& el : map) el.fill(Cell::Empty);
}

bool Board::addShip(const Pos& pos, int size, bool horizontal)
{
    if (!coordinatesCorrect(pos, size, horizontal)) return false;
    std::vector<Pos> p;
    std::vector<bool> b;
    if (horizontal)
    {
        for (int i{}; i < size; ++i) {
            map[pos.x-65][pos.y+i-1] = Cell::Ship;
            p.push_back(Pos(pos.x, pos.y+i));
            b.push_back(true);
        }
    }
    else {
        for (int i{}; i < size; ++i) {
            map[pos.x+i-65][pos.y-1] = Cell::Ship;
            p.push_back(Pos(pos.x+i, pos.y));
            b.push_back(true);
        }
    }
    ships.emplace_back(p);

    if (fullShip()) return false;
    return true;
}

Cell Board::cellAt(int x, int y) const
{
    return map[x][y];
}

ShortResult Board::shot(const Pos& pos)
{
    if (pos.x-65 > 10 || pos.x-65 < 0 || pos.y > 10 || pos.y < 1) {
        return ShortResult::Invalid;
    }
    if (map[pos.x-65][pos.y-1] == Cell::Ship)
    {
        map[pos.x-65][pos.y-1] = Cell::Hit;
        if (regShot(pos)) return ShortResult::Kill;
        return ShortResult::Hit;
    }
    else if (map[pos.x-65][pos.y-1] == Cell::Empty)
    {
        map[pos.x-65][pos.y-1] = Cell::Miss;
        return ShortResult::Miss;
    }
    else if (map[pos.x-65][pos.y-1] == Cell::Halo) return ShortResult::Miss;
    else if (map[pos.x-65][pos.y-1] == Cell::Hit) return ShortResult::Hit;
    else if (map[pos.x-65][pos.y-1] == Cell::Empty) return ShortResult::Miss;
    return ShortResult::Miss;
}

void Board::autoAddShip()
{
    while(!fullShip()) randAddShip();
}

void Board::randAddShip()
{
    Pos pos;
    int size;
    bool horizontal;
    do {
        pos = Pos((rand()%10)+65, (rand()%10)+1);
        size = (rand()%4)+1;
        horizontal = rand()%2;
    }while (!coordinatesCorrect(pos, size, horizontal));

    std::vector<Pos> p;
    std::vector<bool> b;
    if (horizontal)
    {
        for (int i{}; i < size; ++i) {
            map[pos.x-65][pos.y+i-1] = Cell::Ship;
            p.push_back(Pos(pos.x, pos.y+i));
            b.push_back(true);
        }
    }
    else {
        for (int i{}; i < size; ++i) {
            map[pos.x+i-65][pos.y-1] = Cell::Ship;
            p.push_back(Pos(pos.x+i, pos.y));
            b.push_back(true);
        }
    }
    ships.emplace_back(p);
}

bool Board::gameOver() {
    return ships.empty();
}

bool Board::fullShip() const
{
    int four{}, three{}, two{}, one{};
    for (int i{}; i < ships.size(); ++i) {
        if (ships[i].getHitsSize() == 4) ++four;
        if (ships[i].getHitsSize() == 3) ++three;
        if (ships[i].getHitsSize() == 2) ++two;
        if (ships[i].getHitsSize() == 1) ++one;
    }
    if (four != 1 || three != 2 || two != 3 || one != 4) return false;
    return true;
}

bool Board::regShot(const Pos& pos)
{
    for (int i{}; i < ships.size(); ++i) {
        for (int j{}; j < ships[i].getPositions().size(); ++j) {
            if (ships[i].getPositions()[j] == pos) {
                ships[i].registerHit(pos);
                if (*max_element(ships[i].getHits().begin(), ships[i].getHits().end()) == 0)
                {
                    shipDrowned(i);
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

void Board::shipDrowned(int pos)
{
    const auto& ship = ships[pos].getPositions();
    if (ship.size() == 1)
    {
        for (int i = ship[0].y-2; i < ship[0].y + (int)ship.size(); ++i) {
            for (int j = ship[0].x-1-65; j <= ship[0].x+1-65; ++j) {
                if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[j][i] != Cell::Hit) {
                    map[j][i] = Cell::Halo;
                }
            }
        }
    }
    else if (ship[0].x == ship[1].x) {
        for (int i = ship[0].y-2; i < ship[0].y + (int)ship.size(); ++i) {
            for (int j = ship[0].x-1-65; j <= ship[0].x+1-65; ++j) {
                if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[j][i] != Cell::Hit) {
                    map[j][i] = Cell::Halo;
                }
            }
        }
    }
    else if (ship[0].x != ship[1].x) {
        for (int i = ship[0].x-1-65; i < ship[0].x-65 + (int)ship.size()+1; ++i) {
            for (int j = ship[0].y-2; j <= ship[0].y; ++j) {
                if ( i >= 0 && i < 10 && j >= 0 && j < 10 && map[i][j] != Cell::Hit)
                    map[i][j] = Cell::Halo;
            }
        }
    }
    ships.erase(ships.begin()+pos);
}

bool Board::coordinatesCorrect(const Pos& pos, int size, bool horizontal)
{
    int count{};
    for (int i{}; i < ships.size(); ++i) {
        if (size == 4 && ships[i].getHits().size() == 4) return false;
        else if (size == 3 && ships[i].getHits().size() == 3) {
            ++count;
            if ( count >= 2) return false;
        }
        else if (size == 2 && ships[i].getHits().size() == 2) {
            ++count;
            if ( count >= 3) return false;
        }
        else if (size == 1 && ships[i].getHits().size() == 1) {
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
                    if (map[i][j] == Cell::Ship) return false;
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
                    if (map[j][i] == Cell::Ship) return false;
            }
        }
    }
    return true;
}
