/***************************************************************************************************
 * @file  Board.hpp
 * @brief Declaration of the Board struct
 **************************************************************************************************/

#pragma once

#include <string>
#include <vector>

#include "Dictionary.hpp"
#include "Direction.hpp"
#include "Move.hpp"
#include "Position.hpp"
#include "Spot.hpp"

#define BOARD_SIZE 15
#define HAND_SIZE 7

struct Player;

/**
 * @struct Board
 * @brief
 */
struct Board {
public:
    Spot board[BOARD_SIZE][BOARD_SIZE];

    Board(const Bag& bag, const Dictionary& dictionary);

    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;

    bool isPositionValid(const Position& position) const;
    bool isCoordinateValid(unsigned int coord) const;

    char& operator ()(int row, int column);
    BonusType getBonusType(int row, int column) const;

    void sortMoveByPoints(std::vector<Move>& moves) const;
    std::vector<Move> getAllMoves(const char hand[HAND_SIZE], bool print = false) const;

private:
    const Bag& bag;
    const Dictionary& dictionay;

    int getWordPoints(const Spot& startSpot, char startLetter, const Direction& direction) const;
    void applyBonusPoints(Move& move) const;
    void checkForWords(const char hand[HAND_SIZE], const Spot* startSpot, std::vector<Move>& moves, const Direction& direction) const;
};
