/***************************************************************************************************
 * @file  Spot.cpp
 * @brief Implementation of the Spot struct
 **************************************************************************************************/

#include "Spot.hpp"

Spot::Spot() : character('\0'), type(BonusType::None), position(0, 0) { }

Spot::Spot(char character, BonusType type, unsigned int x, unsigned int y)
    : character(character), type(type), position(x, y) { }

bool Spot::isEmpty() const {
    return character == '\0';
}
