#include "../include/Board.hpp"
#include "../include/Pos.hpp"
#include <cstdlib>
#include <iostream>
#include "../include/Player.hpp"

void Player::autoPlaceShip()
{
    board.autoAddShip();
}

bool Player::placeShip(const Pos& pos, int size, bool horizontal)
{
    return board.addShip(pos, size, horizontal);
}

void Player::makeShot(const Pos& pos)
{
    board.shot(pos);
}

void Player::autoShot()
{
    Pos p = Pos((rand()%10)+65, (rand()%10)+1);
    std::cout << "X\t" << p.x << " Y\t" << p.y << std::endl;
    Player::makeShot(p);
}

bool Player::endGame()
{
    return board.gameOver();
}

Board& Player::getBoard()
{
    return board;
}
