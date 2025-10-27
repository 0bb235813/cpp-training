#include "../include/Game.hpp"
#include <cassert>
#include <iostream>

void Game::start()
{
    std::cout << "Начало игры" << std::endl;
    player2.autoPlaceShip();

    while(!player1.getBoard().fullShip())
    {
        char x;
        int y, size;
        bool h;
        view.printBoard(player1);
        view.printBoard(player2);
        std::cout << "Введите координаты для размещения корабля" << std::endl;
        std::cin >> x >> y >> size >> h;
        player1.placeShip(Pos(x, y), size, h);
        std::cout << "\033c";
    }

    while(!player1.endGame() && !player2.endGame())
    {
        view.printBoard(player1);
        view.printBoard(player2);
        std::cout << "Введите координаты для выстрела" << std::endl;
        char x;
        int y;
        std::cin >> x >> y;
        view.printShotResult(player2.makeShot(Pos(x, y)));
        std::cout << "\033c";
        player1.autoShot();
    }

    std::cout << "КОНЕЦ ИГРЫ" << std::endl;
}

void Game::test()
{
    Player player;
    assert(player.placeShip(Pos('A', 1), 4, 0) == true);
    assert(player.placeShip(Pos('M', 1), 4, 0) == false);
    assert(player.placeShip(Pos('B', 5), 5, 1) == false);
    assert(player.placeShip(Pos('B', 5), 0, 1) == false);
}
