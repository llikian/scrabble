/***************************************************************************************************
 * @file  Position.cpp
 * @brief Implementation of the Position struct
 **************************************************************************************************/

#include "Position.hpp"

bool Position::operator==(const Position& pos) const {
    return x == pos.x && y == pos.y;
}
