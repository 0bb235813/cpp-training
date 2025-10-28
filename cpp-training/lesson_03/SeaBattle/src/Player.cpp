#include "../include/Board.hpp"
#include "../include/Pos.hpp"
#include <cstdlib>
#include "../include/Player.hpp"

void Player::autoPlaceShip()
{
    board.autoAddShip();
}

bool Player::placeShip(const Pos& pos, int size, bool horizontal)
{
    return board.addShip(pos, size, horizontal);
}

ShortResult Player::makeShot(const Pos& pos)
{
    return board.shot(pos);
}

ShortResult Player::autoShot()
{
    Pos p = Pos((rand()%10)+65, (rand()%10)+1);
    return makeShot(p);
}

bool Player::endGame()
{
    return board.gameOver();
}

const Board& Player::getBoard() const
{
    return board;
}
