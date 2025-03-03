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
#include "Player.hpp"
#include "Position.hpp"
#include "Spot.hpp"

#define BOARD_SIZE 15

/**
 * @struct Board
 * @brief
 */
struct Board {
public:
    Board(const Bag& bag, const Dictionary& dictionary);

    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path) const;

    bool isPositionValid(const Position& position) const;
    bool isCoordinateValid(unsigned int coord) const;

    char& operator ()(int row, int column);
    BonusType getBonusType(int row, int column) const;

    void sortMoveByPoints(std::vector<Move>& moves) const;
    std::vector<Move> getAllMoves(Player& player, bool print = false) const;
    Move getMostPointsMove(Player& player) const;

    void playMove(Player& player, const Move& move);
    void playMostPointsMove(Player& player);

private:
    Spot board[BOARD_SIZE][BOARD_SIZE];
    const Bag& bag;
    const Dictionary& dictionay;

    int getWordPoints(const Spot& startSpot, const Direction& direction) const;
    void applyBonusPoints(Move& move) const;
    void checkForWords(Player& player, const Spot* startSpot, std::vector<Move>& moves, const Direction& direction) const;
};
