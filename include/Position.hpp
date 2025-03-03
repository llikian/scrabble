/***************************************************************************************************
 * @file  Position.hpp
 * @brief Declaration of the Position struct
 **************************************************************************************************/

#pragma once

/**
 * @struct Position
 * @brief
 */
struct Position {
    unsigned int x;
    unsigned int y;

    bool operator==(const Position& pos) const;
};
