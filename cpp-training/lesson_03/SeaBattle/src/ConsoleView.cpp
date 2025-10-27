#include "../include/ConsoleView.hpp"

void ConsoleView::printBoard (const Player& p1) const
{
    std::cout << "  ";
    for (int i = 1; i < 11; ++i)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (int i{}; i < 10; ++i) {
        std::cout << (char)(i+65) << ' ';
        for (int j{}; j < 10; ++j) {
            switch (p1.getBoard().cellAt(i, j)) {
                case Cell::Empty:
                    std::cout << "  ";
                    break;

                case Cell::Ship:
                    std::cout << "S ";
                    break;

                case Cell::Halo:
                    std::cout << ". ";
                    break;

                case Cell::Hit:
                    std::cout << "X ";
                    break;

                case Cell::Miss:
                    std::cout << "0 ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void ConsoleView::fogOfWar(const Player& p) const
{
    std::cout << "  ";
    for (int i = 1; i < 11; ++i)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (int i{}; i < 10; ++i) {
        std::cout << (char)(i+65) << ' ';
        for (int j{}; j < 10; ++j) {
            switch (p.getBoard().cellAt(i, j)) {
                case Cell::Ship:
                    std::cout << "  ";
                    break;

                case Cell::Empty:
                    std::cout << "  ";
                    break;

                case Cell::Halo:
                    std::cout << ". ";
                    break;

                case Cell::Hit:
                    std::cout << "X ";
                    break;

                case Cell::Miss:
                    std::cout << "0 ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void ConsoleView::printShotResult(ShortResult res)
{
    switch (res) {
        case ShortResult::Miss:
            std::cout << "Мимо\n";
            break;
        case ShortResult::Hit:
            std::cout << "Попал\n";
            break;
        case ShortResult::Kill:
            std::cout << "Корабль уничтожен\n";
            break;
        case ShortResult::Invalid:
            std::cout << "Неверные координаты\n";
            break;
    }
}
