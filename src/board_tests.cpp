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

int main() {
    for(unsigned int boards = 0 ; boards < 10 ; ++boards) {
        Dictionary dictionary("data/dico.txt");
        Bag bag;
        Player player(bag);
        Board board(bag, dictionary);

        while(player.playBestMove(board, false)) { }

        if(!board.testAllWordsOnBoard()) {
            board.saveToFile("data/test_boards_wrong_board.txt");
            return -1;
        }

        std::cout << "No incorrect words were found on the board.\n\n";
    }

    return 0;
}
