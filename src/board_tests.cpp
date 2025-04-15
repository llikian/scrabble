/***************************************************************************************************
 * @file  test.cpp
 * @brief Contains the unit tests for the project
 **************************************************************************************************/

#include <fstream>
#include <iostream>

#include "Bag.hpp"
#include "Board.hpp"
#include "Dictionary.hpp"
#include "Player.hpp"

bool playEntireGame(unsigned int index, unsigned int& total, unsigned int& min, unsigned int& max) {
    Dictionary dictionary("data/dico.txt");
    Bag bag;
    Player player(bag);
    Board board(bag, dictionary);

    while(player.playBestMove(board, false)) { }

    total += player.points;
    if(player.points < min) { min = player.points; }
    if(player.points > max) { max = player.points; }

    if(!board.testAllWordsOnBoard()) {
        board.saveToFile("data/test_boards_wrong_board.txt");
        return false;
    }

    std::cout << "No incorrect words were found on board " << index + 1 << ".\n\n";

    return true;
}

int main() {
    constexpr unsigned int BOARD_AMOUNT = 100;

    unsigned int total = 0;
    unsigned int min = -1;
    unsigned int max = 0;

    for(unsigned int i = 0 ; i < BOARD_AMOUNT ; ++i) { playEntireGame(i, total, min, max); }

    std::cout << "\nThe average points for a complete game is: " << static_cast<float>(total) / BOARD_AMOUNT << '\n';
    std::cout << "The minimum points for a complete game is: " << min << '\n';
    std::cout << "The maximum points for a complete game is: " << max << '\n';

    return 0;
}
