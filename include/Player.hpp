/***************************************************************************************************
 * @file  Player.hpp
 * @brief Declaration of the Player struct
 **************************************************************************************************/

#pragma once

#include "Board.hpp"
#include "Bag.hpp"

/**
 * @struct Player
 * @brief
 */
struct Player {
    Player(Bag& bag);

    Bag& bag;
    char hand[HAND_SIZE];
    unsigned int capacity;
    unsigned int points;

    void refreshHand(const std::string& usedLetters);

    void playMove(Board & board, const Move& move);
    void playMostPointsMove(Board& board);
};
