/***************************************************************************************************
 * @file  Spot.hpp
 * @brief Declaration of the Spot struct
 **************************************************************************************************/

#pragma once

enum class BonusType {
    None,
    LetterX2,
    LetterX3,
    WordX2,
    WordX3
};

struct Spot {
    char character;
    BonusType type;
};