#pragma once
#include "Board.hpp"
#include "Pos.hpp"

class Player
{
public:
    void autoPlaceShip();
    bool placeShip(const Pos&, int, bool);
    void makeShot(const Pos&);
    void autoShot();
    bool endGame();
    Board& getBoard();

private:
    Board board;
};
