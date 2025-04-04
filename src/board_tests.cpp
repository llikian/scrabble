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

#define BOARD_AMOUNT 100

int main() {
    unsigned int total = 0;
    unsigned int min = -1;
    unsigned int max = 0;

    for(unsigned int i = 0 ; i < BOARD_AMOUNT ; ++i) {
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
            return -1;
        }

        std::cout << "No incorrect words were found on board " << i + 1 << ".\n\n";
    }

    std::cout << "\nThe average points for a complete game is: " << static_cast<float>(total) / BOARD_AMOUNT << '\n';
    std::cout << "The minimum points for a complete game is: " << min << '\n';
    std::cout << "The maximum points for a complete game is: " << max << '\n';

    return 0;
}
