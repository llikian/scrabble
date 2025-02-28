/***************************************************************************************************
 * @file  Spot.cpp
 * @brief Implementation of the Spot struct
 **************************************************************************************************/

#include "Spot.hpp"

bool Position::operator==(const Position& pos) const
{
    return x == pos.x && y == pos.y;
}

Spot::Spot()
    : character('\0'), type(BonusType::None), position(0, 0) { }

Spot::Spot(char character, BonusType type, unsigned int x, unsigned int y)
    : character(character), type(type), position(x, y) { }