#include "../include/Ship.hpp"

Ship::Ship(const std::vector<Pos>& positions) : positions(positions), hits(positions.size(), true) {}

std::vector<Pos>& Ship::getPositions()
{
    return positions;
}

std::vector<bool>& Ship::getHits()
{
    return hits;
}
