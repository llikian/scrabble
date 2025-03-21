/***************************************************************************************************
 * @file  Hand.hpp
 * @brief Declaration of the Hand struct
 **************************************************************************************************/

#pragma once

#include "Player.hpp"

/**
 * @struct Hand
 * @brief
 */
struct Hand {
    Hand(const Player& player);
    Hand(const char hand[HAND_SIZE]);
    Hand(const Hand& hand);
    Hand(const Hand& hand, unsigned int removedLetterIndex);
    void operator=(const Hand& hand);

    char letters[HAND_SIZE];
    unsigned int capacity;

    static void unitTests();
};