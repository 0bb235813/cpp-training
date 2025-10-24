#include "../include/Pos.hpp"

Pos::Pos() : x(0), y(0), horizontal(false) {}
Pos::Pos(int n, int m) : x(n), y(m), horizontal(false) {}
bool Pos::operator==(const Pos& other) const { return x == other.x && y == other.y; }
