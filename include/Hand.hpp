/***************************************************************************************************
 * @file  Hand.hpp
 * @brief Declaration of the Hand struct
 **************************************************************************************************/

#pragma once

#define HAND_SIZE 7

struct Player;

/**
 * @struct Hand
 * @brief
 */
struct Hand {
    Hand(const Player& player);
    Hand(const Hand& hand);
    Hand(const Hand& hand, unsigned int removedLetterIndex);
    void operator=(const Hand& hand);

    char letters[HAND_SIZE];
    unsigned int capacity;

    static void unitTests();
};