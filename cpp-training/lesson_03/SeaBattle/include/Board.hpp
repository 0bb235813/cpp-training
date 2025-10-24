#pragma once
#include <vector>
#include <string>
#include "Pos.hpp"
#include "Ship.hpp"

#include <vector>
class Board
{
public:
    Board();

    bool addShip(const Pos& pos, int size, bool horizontal);
    void printBoard();
    bool shot(const Pos& pos);
    void printPos();
    void autoAddShip();
    void randAddShip();
    bool gameOver();
    bool fullShip();
    void fogOfWar();

private:
    void regShot(const Pos& pos);
    void shipDrowned(int pos);
    bool coordinatesCorrect(const Pos& pos, int size, bool horizontal);

    std::vector<std::vector<std::string>> map;
    std::vector<Ship> ships;
};
