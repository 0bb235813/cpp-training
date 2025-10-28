#pragma once
#include <vector>
#include "Pos.hpp"

class Ship
{
public:
    Ship (const std::vector<Pos>& positions);

    void registerHit(const Pos&);
    size_t getHitsSize() const;

    const std::vector<Pos>& getPositions();
    const std::vector<bool>& getHits();

private:
    std::vector<Pos> positions;
    std::vector<bool> hits;
};
