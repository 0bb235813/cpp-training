#include "../include/Ship.hpp"

Ship::Ship(const std::vector<Pos>& positions) : positions(positions), hits(positions.size(), true) {}

const std::vector<Pos>& Ship::getPositions()
{
    return positions;
}

void Ship::registerHit(const Pos& pos)
{
    for (int i{}; i < positions.size(); ++i)
        if (positions[i] == pos)
            hits[i] = false;
}

size_t Ship::getHitsSize() const
{
    return hits.size();
}

const std::vector<bool>& Ship::getHits()
{
    return hits;
}
