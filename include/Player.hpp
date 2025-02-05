/***************************************************************************************************
 * @file  Player.hpp
 * @brief Declaration of the Player struct
 **************************************************************************************************/

#pragma once

#include "Bag.hpp"

#define HAND_SIZE 7

/**
 * @struct Player
 * @brief
 */
struct Player {
    Player(Bag& bag);

    Bag& bag;
    char hand[HAND_SIZE];
    unsigned int capacity;
};