#pragma once
#include "Board.hpp"
#include "Pos.hpp"

class Player
{
public:
    void autoPlaceShip();
    bool placeShip(const Pos&, int, bool);
    ShortResult makeShot(const Pos&);
    ShortResult autoShot();
    bool endGame();
    const Board& getBoard() const;

private:
    Board board;
};
