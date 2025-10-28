#pragma once
#include <array>
#include <vector>
#include "Pos.hpp"
#include "Ship.hpp"
#include <vector>

enum class ShortResult {Invalid, Miss, Hit, Kill};

enum class Cell { Empty, Ship, Hit, Miss, Halo };

class Board
{
public:
    Board();

    bool addShip(const Pos& pos, int size, bool horizontal);
    ShortResult shot(const Pos& pos);
    void autoAddShip();
    void randAddShip();
    bool gameOver();
    bool fullShip() const;
    Cell cellAt(int x, int y) const;

private:
    bool regShot(const Pos& pos);
    void shipDrowned(int pos);
    bool coordinatesCorrect(const Pos& pos, int size, bool horizontal);

    std::array<std::array<Cell, 10>, 10> map;
    std::vector<Ship> ships;
};
