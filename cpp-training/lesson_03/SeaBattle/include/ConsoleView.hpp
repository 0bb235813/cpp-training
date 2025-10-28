#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include <iostream>

class ConsoleView
{
public:
    void printBoard(const Player&) const;
    void printShotResult(ShortResult);
    void fogOfWar(const Player&) const;
};
