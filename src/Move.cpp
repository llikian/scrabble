/***************************************************************************************************
 * @file  Move.cpp
 * @brief Implementation of the Move struct
 **************************************************************************************************/

#include "Move.hpp"


bool operator>(const Move& m1, const Move& m2) {
    return m1.points > m2.points;
}
