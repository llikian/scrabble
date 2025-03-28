/***************************************************************************************************
 * @file  test.cpp
 * @brief Contains the unit tests for the project
 **************************************************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>

#include "Bag.hpp"
#include "Board.hpp"
#include "Dictionary.hpp"
#include "Player.hpp"

int main() {
    Dictionary dictionary("data/dico.txt");;
    Bag(bag);
    Player player(bag);
    Board board(bag, dictionary);

    for(unsigned int i = 0 ; i < 2 ; ++i) { player.playBestMove(board); }

    if(!board.testAllWordsOnBoard()) {
        std::cerr << "Invalid words found on board !\n";
        return -1;
    }

    return 0;
}
