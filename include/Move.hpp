/***************************************************************************************************
 * @file  Move.hpp
 * @brief Declaration of the Move struct
 **************************************************************************************************/

#pragma once

#include <string>
#include "Direction.hpp"
#include "Position.hpp"

/**
 * @struct Move
 * @brief
 */
struct Move {
    Position start; // Position where the search started
    Direction direction;
    std::string word; // Word as it is in the gaddag
    unsigned int points;
};

bool operator>(const Move& m1, const Move& m2);