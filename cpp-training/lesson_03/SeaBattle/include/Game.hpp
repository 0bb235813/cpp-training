#pragma once
#include "Player.hpp"
#include "ConsoleView.hpp"

class Game
{
public:
    void start();
    void test();

private:
    Player player1;
    Player player2;
    ConsoleView view;
};
