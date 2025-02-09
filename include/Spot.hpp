/***************************************************************************************************
 * @file  Spot.hpp
 * @brief Declaration of the Spot struct
 **************************************************************************************************/

#pragma once

enum class BonusType : unsigned char {
    None,
    LetterX2,
    LetterX3,
    WordX2,
    WordX3
};

struct Position {
    unsigned int x;
    unsigned int y;
};

struct Spot {
    Spot();
    Spot(char character, BonusType type, unsigned int x, unsigned int y);

    char character;
    BonusType type;
    Position position;
};