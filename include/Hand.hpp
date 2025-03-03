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
    Hand(const Hand& hand);
    Hand(const Hand& hand, unsigned int removedLetterIndex);
    void operator=(const Hand& hand);

    char letters[7];
    unsigned int capacity;
};