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
    Dictionary dictionary("data/dico.txt");;
    Bag bag;
    Player player(bag);
    Board board(bag, dictionary);

    for(unsigned int i = 0 ; i < 20 ; ++i) { player.playBestMove(board, false); }

    std::cout << '\n';

    if(!board.testAllWordsOnBoard()) { return -1; }
    std::cout << "No incorrect words were found on the board.\n";

    return 0;
}
