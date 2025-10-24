#pragma once
#include <vector>
#include "Pos.hpp"

class Ship
{
public:
    Ship (const std::vector<Pos>& positions);

    std::vector<Pos>& getPositions();
    std::vector<bool>& getHits();

private:
    std::vector<Pos> positions;
    std::vector<bool> hits;
};
