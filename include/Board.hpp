/***************************************************************************************************
 * @file  Board.hpp
 * @brief Declaration of the Board struct
 **************************************************************************************************/

#pragma once

#include <string>
#include "Spot.hpp"

#define BOARD_SIZE 15

/**
 * @struct Board
 * @brief
 */
struct Board {
public:
    Board();

    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;

    char& operator ()(int row, int column);
    BonusType getBonusType(int row, int column);
private:
    Spot board[BOARD_SIZE][BOARD_SIZE];
};